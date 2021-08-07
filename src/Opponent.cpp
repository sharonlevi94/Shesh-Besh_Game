#include "Opponent.h"

Opponent::Opponent(PLAYER_COLOR color) 
	:Character(color, LEFT)
{
	int id = 0;
	for (int i = 0; i < 5; i++) 
		addChecker(id++, sf::Vector2f(HOME_LEFT, TOP + i * RADIUS * 2));
	for (int i = 0; i < 3; i++) 
		addChecker(id++, sf::Vector2f(LEFT_CORNER + DIFF * 4, TOP + i * RADIUS * 2));
	for (int i = 0; i < 5; i++) 
		addChecker(id++, sf::Vector2f(LEFT_CORNER, BOTTOM - i * RADIUS * 2));
	for (int i = 0; i < 2; i++)
		addChecker(id++, sf::Vector2f(RIGHT_CORNER, BOTTOM - i * RADIUS * 2));
}

void Opponent::play(Dice* dice, sf::RenderWindow& window, Manager& manager)
{
}
