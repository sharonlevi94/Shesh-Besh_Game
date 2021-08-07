#pragma once
#include "Character.h"

class Opponent: public Character
{
public:
	Opponent(PLAYER_COLOR=BLACK);
	virtual void play(Dice*, sf::RenderWindow&, Manager&)override;

private:

};




