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
	std::pair<int, int> roll();
	void setState(DICE_STATE);
	DICE_STATE getState()const;
	bool isClickedOn(sf::Vector2f);
	void setDouble(bool);
	bool isDouble()const;
	void updateResult(int, std::pair<int, int>&);

private:
	std::pair<sf::RectangleShape, sf::RectangleShape> m_rollResult;
	sf::Text m_rollButton;
	sf::Text m_doneButton;
	DICE_STATE m_state;
	bool m_isDouble=false;
};


