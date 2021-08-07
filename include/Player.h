#pragma once
#include "Character.h"
class Manager;
class Player: public Character
{
public:
	Player(PLAYER_COLOR=WHITE);
	virtual void play(Dice*, sf::RenderWindow&, Manager&)override;

private:
	
};


