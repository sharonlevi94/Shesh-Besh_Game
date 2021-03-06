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
	virtual bool allPassed(Manager*)override;
	
private:
	std::vector<std::unique_ptr<Move>> m_sepMoves;
	std::vector<std::unique_ptr<Move>> m_seqMoves;

	void generateMoves(const std::pair<int, int>&, Manager*);
	void calcScores(std::vector<std::unique_ptr<Move>>&, Manager*);
	void calcScoresHome(Move*, Manager*, std::array<int, NUM_OF_POINTS>);
	void calcScoresOut(Move*, Manager*, std::array<int, NUM_OF_POINTS>);
	std::vector<Move*> chooseBestMove(const std::pair<int, int>&);
	bool isEatable(Manager*, int);
	std::pair<Move*, Move*> findBestSepMoves(const std::pair<int, int>&);
};




