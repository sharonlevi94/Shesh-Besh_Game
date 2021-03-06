#include "Manager.h"
#include "Textures.h"
#include "Music.h"
#include "Macros.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <Windows.h>
//=============================================================================

Manager::Manager()
	: m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Shesh-Besh Game", sf::Style::Titlebar | sf::Style::Close),
	m_player(), m_AI(), m_dice()
{
	m_window.setFramerateLimit(FRAME_LIMIT);
	srand((unsigned int)time(nullptr));
	m_background.setSize({ WIN_WIDTH, WIN_HEIGHT });
	m_background.setPosition({ 0,0 });
	//m_points.resize(NUM_OF_POINTS);
}

//=============================================================================

void Manager::run()
{
	initializeBoard();
	while (m_window.isOpen()) {
		for (auto event = sf::Event{}; m_window.waitEvent(event);) {
			m_window.clear();
			draw();
			m_window.display();
			switch (event.type) {
			case sf::Event::Closed:
				m_window.close();
			case sf::Event::MouseMoved:
				m_dice.mousePassOnButton(m_window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}));
				break;
			case sf::Event::MouseButtonReleased:
				switch (m_dice.getState()) {
				case ROLL_START:
					if (m_dice.isClickedOn(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
						firstRoll();
					break;
				case ROLL:
					if (m_dice.isClickedOn(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
							m_player.play(&m_dice, m_window, *this);
					break;
				case DONE:
					if (m_dice.isClickedOn(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }))) {
						Music::instance().playSound(BUTTON);
						Sleep(THINKING_TIME);
						m_dice.setState(AI_TURN);
						m_AI.play(&m_dice, m_window, *this);
					}
					break;
				}
			}
		}
	}
}

//=============================================================================

const sf::Texture& Manager::runBoardScreen()
{
	return Textures::instance().getBackground(BOARD1);
}

//=============================================================================

void Manager::initializeBoard()
{
	m_background.setTexture(&runBoardScreen());

	//Featured: ask player for wanted color

	setPoints();
	setCheckers();
}

//=============================================================================

void Manager::setPoints()
{
	for (int i = 0; i < NUM_OF_POINTS/2; i++) {
		if (i < NUM_OF_POINTS / 4) //at player home
			m_points.push_back(std::make_unique<Point>(sf::Vector2f(RIGHT_CORNER - DIFF * i, BOTTOM),
				sf::Vector2f(RIGHT_CORNER - (DIFF * i), AREA_POS_BOT)));
		else
			m_points.push_back(std::make_unique<Point>(sf::Vector2f(LEFT_CORNER + DIFF * ((NUM_OF_POINTS/2-1)-i), BOTTOM),
				sf::Vector2f(LEFT_CORNER + DIFF * ((NUM_OF_POINTS/2 - 1) - i), AREA_POS_BOT)));
	}
	for (int i = 0; i < NUM_OF_POINTS/2; i++) {
		if (i < NUM_OF_POINTS / 4)
			m_points.push_back(std::make_unique<Point>(sf::Vector2f(LEFT_CORNER + DIFF * i, TOP),
				sf::Vector2f(LEFT_CORNER + DIFF * i, TOP)));
		else //at opponent home
			m_points.push_back(std::make_unique<Point>(sf::Vector2f(HOME_LEFT + DIFF * (i % 6), TOP),
				sf::Vector2f(HOME_LEFT + DIFF * (i % 6), TOP)));
	}
}

//=============================================================================
void Manager::setCheckers()
{
	setPlayerCheckers();
	setAICheckers();
}
//=============================================================================

void Manager::setPlayerCheckers()
{
	//set player's checker to eact point:
	int i;
	for (i = 0; i < 5; i++) {
		m_points[5].get()->setColor(WHITE);
		m_points[5].get()->add(m_player.getChecker(i));
	}
	for (; i < 8; i++) {
		m_points[7].get()->setColor(WHITE);
		m_points[7].get()->add(m_player.getChecker(i));
	}
	for (; i < 13; i++) {
		m_points[12].get()->setColor(WHITE);
		m_points[12].get()->add(m_player.getChecker(i));
	}
	for (; i < 15; i++) {
		m_points[23].get()->setColor(WHITE);
		m_points[23].get()->add(m_player.getChecker(i));
	}
}

//=============================================================================

void Manager::setAICheckers()
{
	//set player's checker to eact point:
	int i;
	for (i = 0; i < 5; i++) {
		m_points[18].get()->setColor(BLACK);
		m_points[18].get()->add(m_AI.getChecker(i));
	}
	for (; i < 8; i++) {
		m_points[16].get()->setColor(BLACK);
		m_points[16].get()->add(m_AI.getChecker(i));
	}
	for (; i < 13; i++) {
		m_points[11].get()->setColor(BLACK);
		m_points[11].get()->add(m_AI.getChecker(i));
	}
	for (; i < 15; i++) {
		m_points[0].get()->setColor(BLACK);
		m_points[0].get()->add(m_AI.getChecker(i));
	}

}

//=============================================================================

void Manager::draw()
{
	m_window.draw(m_background);
	m_dice.draw(m_window);
	for (auto& point : m_points)
		point.get()->draw(m_window);
	for (auto& checker : m_lockedCheckers)
		checker->draw(m_window);
}

//=============================================================================

int Manager::getPointContainsClick(const sf::Vector2f& clickLocation)
{
	if (m_player.isLocked()) {
		for (auto& checker : m_lockedCheckers)
			if (checker->isContainsClick(clickLocation))
				return LOCK;
	}
	else {
		for (int i = 0; i < m_points.size(); i++)
			if (m_points[i].get()->getBounds().contains(clickLocation))
				return i;
	}
	
	return -1;
}

//=============================================================================

Point* Manager::getPoint(int wantedIndex) const
{
	return m_points[wantedIndex].get();
}

//=============================================================================

bool Manager::isMovePossible(int source, int step, DIRECTION direction)
{
	if (step == 0)
		return false;

	switch (direction) {
	case RIGHT:
		if (m_player.isLocked()) {
			if (m_points[step - 1].get()->getColor() == WHITE ||
				m_points[step - 1].get()->getCheckersNumber() < BLOCK)
				return true;
		}
		else {
			if (source - step >= 0)
				if (m_points[source - step].get()->getColor() == WHITE ||
					m_points[source - step].get()->getCheckersNumber() < BLOCK)
					return true;
		}
		break;
	case LEFT:
		if (m_AI.isLocked()) {
			if (m_points[NUM_OF_POINTS-step].get()->getColor() == BLACK ||
				m_points[NUM_OF_POINTS - step].get()->getCheckersNumber() < BLOCK)
				return true;
		}
		else {
			if (source + step < NUM_OF_POINTS)
				if (m_points[source + step].get()->getColor() == BLACK ||
					m_points[source + step].get()->getCheckersNumber() < BLOCK)
					return true;
		}
		break;
	default: 
		return false;
	}
	return false;
}

//=============================================================================

void Manager::updateBoard(int fromPoint, int toPoint, PLAYER_COLOR color)
{
	Music::instance().playSound(PLAY_STEP);
	

	Checker* p2Checker = m_points[fromPoint].get()->getChecker(m_points[fromPoint].get()->getCheckersNumber() - 1);
	m_points[fromPoint].get()->del(p2Checker);
	if(m_points[fromPoint].get()->getCheckersNumber() == 0)
		m_points[fromPoint].get()->setColor(NO_COLOR);


	if (m_points[toPoint].get()->getCheckersNumber() == 1 and m_points[toPoint].get()->getColor() != color) {
		eatChecker(m_points[toPoint].get()->getChecker(0));
		m_points[toPoint].get()->del(m_points[toPoint].get()->getChecker(0));
	}
	p2Checker->updatePos(m_points[toPoint].get()->getPosition(), m_points[toPoint].get()->getCheckersNumber(), toPoint);
	m_points[toPoint].get()->add(p2Checker);
	m_points[toPoint].get()->setColor(color);
}

//=============================================================================

void Manager::eatChecker(Checker* checker)
{
	if (checker->getColor() == WHITE)
		m_player.setLock(true);
	else
		m_AI.setLock(true);

	checker->updatePos(sf::Vector2f(WIN_WIDTH / 2 - 30, WIN_HEIGHT / 2), m_lockedCheckers.size(), LOCK);
	m_lockedCheckers.push_back(checker);
}

//=============================================================================

void Manager::firstRoll()
{
	m_dice.setState(START);
	m_dice.roll();
	while (m_dice.getResult().first == m_dice.getResult().second)
		m_dice.roll();
	if (m_dice.getResult().first > m_dice.getResult().second)
		m_dice.setState(ROLL);
	else
		m_dice.setState(DONE); 
}

//=============================================================================

void Manager::movePlayer(int fromPoint, const std::pair<int, int>& diceResult)
{
	int maxValue = std::max(diceResult.first, diceResult.second);
	int minValue = std::min(diceResult.first, diceResult.second);
	int step = 0;

	if (isMovePossible(fromPoint, maxValue, RIGHT)) 
		step = maxValue;
	
	else if (isMovePossible(fromPoint, minValue, RIGHT)) 
		step = minValue;
	else {
		m_dice.setState(AI_TURN);
		return;
	}
	updateBoard(fromPoint, fromPoint - step, WHITE);

	m_dice.updateResult(step);
}
