#include "Point.h"
#include <iostream>

//-----------------------------------------------------------------------------
Point::Point(const sf::Vector2f& position,const sf::Vector2f& bounds_pos)
{
	m_checkers.clear();
	m_bounds.setSize({ POINT_AREA_X, POINT_AREA_Y });
	m_bounds.setPosition(bounds_pos);
	m_position = position;
	setColor(NO_COLOR);
}
//-----------------------------------------------------------------------------
void Point::add(Checker* newCheckerPtr)
{
	m_checkers.push_back(newCheckerPtr);
}
//-----------------------------------------------------------------------------
void Point::del(Checker* wanted_checker)
{
	for (int i = 0; i < m_checkers.size(); i++)
		if (m_checkers[i]->getID() == wanted_checker->getID()) {
			m_checkers.erase(m_checkers.begin() + i);
			break;
		}
}
//-----------------------------------------------------------------------------
void Point::draw(sf::RenderWindow& window)
{
	for (auto& checker : m_checkers)
		checker->draw(window);
}
//-----------------------------------------------------------------------------
int Point::getCheckersNumber() const
{
	return int(m_checkers.size());
}
//-----------------------------------------------------------------------------
sf::Vector2f Point::getPosition() const
{
	return m_position;
}
//-----------------------------------------------------------------------------
sf::FloatRect Point::getBounds() const
{
	return m_bounds.getGlobalBounds();
}
Checker* Point::getChecker(int i) const
{
	return m_checkers[i];
}
//-----------------------------------------------------------------------------
void Point::setColor(PLAYER_COLOR color)
{
	m_color = color;
}
//-----------------------------------------------------------------------------
PLAYER_COLOR Point::getColor() const
{
	return m_color;
}
