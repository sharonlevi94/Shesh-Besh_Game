#pragma once
#include <utility>

class Move {
	public:
		Move(int, int);
		int getScore()const;
		void setScore(int);

		int getFrom()const;
		int getTo()const;

	private:
		int m_score = 0;
		std::pair<int, int> m_move;
};