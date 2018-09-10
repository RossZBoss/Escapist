// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveValidation.h"
#include "EscapistBlock.h"
#include "Piece.h"
#include "Direction.h"
#include "User_Piece.h"

using namespace std;

MoveValidation::MoveValidation()
{
	//TOP
	moveCalculator.push_back(Direction::moveTop);
	//TOP LEFT
	moveCalculator.push_back(Direction::moveTopLeft);
	//TOP RIGHT
	moveCalculator.push_back(Direction::moveTopRight);
	//BOTTOM
	moveCalculator.push_back(Direction::moveBottom);
	//BOTTOM LEFT
	moveCalculator.push_back(Direction::moveBottomLeft);
	//BOTTOM RIGHT
	moveCalculator.push_back(Direction::moveBottomRight);
}

void MoveValidation::SetValidMoves(APiece* piece, vector<vector<AEscapistBlock*>>* blockGrid)
{
	MoveGrid = blockGrid;
	MoveDistance = piece->moveDistance;
	PieceLocation = piece->location;
	
	vector<Point> validMoveset = buildValidMoveset();
	notifyBlocksOfValidMove(validMoveset);
}

vector<Point> MoveValidation::buildValidMoveset()
{
	vector<Point> validMoveset;
	for (int dec = MoveDistance; dec != 0; dec--)
	{
		// TODO: this will need to get each valid move from previous iteration and perform the same calculation on that Point.
		// will do later!
		for (Point p : moveCalculator)
		{
			Point result = p.add(PieceLocation);
			if (PieceLocation.getY() % 2 > 0 && PieceLocation.getY() != result.getY())
			{
				result = result.add(Direction::moveOffset);
			}
			validMoveset.push_back(result);
		}
	}
	return validMoveset;
}

void MoveValidation::notifyBlocksOfValidMove(vector<Point> validMoveset)
{
	for (Point validMove : validMoveset)
	{
		if (validMove.getX() < MoveGrid->size() && validMove.getX() >= 0)
		{
			vector<AEscapistBlock*> gridRow = MoveGrid->at(validMove.getX());
			if (validMove.getY() < gridRow.size() && validMove.getY() >= 0)
			{
				AEscapistBlock* blockRef = gridRow.at(validMove.getY());
				blockRef->SetValidMove(true);
			}
		}
	}
}

vector<Point> MoveValidation::getShortestPathBetweenTwoPoints(vector<vector<AEscapistBlock*>>* blockGrid, Point startPoint, Point destination)
{
	//we can easily convert this to return a set of blocks instead of a set of points.
	//this will be used for the AI so wasn't sure what was the better option.

	//TODO: Current implementation is ignoring obstacle blocks and hills. will be added later.
	/*
	Point currentPoint = Point(startPoint.getX, startPoint.getY());
	vector<Point> shortestPath;
	while (!currentPoint.equals(destination))
	{
		Point result = p.add(PieceLocation);
		if (PieceLocation.getY() % 2 > 0 && PieceLocation.getY() != result.getY())
		{
			result = result.add(Direction::moveOffset);
		}
	}*/
	return {};
}
