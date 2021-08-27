#include "Dice.h"
#include "Macros.h"
#include "Textures.h"
#include "Music.h"

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

void Dice::mousePassOnButton(sf::Vector2f mousePos)
{
	if(m_rollButton.getGlobalBounds().contains(mousePos))
		m_rollButton.setFillColor(sf::Color::Black);
	else
		m_rollButton.setFillColor(sf::Color::White);
}

//-----------------------------------------------------------------------------

void Dice::roll()
{
	Music::instance().playSound(ROLL_SOUND);

	m_numsResult.first = rand() % 6 + 1;
	m_numsResult.second = rand() % 6 + 1;
	m_rollResult.first.setTexture(&Textures::instance().getTexture(m_numsResult.first+1));
	m_rollResult.second.setTexture(&Textures::instance().getTexture(m_numsResult.second+1));

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
}

//-----------------------------------------------------------------------------

void Dice::setState(DICE_STATE new_state)
{
	m_state = new_state;
}

//-----------------------------------------------------------------------------

DICE_STATE Dice::getState() const
{
	return m_state;
}

std::pair<int, int> Dice::getResult() const
{
	return m_numsResult;
}

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

void Dice::setDouble(bool is_double)
{
	m_isDouble = is_double;
	m_doubleValue = m_numsResult.first;
}

//-----------------------------------------------------------------------------

bool Dice::isDouble() const
{
	return m_isDouble;
}

//-----------------------------------------------------------------------------

void Dice::updateResult(int played)
{
	if (played > 6) {
		m_numsResult.first = 0;
		m_numsResult.second = 0;
	}
	else {
		if (played == m_numsResult.first)
			m_numsResult.first = 0;
		else
			m_numsResult.second = 0;
	}
}

void Dice::resetResult()
{
	m_isDouble = false;
	m_numsResult.first = m_doubleValue;
	m_numsResult.second = m_doubleValue;
}
