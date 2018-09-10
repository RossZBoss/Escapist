// Fill out your copyright notice in the Description page of Project Settings.

#include "Direction.h"

const Point Direction::moveTop = Point(1, 0);
const Point Direction::moveTopLeft = Point(0, -1);
const Point Direction::moveTopRight = Point(0, 1);
const Point Direction::moveBottom = Point(-1, 0);
const Point Direction::moveBottomLeft = Point(-1, -1);
const Point Direction::moveBottomRight = Point(-1, 1);

//OFFSET -> this is pretty confusing, because we are representing hexigons in a 2d vector we get a couple
// annomalies in some positions on the board. sometime sthe position to the right is in the same row and 
// others its in the row above in the 2d grid. currently debugging is on and you can click on tiles to see this.
const Point Direction::moveOffset = Point(1, 0);