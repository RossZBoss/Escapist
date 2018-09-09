// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveValidation.h"
#include "EscapistBlock.h"
#include "Piece.h"
#include "User_Piece.h"

MoveValidation::MoveValidation()
{
	//TOP
	moveCalculator.push_back(Point(1, 0));
	//TOP LEFT
	moveCalculator.push_back(Point(0, -1));
	//TOP RIGHT
	moveCalculator.push_back(Point(0, 1));
	//BOTTOM
	moveCalculator.push_back(Point(-1, 0));
	//BOTTOM LEFT
	moveCalculator.push_back(Point(-1, -1));
	//BOTTOM RIGHT
	moveCalculator.push_back(Point(-1, 1));

	//OFFSET
	offset = Point(1, 0);
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
				result = result.add(offset);
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
