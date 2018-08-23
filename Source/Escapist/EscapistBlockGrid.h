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
#include "EscapistBlock.h"
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

	//TODO look at getting rid of this or using it better.
	void defaultSetupGivenByUnreal();

	TArray<FString> getArrayFromFile();

	void buildBoard(TArray<FString> gameMap);

	void spwanBlockDefault(int rowNumber, int blockIndexInRow, float zigzag);

	void spwanBlockObstacle(int rowNumber, int blockIndexInRow, float zigzag);

	void spwanPieceUser(int rowNumber, int blockIndexInRow, float zigzag);

	//TODO this can be removed
	void SpawnActor(std::string character, int x, int y);

protected:
	virtual void BeginPlay() override;

public:
	AEscapistBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;
	std::vector<std::vector<int>> GridArray;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	std::list<AEscapistBlock*> tiles = *new std::list<AEscapistBlock*>();

	APiece* userPiece;

	/** Handle the block being clicked */
	void AddScore();

	MoveResult MovePiece(AEscapistBlock* block);

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }


};



