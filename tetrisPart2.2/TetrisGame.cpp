#include "tetrisgame.h"
#include "board.h"
#include "shape.h"






void TetrisGame::mainGameLoop()
{

	while (true)
	{
		switch (currentState) 
		{
		case NEW_GAME:
		case MENU:
			displayMainMenu();
			break;

		case ENDED:
			return;
		}
	}
}




void TetrisGame::displayPauseMenu()
{
	system("cls"); // Clear the screen
	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2);
	cout << "Press (1) to go back to MAIN MENU" << endl;

	if (currentState == PAUSED) {
		gotoxy(Board::RIGHT_F1 + 3, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 1);
		cout << "Press (2) to RESUME" << endl;
	}
	gotoxy(Board::RIGHT_F1 + 3, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 2);
	cout << "                          " << endl;

	gotoxy(Board::RIGHT_F1 + 3, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 4);
	cout << "Press (8) for INSTRUCTIONS" << endl;
	gotoxy(Board::RIGHT_F1 + 3, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 5);
	cout << "Press (9) to EXIT" << endl;

	char choice = _getch();

	switch (choice)
	{
	case '1':
		system("cls"); // Clear the menu
		currentState = NEW_GAME;
		this->_p1Board.resetBoard();
		this->_p2Board.resetBoard();
		break;
	case '2':
		system("cls");
		currentState = RUNNING; // Continue paused game
		this->_p1Board.resume();
		this->_p2Board.resume();

		break;
	case '8':
		// Display instructions
		showInstructions();
		break;
	case '9':
		currentState = ENDED;
		break;
	default:
		// If an invalid key is pressed, show the menu again
		displayPauseMenu();
		break;
	}


}



// Display the main menu
void TetrisGame::displayMainMenu()
{
	system("cls"); // Clear the screen
	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2);
	cout << "Press (1) to START A NEW GAME" << endl;

	gotoxy(Board::RIGHT_F1 + 3, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 2);

	if (mode == COLOR)
		cout << "Press (3) to switch COLOR modes: ON " << endl;
	else
		cout << "Press (3) to switch COLOR modes: OFF " << endl;

	gotoxy(Board::RIGHT_F1 + 3, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 4);
	cout << "Press (8) for INSTRUCTIONS" << endl;
	gotoxy(Board::RIGHT_F1 + 3, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 5);
	cout << "Press (9) to EXIT" << endl;

	/*char choice = _getch();*/
	
		char choice = _getch();
		switch (choice)
		{
		case '1':
			system("cls"); // Clear the menu
			currentState = RUNNING; // Start a new game
			run();
			return;
			break;
		case '3':  // toggling color mode

			if (mode == COLOR)
			{
				gotoxy(Board::RIGHT_F1 + 5, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 2);
				cout << "Press (3) to switch COLOR modes: OFF " << endl;
				mode = NO_COLOR;
			}
			else
			{
				gotoxy(Board::RIGHT_F1 + 5, ((Board::BOTTOM_F1 + Board::TOP_F1) / 2) + 2);
				cout << "Press (3) to switch COLOR modes: ON " << endl;
				mode = COLOR;
			}

			break;
		case '8':
			// Display instructions
			showInstructions();
			break;
		case '9':
			currentState=ENDED;

			break;
		default:
			break;
		}
	}



void TetrisGame::showInstructions() const
{
	cout << "Game Instructions:\nIn Tetris, strategically place shapes to complete horizontal lines and score points.Each completed line grants 100 points.Be careful : if blocks reach the top, you lose.\n " << endl;
	cout << "Player 1 Controls:\nLeft: a or A\nRight: d or D\nRotate Clockwise: s or S\nRotate Counter-Clockwise: w or W\nHard Drop: x or X\nPause: ESC\n" << endl;
	cout << "Player 2 Controls:\nLeft: j or J\nRight:  l or L\nRotate Clockwise: i or I\nRotate Counter-Clockwise: k or K\nHard Drop: m or M\nPause: ESC\n" << endl;
	cout << "Press any key to return to menu..." << endl;
	_getch();
}


// Run the game
void TetrisGame::run()
{

	std::srand(static_cast<unsigned>(std::time(nullptr)));
	bool gameOver = false;
	system("cls");

	if (currentState == RUNNING)
	{

		_p1Board.printFrame();
		_p2Board.printFrame();
		int randObj1 = rand() % GameConfig::eShapes::NUM_SHAPES;
		int randObj2 = rand() % GameConfig::eShapes::NUM_SHAPES;

		Shape* pCurrP1Shape = new Shape((GameConfig::eShapes)randObj1, 0, player1, mode);
		pCurrP1Shape->drawOnScreen();

		Shape* pCurrP2Shape = new Shape((GameConfig::eShapes)randObj1, 0, player2, mode);
		pCurrP2Shape->drawOnScreen();



		while (!gameOver)
		{
			if ((checkGameOver(_p1Board) || checkGameOver(_p2Board)))
			{
				system("cls");
				HandleGameOver();
				gameOver = true;
				currentState = NEW_GAME;
				return;
			}


			hideCursor();
			if (_kbhit())
			{
				char keyPressed = _getch();

				if (keyPressed == (int)GameConfig::eKeys::ESC)
				{
					currentState = PAUSED;
					displayPauseMenu();
					if (currentState==NEW_GAME||currentState == ENDED)
						return;

				}

				if (isPlayer1Key(keyPressed))
				{
					if (_p1Board.canShapeMove((GameConfig::eKeys)keyPressed, pCurrP1Shape))
					{
						pCurrP1Shape->moveShape((GameConfig::eKeys)keyPressed);
					}
				}

				else if (isPlayer2Key(keyPressed))
				{
					if (_p2Board.canShapeMove((GameConfig::eKeys)keyPressed, pCurrP2Shape))
					{
						pCurrP2Shape->moveShape((GameConfig::eKeys)keyPressed);
					}
				}

			}

			Sleep(GameConfig::speed::NORMAL);

			if (_p1Board.canMoveDown(pCurrP1Shape->getShapeArr()) == true) // check can move down
			{
				pCurrP1Shape->moveDown();
			}
			else
			{
				_p1Board.addShapeToBoard(pCurrP1Shape);
				delete pCurrP1Shape;
				int randObj1 = rand() % GameConfig::eShapes::NUM_SHAPES;
				pCurrP1Shape = new Shape((GameConfig::eShapes)randObj1, 0, player1, mode);
				pCurrP1Shape->drawOnScreen();
				_p1Board.checkFullRow();
			}


			if (_p2Board.canMoveDown(pCurrP2Shape->getShapeArr()) == true) // check can move down
			{
				pCurrP2Shape->moveDown();
			}
			else
			{
				_p2Board.addShapeToBoard(pCurrP2Shape);
				delete pCurrP2Shape;
				int randObj2 = rand() % GameConfig::eShapes::NUM_SHAPES;
				pCurrP2Shape = new Shape((GameConfig::eShapes)randObj2, 0, player2, mode);
				pCurrP2Shape->drawOnScreen();
				_p2Board.checkFullRow();
			}

		}
		delete pCurrP1Shape;
		delete pCurrP2Shape;
	}
}


// Check if the game is over
bool TetrisGame::checkGameOver(Board& board) const
{

	for (int col = 0; col < COLS; ++col) {
		if (board.isCellOccupied(col, 0)) {
			return true;
		}
	}

	return false;
}




void TetrisGame::HandleGameOver()
{
	int score1 = _p1Board.getScore();
	int score2 = _p2Board.getScore();
	int winner = 0;  //0 for draw, 1 for player 1, 2 for player 2
	int bestScore = 0;
	if (checkGameOver(_p1Board))
		winner = 2;

	else if (checkGameOver(_p2Board))
		winner = 1;

	else if (checkGameOver(_p2Board) && checkGameOver(_p1Board))
	{
		if (score1 > score2)
			winner = 1;

		else if (score2 > score1)
			winner = 2;
		else
			winner = 0;
	}

	// Handle New Record
	if (score1 > bestScore) {
		bestScore = score1;
		updateRecordDisplay(1, bestScore);
	}
	if (score2 > bestScore) {
		bestScore = score2;
		updateRecordDisplay(2, bestScore);
	}

	// Display Game Over and Winner
	displayGameOverMessage(winner, score1, score2);



	char keyPressed = _getch(); // Wait for key press
	if (keyPressed)
	{
		GameState state = NEW_GAME;
		_p1Board.resetBoard();
		_p2Board.resetBoard();
		return;
	}


}


// Update the record display
void TetrisGame::updateRecordDisplay(int player, int newRecord) const
{
	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2 + 8);
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 4); // Set color to red 
	cout << "Player " << player << " sets a new record: " << newRecord;
	SetConsoleTextAttribute(color, 7); // Reset color to default
}


void TetrisGame::displayGameOverMessage(int winner, int score1, int score2) const {

	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2);
	cout << "GAME OVER!" << endl;
	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2 + 1);
	if (winner == 0) {
		gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2 + 2);
		cout << "It's a draw!" << endl;
	}
	else {
		gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2 + 3);
		cout << "Player " << winner << " wins!" << endl;
	}
	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2 + 4);
	cout << "Player 1's Score: " << score1 << endl;
	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2 + 5);
	cout << "Player 2's Score: " << score2 << endl;
	gotoxy(Board::RIGHT_F1 + 3, (Board::BOTTOM_F1 + Board::TOP_F1) / 2 + 6);
	cout << "Press any key to go back to MAIN MENU" << endl;
}




bool TetrisGame::isPlayer1Key(char key) const {
	if (key == GameConfig::eKeys::LEFT || key == GameConfig::eKeys::RIGHT || key == GameConfig::eKeys::HARD_DOWN || key == GameConfig::eKeys::ROTATE_CW || key == GameConfig::eKeys::ROTATE_CCW || key == GameConfig::eKeys::LEFT_CAP || key == GameConfig::eKeys::RIGHT_CAP || key == GameConfig::eKeys::HARD_DOWN_CAP || key == GameConfig::eKeys::ROTATE_CW_CAP || key == GameConfig::eKeys::ROTATE_CCW_CAP) {
		return true; // Player 1
	}
	else return false;
}
bool TetrisGame::isPlayer2Key(char key) const {
	if (key == GameConfig::eKeys2::LEFT2 || key == GameConfig::eKeys2::RIGHT2 || key == GameConfig::eKeys2::HARD_DOWN2 || key == GameConfig::eKeys2::ROTATE_CW2 || key == GameConfig::eKeys2::ROTATE_CCW2 || key == GameConfig::eKeys2::LEFT_CAP2 || key == GameConfig::eKeys2::RIGHT_CAP2 || key == GameConfig::eKeys2::HARD_DOWN_CAP2 || key == GameConfig::eKeys2::ROTATE_CW_CAP2 || key == GameConfig::eKeys2::ROTATE_CCW2) {
		return true; // Player 2
	}
	return false;
}

//Hide Cursor
void TetrisGame::hideCursor() const
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);
}
