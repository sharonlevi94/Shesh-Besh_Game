#pragma once
#include "SFML/Graphics.hpp"
#include "Macros.h"

class Checker
{
public:
	Checker(PLAYER_COLOR, int, sf::Vector2f);
	void updatePos(const sf::Vector2f&, int, int);
	sf::Vector2f getPos()const;
	PLAYER_COLOR getColor()const;
	int getID()const;
	void draw(sf::RenderWindow&);
	bool isContainsClick(const sf::Vector2f&);

private:
	sf::CircleShape m_shape;
	PLAYER_COLOR m_color;
	int m_id;
};


