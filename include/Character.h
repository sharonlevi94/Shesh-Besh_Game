#pragma once
#include "Checker.h"
#include <memory>
#include <vector>
#include "Macros.h"
#include "Dice.h"
class Manager;
class Character
{
public:
	Character(PLAYER_COLOR, DIRECTION);
	virtual void play(Dice*, sf::RenderWindow&, Manager&)=0;
	void addChecker(int, sf::Vector2f);
	void drawCheckers(sf::RenderWindow&);

	Checker* getChecker(int)const;
	PLAYER_COLOR getColor()const;

private:
	std::vector<std::unique_ptr<Checker>> m_checkers;
	PLAYER_COLOR m_color;
	DIRECTION m_direction;
};


