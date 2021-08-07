#pragma once
/*============================================================================
* Class: Manager.
* This class manage the game. handle all the cases that happen in the game.
* it connect between all the classes in the project.
* it can load the levels, play the turns,handle colisions
* and draw the objects of the game.*/
 //============================ include section ===============================
#include <vector>
#include "Point.h"
#include "Player.h"
#include "Opponent.h"
#include "Dice.h"

class Manager {
public:
	Manager();
	void run();
	void draw();
	int getPointContainsClick(const sf::Vector2f&);
	Point* getPoint(int)const;
	void moveChecker(int, std::pair<int, int>&, DIRECTION);
	//========================= private section ==============================
private:
	sf::RenderWindow m_window;
	sf::Clock m_gameClock;
	sf::RectangleShape m_background;
	std::vector <std::unique_ptr<Point>> m_points;
	Player m_player;
	Opponent m_AI;
	Dice m_dice;
	//====================== private methods section =========================
	const sf::Texture& runBoardScreen();
	void initializeBoard();
	void setPoints();
	void setCheckers();
	void setPlayerCheckers();
	void setAICheckers();
	bool isMovePossible(int, int, DIRECTION);
	void movePlayer(int, int);
	void moveAI(int, int);
	void eatChecker(Checker*);
};