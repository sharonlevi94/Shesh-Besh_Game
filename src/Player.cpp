#include "Player.h"
#include "Manager.h"

Player::Player(PLAYER_COLOR color)
	:Character(color, RIGHT)
{
	int id = 0;
	for (int i = 0; i < 5; i++) 
		addChecker(id++, sf::Vector2f(HOME_LEFT, BOTTOM - i * RADIUS * 2));
	for (int i = 0; i < 3; i++) 
		addChecker(id++, sf::Vector2f(LEFT_CORNER+DIFF*4, BOTTOM - i * RADIUS * 2));
	for (int i = 0; i < 5; i++) 
		addChecker(id++, sf::Vector2f(LEFT_CORNER, TOP + i * RADIUS * 2));
	for (int i = 0; i < 2; i++)
		addChecker(id++, sf::Vector2f(RIGHT_CORNER, TOP + i * RADIUS * 2));

}

void Player::play(Dice* dice, sf::RenderWindow& window, Manager& manager)
{
	int diceValue=0;
	dice->setState(PLAY);
	std::pair<int, int> diceResult = dice->roll();
	if (diceResult.first == diceResult.second) {
		dice->setDouble(true);
		diceValue = diceResult.first;
	}
	
	while (dice->getState() == PLAY) {
		for (auto event = sf::Event{}; window.waitEvent(event);) {
			window.clear();
			manager.draw();
			window.display();
			if (event.type == sf::Event::MouseButtonPressed) {
				int pointClicked = manager.getPointContainsClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
				if (pointClicked != NO_POINT_CLICKED) {
					if (diceResult.first > 0 || diceResult.second > 0)
						manager.movePlayer(pointClicked, diceResult);
					if (diceResult.first == 0 && diceResult.second == 0) {
						if (dice->isDouble()) {
							dice->setDouble(false);
							diceResult.first = diceValue;
							diceResult.second = diceValue;
						}
						else {
							dice->setState(ROLL);
							break;
						}
					}
				}
			}
		}
	}
}
