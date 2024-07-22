#pragma once
#include "Board.h"
#include "Point.h"
#include "GameConfig.h"
#include <Windows.h>
#include <conio.h>
using namespace std;
enum GameState { MENU, RUNNING, PAUSED, ENDED, NEW_GAME };
enum { NO_COLOR = false, COLOR = true };
enum { player1 = true, player2 = false };

class TetrisGame {
	Board _p1Board;
	Board _p2Board;
	GameState currentState = MENU;
	bool mode = COLOR;
	void run();
public:


	TetrisGame() : _p1Board(player1), _p2Board(player2) {};

	void showInstructions()const;
	void mainGameLoop();
	void displayMainMenu();
	void displayPauseMenu();
	bool checkGameOver(Board& board) const;
	bool isPlayer1Key(char key) const;
	bool isPlayer2Key(char key) const;
	void HandleGameOver();
	void  displayGameOverMessage(int winner, int score1, int score2) const;
	void updateRecordDisplay(int player, int newRecord) const;
	void hideCursor() const;
};