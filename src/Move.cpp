#include "Move.h"

Move::Move(int from, int to) {
	m_move.first = from;
	m_move.second = to;
}

//------------------------------------

int Move::getScore()const { return m_score; }

//------------------------------------

void Move::setScore(int score) {
	m_score = score;
}

//------------------------------------

int Move::getFrom() const
{
	return m_move.first;
}
//------------------------------------

int Move::getTo() const
{
	return m_move.second;
}
//------------------------------------

