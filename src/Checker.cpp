#include "Checker.h"
#include "Textures.h"
//-----------------------------------------------------------------------------
Checker::Checker(PLAYER_COLOR color, int id, sf::Vector2f position = { 0,0 })
	:m_id(id)
{
	m_shape.setRadius(RADIUS);
	m_shape.setPosition(position);
	m_shape.setTexture(&Textures::instance().getTexture(color));
}
//-----------------------------------------------------------------------------
void Checker::updatePos(const sf::Vector2f& pos,int checkersNum, int loc)
{
	if (loc >= 0 && loc <= 11)
		m_shape.setPosition(sf::Vector2f{pos.x, pos.y - checkersNum *RADIUS*2});
	else
		m_shape.setPosition(sf::Vector2f{ pos.x, pos.y + checkersNum * RADIUS * 2 });
}
//-----------------------------------------------------------------------------
int Checker::getID() const
{
	return m_id;
}
//-----------------------------------------------------------------------------
void Checker::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}
