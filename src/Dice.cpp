#include "Dice.h"
#include "Macros.h"
#include "Textures.h"

Dice::Dice()
{
	m_state = ROLL_START;

	m_rollButton.setPosition({ BUTTON_POS_X, BUTTON_POS_Y });
	m_rollButton.setFillColor(sf::Color::White);
	m_rollButton.setFont(Textures::instance().getFont());
	m_rollButton.setCharacterSize(CHAR_SIZE);
	m_rollButton.setString("Roll!");

	m_doneButton.setPosition({ BUTTON_POS_X, BUTTON_POS_Y });
	m_doneButton.setFillColor(sf::Color::White);
	m_doneButton.setFont(Textures::instance().getFont());
	m_doneButton.setCharacterSize(CHAR_SIZE);
	m_doneButton.setString("Done");

	m_rollResult.first.setSize({ DICE_SIZE,DICE_SIZE });
	m_rollResult.second.setSize({ DICE_SIZE,DICE_SIZE });
}

void Dice::draw(sf::RenderWindow& window)
{
	switch (m_state) {
	case ROLL:
		window.draw(m_rollButton);
		window.draw(m_rollResult.first);
		window.draw(m_rollResult.second);
		break;
	case ROLL_START:
		window.draw(m_rollButton);
		break;
	case DONE:
		window.draw(m_doneButton);
		window.draw(m_rollResult.first);
		window.draw(m_rollResult.second);
		break;
	default:
		window.draw(m_rollResult.first);
		window.draw(m_rollResult.second);
		break;
	}
}

void Dice::mousePassOnButton(sf::Vector2f mousePos)
{
	if(m_rollButton.getGlobalBounds().contains(mousePos))
		m_rollButton.setFillColor(sf::Color::Black);
	else
		m_rollButton.setFillColor(sf::Color::White);
}

std::pair<int, int> Dice::roll()
{
	std::pair<int, int> diceResult;
	diceResult.first = rand() % 6 + 1;
	diceResult.second = rand() % 6 + 1;
	m_rollResult.first.setTexture(&Textures::instance().getTexture(diceResult.first+1));
	m_rollResult.second.setTexture(&Textures::instance().getTexture(diceResult.second+1));

	//state will change in the turns functions
	switch (m_state) {
	case PLAY:
		m_rollResult.first.setPosition({ HOME_LEFT + DIFF * 3,BUTTON_POS_Y });
		m_rollResult.second.setPosition({ HOME_LEFT + DIFF * 3 + 50,  BUTTON_POS_Y });
		break;
	case AI_TURN:
		m_rollResult.first.setPosition({ LEFT_CORNER + DIFF * 3,BUTTON_POS_Y });
		m_rollResult.second.setPosition({ LEFT_CORNER + DIFF * 3 + 50,  BUTTON_POS_Y });
		break;
	case START:
		m_rollResult.first.setPosition({ HOME_LEFT,BUTTON_POS_Y });
		m_rollResult.second.setPosition({ LEFT_CORNER + DIFF * 5 ,  BUTTON_POS_Y });
	}
	return diceResult;
}

void Dice::setState(DICE_STATE new_state)
{
	m_state = new_state;
}

DICE_STATE Dice::getState() const
{
	return m_state;
}

bool Dice::isClickedOn(sf::Vector2f pos)
{
	switch (m_state) {
	case ROLL_START:
		return m_rollButton.getGlobalBounds().contains(pos);
	case ROLL:
		return m_rollButton.getGlobalBounds().contains(pos);
	case DONE:
		return m_doneButton.getGlobalBounds().contains(pos);
	}
}

void Dice::setDouble(bool is_double)
{
	m_isDouble = is_double;
}

bool Dice::isDouble() const
{
	return m_isDouble;
}

void Dice::updateResult(int played, std::pair<int, int>& result)
{
	if (played == result.first)
		result.first = 0;
	else
		result.second = 0;
}
