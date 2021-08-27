#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "Textures.h"

class Dice
{
public:
	Dice();
	void draw(sf::RenderWindow&);
	void mousePassOnButton(sf::Vector2f);
	void roll();
	bool isClickedOn(sf::Vector2f);
	bool isDouble()const;
	void updateResult(int);
	void resetResult();

	void setState(DICE_STATE);
	void setDouble(bool);

	DICE_STATE getState()const;
	std::pair<int, int> getResult()const;

private:
	std::pair<sf::RectangleShape, sf::RectangleShape> m_rollResult;
	std::pair<int, int> m_numsResult;
	sf::Text m_rollButton;
	sf::Text m_doneButton;
	DICE_STATE m_state;
	bool m_isDouble = false;
	int m_doubleValue;
};


