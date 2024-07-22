#pragma once
#include "Point.h"
#include "Board.h"

enum SCORE { SOFT_DROP = 1, HARD_DROP = 2, SINGLE_LINE = 100, DOUBLE_LINE = 300, TRIPLE_LINE = 500 };

class TopBoard {
	//Data members
	int score;
	int startX;

public:

	void resetTopBoard() {
		 score = 0; printTopBoard();
	}

	int getScore() { return score; }

	TopBoard(int playerNumber) :  score(0), startX(playerNumber) {
		printTopBoard();
	};

	void updateScore(int addScore) {
		score += addScore;
		printTopBoard();
	}

	void printTopBoard();

	void resetscore() { score = 0; }

};