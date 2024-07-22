#include "TopBoard.h"
#include <Windows.h>

//print the score and player number
void TopBoard::printTopBoard()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 15);

	gotoxy(Board::RIGHT_F1 - 5 + startX, Board::TOP_F1 + 2);
	cout << "Score:" << score << endl;
	gotoxy(Board::RIGHT_F1 - 5 + startX, Board::TOP_F1 + 3);
	for (int i = 0; i < 10; i++)
		cout << "_";
	cout << endl;
	gotoxy(Board::LEFT_F1 - 8 + startX, Board::TOP_F1 + 2);
	if (startX == 9)
		cout << "  Player 1  " << endl;
	else
		cout << "  Player 2  " << endl;
	gotoxy(Board::LEFT_F1 - 8 + startX, Board::TOP_F1 + 3);
	for (int i = 0; i < 12; i++)
		cout << "_";
	cout << endl;




}