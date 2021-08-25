#include "Opponent.h"
#include "Manager.h"
#include <array>
#include <algorithm>

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

void Opponent::play(Dice* dice, sf::RenderWindow& window, Manager& manager)
{
	std::pair<int, int> result = dice->roll();
	generateMoves(result, &manager);
	calcScores(m_sepMoves, &manager);
	calcScores(m_seqMoves, &manager);
	std::vector<Move*> chosenMoves = chooseBestMove();

	for (auto& move : chosenMoves) 
		manager.updateBoard(move->getFrom(), move->getTo(), BLACK);

	dice->setState(ROLL);
	m_sepMoves.clear();
	m_seqMoves.clear();
}

//-----------------------------------------------------------------------------

void Opponent::generateMoves(std::pair<int, int> result, Manager* manager) {
	bool both = false;
	for (int i = 0; i < NUM_OF_POINTS; i++) 
		if (manager->getPoint(i)->getColor() == BLACK) {
			if (manager->isMovePossible(i, i + result.first, LEFT)) {
				m_sepMoves.push_back(std::make_unique<Move>(i, i + result.first));
				if (manager->isMovePossible(i + result.first, i + result.first + result.second, LEFT))
					both = true;
			}

			if (manager->isMovePossible(i, i + result.second, LEFT)) {
				m_sepMoves.push_back(std::make_unique<Move>(i, i + result.second));
				if (manager->isMovePossible(i + result.second, i + result.first + result.second, LEFT))
					both = true;
			}

			if (both) {
				m_seqMoves.push_back(std::make_unique<Move>(i, i + result.first + result.second));
				both = false;
			}
		}
}

//-----------------------------------------------------------------------------

void Opponent::calcScores(std::vector<std::unique_ptr<Move>>& moves, Manager* manager)
{
	std::array<int, NUM_OF_POINTS> checkersMovedTo = {};
	std::fill(checkersMovedTo.begin(), checkersMovedTo.end(), 0);

	for (auto& move : moves) 
		checkersMovedTo[move->getTo()]++;
	
	for (auto& move : moves) 
		if (move->getTo() >= AI_HOME) 
			calcScoresHome(move.get(), manager, checkersMovedTo);
		else 
			calcScoresOut(move.get(), manager, checkersMovedTo);
}

//-----------------------------------------------------------------------------

void Opponent::calcScoresHome(Move* move, Manager* manager, 
	std::array<int, NUM_OF_POINTS> checkersMovedTo)
{
	if (manager->getPoint(move->getTo())->getColor() == WHITE) {
		if (checkersMovedTo[move->getTo()] == BLOCK)
			move->setScore(EAT_BLOCK_HOME);
		else
			move->setScore(EAT_HOME);
	}
	else {
		if (manager->getPoint(move->getTo())->getCheckersNumber() >= BLOCK)
			move->setScore(EBLOCK_HOME);
		else {
			if (manager->getPoint(move->getTo())->getColor() == BLACK)
				move->setScore(NBLOCK_HOME);
			else {
				if (checkersMovedTo[move->getTo()] == BLOCK)
					move->setScore(NBLOCK_HOME);
				else if (isEatable(manager, move->getTo()))
					move->setScore(OPEN_HOME_NOT_FREE);
				else
					move->setScore(OPEN_FREE_HOME);
			}
		}
	}
}

//-----------------------------------------------------------------------------

void Opponent::calcScoresOut(Move* move, Manager* manager, 
	std::array<int, NUM_OF_POINTS> checkersMovedTo)
{
	if (manager->getPoint(move->getTo())->getColor() == WHITE) {
		if (checkersMovedTo[move->getTo()] == BLOCK)
			move->setScore(EAT_BLOCK_OUT);
		else if (isEatable(manager, move->getTo()))
			move->setScore(EAT_OUT_NOT_FREE);
		else
			move->setScore(EAT_OUT_FREE);
	}
	else {
		if (manager->getPoint(move->getTo())->getCheckersNumber() >= BLOCK)
			move->setScore(EBLOCK_OUT);
		else {
			if (manager->getPoint(move->getTo())->getColor() == BLACK)
				move->setScore(NBLOCK_OUT);
			else {
				if (checkersMovedTo[move->getTo()] == BLOCK)
					move->setScore(NBLOCK_OUT);
				else if (isEatable(manager, move->getTo()))
					move->setScore(OPEN_OUT_NOT_FREE);
				else
					move->setScore(OPEN_FREE_OUT);
			}
		}
	}
}

//-----------------------------------------------------------------------------

std::vector<Move*> Opponent::chooseBestMove()
{
	std::vector<Move*> bestMoves;
	Move* maxSeqScoreMove = m_seqMoves[0].get(),
		* maxSepScoreMove = m_sepMoves[0].get(),
		* secMaxSepScoremove = m_sepMoves[0].get();

	for (auto& seqMove : m_seqMoves)
		if (seqMove->getScore() > maxSeqScoreMove->getScore())
			maxSeqScoreMove = seqMove.get();

	for (auto& sepMove : m_sepMoves)
		if (sepMove->getScore() > maxSepScoreMove->getScore()) {
			secMaxSepScoremove = maxSepScoreMove;
			maxSepScoreMove = sepMove.get();
		}

	if (maxSeqScoreMove->getScore() > maxSepScoreMove->getScore() + secMaxSepScoremove->getScore())
		bestMoves.push_back(maxSeqScoreMove);
	else {
		bestMoves.push_back(maxSepScoreMove);
		bestMoves.push_back(secMaxSepScoremove);
	}
	return bestMoves;
}

//-----------------------------------------------------------------------------

bool Opponent::isEatable(Manager* manager, int point_i)
{
	float prob = 0;
	int i = point_i + 1;

	while (i < NUM_OF_POINTS && i < i + NUM_OF_OPTIONS) {
		switch (i)
		{
		default:
			break;
		}
	}

	if(prob > PROB_LIMIT)
		return true;
	return false;
}
