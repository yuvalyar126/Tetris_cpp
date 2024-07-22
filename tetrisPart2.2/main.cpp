#include "Point.h"
#include "Board.h"
#include "GameConfig.h"
#include"Shape.h"
#include "TetrisGame.h"

#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;


int main()
{
	TetrisGame game;

	game.mainGameLoop	(); // Display the main menu

	gotoxy(0, 30);
}