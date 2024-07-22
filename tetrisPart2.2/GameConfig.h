#pragma once
#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

void gotoxy(int x, int y);
void clrscr();



class GameConfig {
public:
	static char constexpr EmptyPoint = ' ';
	static int constexpr ShapeSize = 4;
	static int constexpr Player1StartX = 10;
	static int constexpr Player1StartY = 5;
	static int constexpr whiteColor = 15;

	static int constexpr Player2StartX = 40;
	static int constexpr Player2StartY = 5;

	enum eKeys { LEFT = 'a', LEFT_CAP = 'A', RIGHT = 'd', RIGHT_CAP = 'D', HARD_DOWN = 'x', HARD_DOWN_CAP = 'X', ROTATE_CW = 'w', ROTATE_CW_CAP = 'W', ROTATE_CCW = 's', ROTATE_CCW_CAP = 'S', ESC = 27 };
	enum eKeys2 { LEFT2 = 'j', LEFT_CAP2 = 'J', RIGHT2 = 'l', RIGHT_CAP2 = 'L', HARD_DOWN2 = 'm', HARD_DOWN_CAP2 = 'M', ROTATE_CW2 = 'i', ROTATE_CW_CAP2 = 'I', ROTATE_CCW2 = 'k', ROTATE_CCW_CAP2 = 'K'
	};

	enum eShapes { L_Shape = 0, J_Shape = 1, S_Shape = 2, Z_Shape = 3, I_Shape = 4, T_Shape = 5, O_Shape = 6, NUM_SHAPES = 7 };

	enum { rand = 7 };

	enum { player1 = 0, player2 = 30 };

	enum speed { SLOW = 500, NORMAL = 220, FAST = 150, EXTREME = 100 }; 

	enum menuKeys { START_NEW_GAME = '1', PAUSE = 27, CONTINUE = '2', INSTRUCTIONS = '8', EXIT = '9' };
};