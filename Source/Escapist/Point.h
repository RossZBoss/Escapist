// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <list>

//Class Point represents points in the Cartesian coordinate
class ESCAPIST_API Point
{
protected:
	int x, y; // coordinates of the point

public:
	Point();
	Point(int, int);
	int getX() const;
	int getY() const;

	Point add(Point p);

	bool equals(Point p);

	std::string toString();

	~Point();
};
