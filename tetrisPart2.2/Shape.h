#pragma once

#include "Point.h"
#include "GameConfig.h"
class Shape
{
private:
	Point shapeArr[4];
	int color;
	bool isPlayer1;
	bool colorMode=true;
public:
	Shape(GameConfig::eShapes type, int _color = GameConfig::whiteColor, bool isPlayer1 = true, bool colorMode=true);
	~Shape() {}
	// Copy constructor
	Shape(const Shape& other) {
		// Copy the color
		color = other.color;

		// Copy each point in the shapeArr
		for (int i = 0; i < 4; ++i) {
			shapeArr[i] = other.shapeArr[i];
		}
	}

	const Point* getShapeArr() const { return shapeArr; }
	int getColor() const { return color; }

	void moveShape(GameConfig::eKeys direction);
	void rotateCW();
	void rotateCCW();
	void moveDown();
	void drawOnScreen();
	void eraseFromScreen();


};








