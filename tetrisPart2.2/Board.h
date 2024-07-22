#pragma once
#include "TopBoard.h"
#include "Point.h"
#include "Shape.h"


enum { ROWS = 18, COLS = 12 };
enum { START_X1 = 9, START_X2 = 39, START_Y = 1 };
class TopBoard;

class Board {
	Point boardGame[COLS][ROWS];
	TopBoard* topB;
	bool isPlayer1;// Member variable to represent the current player

	bool isInBoard(int x, int y) const;

public:
	enum GameZone { LEFT1 = 10, RIGHT1 = 21, TOP1 = 5, BOTTOM1 = 22 }; //  only the game zone area
	enum menuFrame { LEFT_F1 = GameZone::LEFT1 - 1, RIGHT_F1 = GameZone::RIGHT1 + 1, TOP_F1 = GameZone::TOP1 - 4, BOTTOM_F1 = GameZone::BOTTOM1 + 1 };
	enum GameFrame { WIDTH = 14, LENGTH = 23 };

	Board(bool isPlayer1); // ctr 
	~Board() { delete topB; } // dtr


	bool canShapeMove(GameConfig::eKeys direction, const Shape* s) const;
	bool canMoveDown(const Point* pointsArr) const;

	bool canMoveToSetOff(const Point* pointsArr, int setOffX, int setOffY) const;

	bool canRotateCW(const Shape* s) const;
	bool canRotateCCW(const Shape* s) const;

	bool isCellOccupied(int x, int y) const;
	////////////row deletion
	bool isFullRow(int row) const;// checks if a row on boared is full
	void checkFullRow() ;
	void eraseRow(int rowToErase, bool isPlayer1);
	///////////////////////////////////
	void addShapeToBoard(const Shape* s);
	void printBoard() const;


	void printFrame() const;

	void resetBoard();

	int getScore();

	void updateScoreBoard(int addScore);

	void resume();
};


