#pragma once
#include "Character.h"
#include "Move.h"
#include <memory>

//-----------------------------------------------------------------------------

class Opponent: public Character
{
public:
	Opponent(PLAYER_COLOR=BLACK);
	virtual void play(Dice*, sf::RenderWindow&, Manager&)override;
	
private:
	std::vector<std::unique_ptr<Move>> m_sepMoves;
	std::vector<std::unique_ptr<Move>> m_seqMoves;

	void generateMoves(std::pair<int, int>, Manager*);
	void calcScores(std::vector<std::unique_ptr<Move>>&, Manager*);
	void calcScoresHome(Move*, Manager*, std::array<int, NUM_OF_POINTS>);
	void calcScoresOut(Move*, Manager*, std::array<int, NUM_OF_POINTS>);
	std::vector<Move*> chooseBestMove();
	bool isEatable(Manager*, int);
};




