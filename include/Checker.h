#pragma once
#include "SFML/Graphics.hpp"
#include "Macros.h"

class Checker
{
public:
	Checker(PLAYER_COLOR, int, sf::Vector2f);
	void updatePos(const sf::Vector2f&, int, int);
	int getID()const;
	void draw(sf::RenderWindow&);

private:
	sf::CircleShape m_shape;
	int m_id;
};


