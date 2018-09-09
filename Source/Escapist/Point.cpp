// Fill out your copyright notice in the Description page of Project Settings.

#include "Point.h"

Point::Point()
{
	//kept complaing about no default constructor.
}

Point::Point(int x_coord, int y_coord) {
	x = x_coord;
	y = y_coord;
}

int Point::getX() const {
	return x;
}

int Point::getY() const {
	return y;
}

Point Point::add(Point p)
{
	int resultX = x + p.getX();
	int resultY = y + p.getY();

	return Point(resultX, resultY);
}

std::string Point::toString() {
	std::ostringstream oss;
	oss << "(" << getX() << "," << getY() << ")";
	return oss.str();
}

Point::~Point()
{
}
