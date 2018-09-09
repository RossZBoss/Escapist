// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "EscapistBlock.h"
#include <vector>

/**
 * 
 */
class ESCAPIST_API MoveValidation
{
private:
	//CALCULATING MOVESET
	vector<Point> moveCalculator;

	Point offset;

	//PIECE DATA
	std::vector<vector<AEscapistBlock*>>* MoveGrid;
	int MoveDistance;
	Point PieceLocation;

	vector<Point> buildValidMoveset();

	void notifyBlocksOfValidMove(vector<Point> validMoveset);
public:
	MoveValidation();

	void SetValidMoves(APiece* piece, vector<vector<AEscapistBlock*>>* blockGrid);
};
