#include "Board.h"
#include"GameConfig.h"

Board::Board(bool isPlayer1)
{
	this->isPlayer1 = isPlayer1;
	int startX;
	if (isPlayer1)
		startX = START_X1;
	
	else
		startX = START_X2;
	topB = new TopBoard(startX);
	resetBoard();
}


void Board::printFrame() const
{
	int startX;
	if (isPlayer1)
	{
		startX = START_X1;
	}
	else
		startX = START_X2;
	for (int col = startX + 1; col < startX + COLS + 1; col++)
	{
		gotoxy(col, START_Y);
		cout << "*";

		gotoxy(col, START_Y + GameFrame::LENGTH - 1);
		cout << "*";
	}

	for (int row = START_Y; row < START_Y + GameFrame::LENGTH; row++)
	{
		gotoxy(startX, row);
		cout << "|";

		gotoxy(startX + GameFrame::WIDTH - 1, row);
		cout << "|";
	}
	
	topB->printTopBoard();
}

//resets the board to default
void Board::resetBoard() {
	for (int x = 0; x < COLS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			boardGame[x][y].setPoint(x, y, GameConfig::EmptyPoint, GameConfig::whiteColor);
		}
	}
	topB->resetscore();
}

//checks if the point is in the board
bool Board::isInBoard(int x, int y) const {
	return(x >= 0 && x < COLS && y >= 0 && y < ROWS);
}


//checks if the shape can move in the direction
bool Board::canShapeMove(GameConfig::eKeys direction, const Shape* s) const
{
	switch (direction)
	{
	case GameConfig::LEFT:
	case GameConfig::LEFT2:
	case GameConfig::LEFT_CAP:
	case GameConfig::LEFT_CAP2:
		return canMoveToSetOff(s->getShapeArr(), -1, 0);
		break;
	case GameConfig::RIGHT:
	case GameConfig::RIGHT2:
	case GameConfig::RIGHT_CAP:
	case GameConfig::RIGHT_CAP2:
		return canMoveToSetOff(s->getShapeArr(), 1, 0);
		break;
	case GameConfig::HARD_DOWN:
	case GameConfig::HARD_DOWN2:
	case GameConfig::HARD_DOWN_CAP:
	case GameConfig::HARD_DOWN_CAP2:
		return canMoveToSetOff(s->getShapeArr(), 0, 2);
		break;
	case GameConfig::ROTATE_CW:
	case GameConfig::ROTATE_CW2:
	case GameConfig::ROTATE_CW_CAP:
	case GameConfig::ROTATE_CW_CAP2:
		return canRotateCW(s);
		break;
	case GameConfig::ROTATE_CCW:
	case GameConfig::ROTATE_CCW2:
	case GameConfig::ROTATE_CCW_CAP:
	case GameConfig::ROTATE_CCW_CAP2:
		return canRotateCCW(s);
		break;
	default:
		break;
	}
}

//checks if the shape can rotete in the clockwise
bool Board::canRotateCW(const Shape* s) const
{
	Shape copiedShape(*s);
	copiedShape.rotateCW();
	return canMoveToSetOff(copiedShape.getShapeArr(), 0, 0);//sending the shape with set of 0,0(rotated shape shape)
}

bool Board::canRotateCCW(const Shape* s) const
{
	Shape copiedShape(*s);
	copiedShape.rotateCCW();
	return canMoveToSetOff(copiedShape.getShapeArr(), 0, 0);//sending the shape with set of 0,0(rotated shape shape)
}

// Checks if a shape can be moved to a new position
bool Board::canMoveToSetOff(const Point* pointsArr, int setOffX, int setOffY) const
{
	for (int i = 0; i < GameConfig::ShapeSize; i++) {
		int x = pointsArr[i].getX() + setOffX;
		int y = pointsArr[i].getY() + setOffY;

		if (boardGame[x][y].getSign() != ' ' || !isInBoard(x, y)) 
		{
			return false;
		}
	}
	return true;
}




bool Board::canMoveDown(const Point* pointsArr) const
{
	for (int i = 0; i < GameConfig::ShapeSize; i++) {
		int x = pointsArr[i].getX();
		int y = pointsArr[i].getY() + 1;

		if (isCellOccupied(x, y) || !isInBoard(x, y)) 
		{
			return false;
		}
	}
	return true;
}

bool Board::isFullRow(int row) const
{
	for (int col = 0; col < COLS; col++)
	{
		if (boardGame[col][row].getSign() == ' ')
			return false;
	}
	return true;
}

void Board::checkFullRow() 
{
	for (int row = ROWS - 1; row > 0; row--)
	{
		if (isFullRow(row) == true)
		{
			eraseRow(row, isPlayer1);
		}
	}
}


//erases a row and moves all the rows above it down
void Board::eraseRow(int rowToErase, bool isPlayer1)
{
	for (int curRow = rowToErase; curRow > 0; curRow--)
	{
		for (int col = 0; col < COLS; col++)
		{
			boardGame[col][curRow].erase(isPlayer1);
			boardGame[col][curRow].setSign(boardGame[col][curRow - 1].getSign());
			boardGame[col][curRow].setColor(boardGame[col][curRow - 1].getColor());
			boardGame[col][curRow].draw(isPlayer1);

		}
	}
	topB->updateScore(SCORE::SINGLE_LINE);
}


//adds the shape to the board	
void Board::addShapeToBoard(const Shape* s)
{
	const Point* pointsArr = s->getShapeArr();
	int color = s->getColor();
	for (int i = 0; i < GameConfig::ShapeSize; i++) {
		int x = pointsArr[i].getX();
		int y = pointsArr[i].getY();
		boardGame[x][y].setPoint(x, y, '#', color);
	}
}

//checks if the cell is occupied
bool Board::isCellOccupied(int x, int y) const
{
	return boardGame[x][y].getSign() != ' ';
}

void Board::printBoard() const//prints board's points
{
	this->printFrame();
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			boardGame[i][j].draw(isPlayer1);
		}
	}
}
void Board::updateScoreBoard(int addScore)
{
	topB->updateScore(addScore);
	topB->printTopBoard();
}

int Board::getScore() {
	return topB->getScore();
}

//function that resume the game after pause
void Board::resume()
{
	printBoard();
	topB->printTopBoard();
}