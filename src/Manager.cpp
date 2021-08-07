#include "Manager.h"
#include "Textures.h"
#include "Macros.h"
#include <iostream>
#include <memory>
#include <algorithm>
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
				if (m_dice.isClickedOn(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
					m_player.play(&m_dice, m_window, *this);
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
}
//=============================================================================
int Manager::getPointContainsClick(const sf::Vector2f& clickLocation)
{
	for (int i = 0; i < m_points.size(); i++)
		if (m_points[i].get()->getBounds().contains(clickLocation))
			return i;
	return -1;
}
//=============================================================================
Point* Manager::getPoint(int wantedIndex) const
{
	return m_points[wantedIndex].get();
}
//=============================================================================
bool Manager::isMovePossible(int pointClicked, int toPoint, DIRECTION direction)
{
	switch (direction) {
	case RIGHT:
		if (pointClicked - toPoint >= 0)
			if (m_points[pointClicked - toPoint].get()->getColor() == m_points[pointClicked].get()->getColor() ||
				m_points[pointClicked - toPoint].get()->getCheckersNumber() <= 1)
				return true;
		break;
	case LEFT:
		if (pointClicked + toPoint >= m_points.size())
			if (m_points[pointClicked + toPoint].get()->getColor() == m_points[pointClicked].get()->getColor() ||
				m_points[pointClicked + toPoint].get()->getCheckersNumber() <= 1)
				return true;
		break;
	default: 
		return false;
	}
	return false;
}
//=============================================================================
void Manager::movePlayer(int fromPoint, int toPoint)
{
	Checker* p2Checker = m_points[fromPoint].get()->getChecker(m_points[fromPoint].get()->getCheckersNumber() - 1);
	m_points[fromPoint].get()->del(p2Checker);
	if(m_points[fromPoint].get()->getCheckersNumber() == 0)
		m_points[fromPoint].get()->setColor(NO_COLOR);

	if (m_points[toPoint].get()->getCheckersNumber() == 1)
		eatChecker(m_points[toPoint].get()->getChecker(0));

	p2Checker->updatePos(m_points[toPoint].get()->getPosition(), m_points[toPoint].get()->getCheckersNumber(), toPoint);

	m_points[toPoint].get()->add(p2Checker);
	m_points[toPoint].get()->setColor(WHITE);
}
//=============================================================================

void Manager::moveAI(int fromPoint, int toPoint)
{

}

//=============================================================================

void Manager::eatChecker(Checker* checker)
{
}

//=============================================================================

void Manager::moveChecker(int fromPoint, std::pair<int, int>& diceResult, DIRECTION direction)
{
	int maxValue = std::max(diceResult.first, diceResult.second);
	int minValue = std::min(diceResult.first, diceResult.second);
	if (isMovePossible(fromPoint, maxValue, direction)) {
		if (direction == RIGHT)
			movePlayer(fromPoint, fromPoint - maxValue);
		else
			moveAI(fromPoint, fromPoint + maxValue);
		m_dice.updateResult(maxValue, diceResult);
	}
	else if (isMovePossible(fromPoint, minValue, direction)) {
		if (direction == RIGHT)
			movePlayer(fromPoint, fromPoint - minValue);
		else
			moveAI(fromPoint, fromPoint + minValue);
		m_dice.updateResult(minValue, diceResult);
	}
}
