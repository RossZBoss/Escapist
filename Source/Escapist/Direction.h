// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Point.h"

/**
*
*/
class ESCAPIST_API Direction
{
public:
	static const Point moveTop;
	static const Point moveTopLeft;
	static const Point moveTopRight;
	static const Point moveBottom;
	static const Point moveBottomLeft;
	static const Point moveBottomRight;

	//OFFSET -> this is pretty confusing, because we are representing hexigons in a 2d vector we get a couple
	// annomalies in some positions on the board. sometime sthe position to the right is in the same row and 
	// others its in the row above in the 2d grid. currently debugging is on and you can click on tiles to see this.
	static const Point moveOffset;
};