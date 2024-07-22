#include "Shape.h"
#include "GameConfig.h"


//build the shape according to the type
Shape::Shape(GameConfig::eShapes type, int _color, bool _isPlayer1, bool colorMode) : color(_color), isPlayer1(_isPlayer1) {
	int color;
	switch (type)
	{
	case GameConfig::eShapes::L_Shape:
	{
		if (colorMode)
			color = 6;
		else
			color = GameConfig::whiteColor;

		shapeArr[0].setPoint(7, 0, '#', color);
		shapeArr[1].setPoint(7, 1, '#', color);
		shapeArr[2].setPoint(6, 1, '#', color);
		shapeArr[3].setPoint(5, 1, '#', color);
		this->color = color;
		break;
	}
	case GameConfig::eShapes::J_Shape:
	{
		if (colorMode)
			color = 1;
		else
			color = GameConfig::whiteColor;
		shapeArr[0].setPoint(5, 0, '#', color);
		shapeArr[1].setPoint(5, 1, '#', color);
		shapeArr[2].setPoint(6, 1, '#', color);
		shapeArr[3].setPoint(7, 1, '#', color);
		this->color = color;
		break;

	}
	case GameConfig::eShapes::S_Shape:
	{
		if (colorMode)
			color = 10;
		else
			color = GameConfig::whiteColor;
		shapeArr[0].setPoint(7, 0, '#', color);
		shapeArr[1].setPoint(6, 0, '#', color);
		shapeArr[2].setPoint(6, 1, '#', color);
		shapeArr[3].setPoint(5, 1, '#', color);
		this->color = color;
		break;
	}
	case GameConfig::eShapes::Z_Shape:
	{
		if (colorMode)
			color = 4;
		else
			color = GameConfig::whiteColor;
		shapeArr[0].setPoint(5, 0, '#', color);
		shapeArr[1].setPoint(6, 0, '#', color);
		shapeArr[2].setPoint(6, 1, '#', color);
		shapeArr[3].setPoint(7, 1, '#', color);
		this->color = color;
		break;
	}
	case GameConfig::eShapes::I_Shape:
	{
		if (colorMode)
			color = 11;
		else
			color = GameConfig::whiteColor;
		shapeArr[0].setPoint(6, 0, '#', color);
		shapeArr[1].setPoint(6, 1, '#', color);
		shapeArr[2].setPoint(6, 2, '#', color);
		shapeArr[3].setPoint(6, 3, '#', color);
		this->color = color;
		break;
	}
	case GameConfig::eShapes::T_Shape:
	{
		if (colorMode)
			color = 13;
		else
			color = GameConfig::whiteColor;
		shapeArr[0].setPoint(6, 0, '#', color);
		shapeArr[1].setPoint(7, 1, '#', color);
		shapeArr[2].setPoint(6, 1, '#', color);
		shapeArr[3].setPoint(5, 1, '#', color);
		this->color = color;
		break;
	}
	case GameConfig::eShapes::O_Shape:
	{
		if (colorMode)
			color = 14;
		else
			color = GameConfig::whiteColor;
		shapeArr[0].setPoint(6, 0, '#', color);
		shapeArr[1].setPoint(6, 1, '#', color);
		shapeArr[2].setPoint(5, 1, '#', color);
		shapeArr[3].setPoint(5, 0, '#', color);
		this->color = color;
		break;

	}
	default:
		break;
	}
}

//moving the shape according to the key pressed
void Shape::moveShape(GameConfig::eKeys direction) {
	eraseFromScreen();
	switch (direction)
	{
	case GameConfig::LEFT:
	case GameConfig::LEFT2:
	case GameConfig::LEFT_CAP:
	case GameConfig::LEFT_CAP2:

		for (int i = 0; i < 4; i++) {
			shapeArr[i].setOffPoint(-1, 0);
		}
		break;

	case GameConfig::RIGHT:
	case GameConfig::RIGHT2:
	case GameConfig::RIGHT_CAP:
	case GameConfig::RIGHT_CAP2:
		for (int i = 0; i < 4; i++) {
			shapeArr[i].setOffPoint(1, 0);
		}
		break;
	case GameConfig::HARD_DOWN:
	case GameConfig::HARD_DOWN2:
	case GameConfig::HARD_DOWN_CAP:
	case GameConfig::HARD_DOWN_CAP2:
		for (int i = 0; i < 4; i++) {
			shapeArr[i].setOffPoint(0, 2);
		}
		break;
	case GameConfig::ROTATE_CW:
	case GameConfig::ROTATE_CW2:
	case GameConfig::ROTATE_CW_CAP:
	case GameConfig::ROTATE_CW_CAP2:
		this->rotateCW();
		break;
	case GameConfig::ROTATE_CCW:
	case GameConfig::ROTATE_CCW2:
	case GameConfig::ROTATE_CCW_CAP:
	case GameConfig::ROTATE_CCW_CAP2:
		this->rotateCCW();
		break;
	case GameConfig::ESC:
		break;
	}
	drawOnScreen();
}

void Shape::rotateCW() {
	Point pivot = shapeArr[2];

	for (int i = 0; i < 4; ++i) {
		int relativeX = shapeArr[i].getX() - pivot.getX();
		int relativeY = shapeArr[i].getY() - pivot.getY();

		// Rotate 90 degrees clockwise using the 2D rotation matrix
		shapeArr[i].setPoint(pivot.getX() + relativeY, pivot.getY() - relativeX);
	}
}

void Shape::rotateCCW() {
	// Choose a central block as the pivot for rotation
	Point pivot = shapeArr[2];

	for (int i = 0; i < 4; ++i) {
		int relativeX = shapeArr[i].getX() - pivot.getX();
		int relativeY = shapeArr[i].getY() - pivot.getY();

		// Rotate 90 degrees counter-clockwise
		shapeArr[i].setPoint(pivot.getX() - relativeY, pivot.getY() + relativeX);
	}
}

void Shape::moveDown() {

	eraseFromScreen();

	for (int i = 0; i < 4; ++i) {
		shapeArr[i].setY(shapeArr[i].getY() + 1); 
	}

	drawOnScreen();
}



void Shape::drawOnScreen() {
	for (int i = 0; i < 4; i++) {
		shapeArr[i].draw(isPlayer1);
	}
}

void Shape::eraseFromScreen() {
	for (int i = 0; i < 4; i++) {
		shapeArr[i].erase(isPlayer1);
	}
}

