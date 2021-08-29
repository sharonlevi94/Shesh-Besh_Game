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
	dice->setState(PLAY);
	dice->roll();
	if (dice->getResult().first == dice->getResult().second)
		dice->setDouble(true);
	
	while (dice->getState() == PLAY) {
		for (auto event = sf::Event{}; window.waitEvent(event);) {
			window.clear();
			manager.draw();
			window.display();
			if (event.type == sf::Event::MouseButtonPressed) {
				int pointClicked = manager.getPointContainsClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
				if (pointClicked != NO_POINT_CLICKED) {
					if (dice->getResult().first > 0 || dice->getResult().second > 0)
						manager.movePlayer(pointClicked, dice->getResult());
					if (dice->getResult().first == 0 && dice->getResult().second == 0) {
						if (dice->isDouble()) 
							dice->resetResult();
						else {
							dice->setState(DONE);
							break;
						}
					}
				}
			}
		}
	}
}

bool Player::allPassed(Manager* manager)
{
	int num_of_chckrs_in_home = 0;
	for (int i = 0; i <= PLAYER_HOME; i++) 
		num_of_chckrs_in_home += manager->getPoint(i)->getCheckersNumber();
	
	if (num_of_chckrs_in_home == getNumChkrsLeft())
		return true;
	return false;
}
