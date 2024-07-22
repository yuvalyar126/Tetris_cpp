#include "Point.h"

//set the point to the given values
void Point::setPoint(int _x, int _y, char ch = '#', int _color = GameConfig::whiteColor)
{
	x = _x;
	y = _y;
	this->ch = ch;
	color = _color;
}

//erase the point
void Point::erase(bool isPlayer1) const
{
	if (isPlayer1)
	{
		gotoxy(GameConfig::Player1StartX + x, GameConfig::Player1StartY + y);
	}
	else
	{
		gotoxy(GameConfig::Player2StartX + x, GameConfig::Player2StartY + y);

	}
	cout << GameConfig::EmptyPoint << endl;

}

//draw the point
void Point::draw(bool isPlayer1) const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	if (isPlayer1)
	{
		gotoxy(GameConfig::Player1StartX + x, GameConfig::Player1StartY + y);
	}
	else
	{
		gotoxy(GameConfig::Player2StartX + x, GameConfig::Player2StartY + y);

	}
	cout << ch << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::whiteColor); //reset color to default

}

