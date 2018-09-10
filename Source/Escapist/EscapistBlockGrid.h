// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include "ObstacleBlock.h"
#include "Piece.h"
#include "User_Piece.h"
#include "EscapistBlock.h"
#include "Point.h"
#include "MoveValidation.h"
#include "Move.h"
#include "MoveResult.h"
#include "EscapistBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class AEscapistBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

private:
	MoveValidation moveValidation;

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }

	//TODO look at getting rid of this or using it better.
	void defaultSetupGivenByUnreal();

	TArray<FString> getArrayFromFile();

	void buildBoard(TArray<FString> gameMap);

	AEscapistBlock* spwanBlockDefault(int rowNumber, int blockIndexInRow, float zigzag);

	AEscapistBlock* spwanBlockHill(int rowNumber, int blockIndexInRow, float zigzag);

	AObstacleBlock* spwanBlockObstacle(int rowNumber, int blockIndexInRow, float zigzag);

	void insertIntoBlockGrid(AEscapistBlock* block, int rowNumber);

	AUser_Piece* spwanPieceUser(AEscapistBlock* block);

	void insertUserPiece(AUser_Piece* userPiece);

	APiece* spwanPieceAi(AEscapistBlock* block);

	void insertAiPiece(APiece* userPiece);

protected:
	virtual void BeginPlay() override;

public:
	AEscapistBlockGrid();

	std::vector<vector<AEscapistBlock*>> blockGrid;

	std::vector<AUser_Piece*> userPieces;

	APiece* selectedUserPiece;

	std::vector<APiece*> aiPieces;

	void validateMovePiece(APiece* piece);

	MoveResult MovePiece(AEscapistBlock* destinationBlock);

	/** How many blocks have been clicked */
	int32 Score;

	/** Handle the block being clicked */
	void AddScore();
};



