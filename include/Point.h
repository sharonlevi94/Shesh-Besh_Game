#pragma once
#include <vector>
#include "Checker.h"

class Point
{
public:
	Point(const sf::Vector2f&,const sf::Vector2f&);
	void add(Checker*);
	void del(Checker*);
	void draw(sf::RenderWindow&);

	int getCheckersNumber()const;
	sf::Vector2f getPosition()const;
	sf::FloatRect getBounds()const;
	Checker* getChecker(int)const;

	void setColor(PLAYER_COLOR);
	PLAYER_COLOR getColor()const;

private:
	sf::Vector2f m_position;
	sf::RectangleShape m_bounds;
	std::vector<Checker*> m_checkers;
	PLAYER_COLOR m_color;
};


