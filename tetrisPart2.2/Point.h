#pragma once
#include "GameConfig.h"
#include <iostream>
#include <Windows.h>
using namespace std;

class Point
{
	//Data members
	int x;
	int y;
	char ch;
	int color;

public:
	//default ctor
	Point() : x(0), y(0), ch('#') {}

	//ctor 
	Point(int _x, int _y, char _ch = '#') : x(_x), y(_y), ch(_ch) {};

	void setPoint(int _x, int _y, char ch, int _color);
	void setPoint(int _x, int _y) { x = _x; y = _y; } // set point only for the coordinates

	const int getColor() const { return color; }
	void setColor(int _color) { color = _color; }

	void setOffPoint(int _x, int _y) { x += _x; y += _y; }
	char getSign() const { return ch; };
	void setSign(char sign) { ch = sign; }


	//draw
	void draw(bool isPlayer1) const;

	void erase(bool isPlayer1) const;

	//set point coordinates
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	// get point coordinates
	int getX() const { return x; }
	int getY() const { return y; }

};