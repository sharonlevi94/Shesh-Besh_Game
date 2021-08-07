#include "Character.h"

Character::Character(PLAYER_COLOR color, DIRECTION direction)
	: m_color(color), m_direction(direction){}

void Character::addChecker(int id, sf::Vector2f position)
{
	m_checkers.push_back(std::make_unique<Checker>(m_color, id, position));
}

Checker* Character::getChecker(int i) const
{
	return m_checkers[i].get();
}

PLAYER_COLOR Character::getColor() const
{
	return m_color;
}

void Character::drawCheckers(sf::RenderWindow& window)
{
	for (auto& checker : m_checkers)
		checker.get()->draw(window);
}
