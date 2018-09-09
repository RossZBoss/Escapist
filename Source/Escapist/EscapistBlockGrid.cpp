// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EscapistBlockGrid.h"
#include "EscapistBlock.h"
#include "Direction.h"
#include "ObstacleBlock.h"
#include <vector>
#include <list>
#include <string>
#include "User_Piece.h"
#include "EscapistBlock.h"
#include "Point.h"
#include "MoveValidation.h"
#include "WorldMapConstants.h"
#include "FileHelper.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AEscapistBlockGrid::AEscapistBlockGrid()
{
	defaultSetupGivenByUnreal();
}

void AEscapistBlockGrid::defaultSetupGivenByUnreal()
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	RootComponent->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(800.f, 0.f, -200.f));
	ScoreText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);
}

void AEscapistBlockGrid::BeginPlay()
{
	Super::BeginPlay();
	moveValidation = MoveValidation::MoveValidation();
	TArray<FString> gameMap = getArrayFromFile();
	buildBoard(gameMap);
}


TArray<FString> AEscapistBlockGrid::getArrayFromFile() {
	//this can be cleaned up later
	FString result = "FileWasNotRead";
	//put Z in name so its at bottom of IDE
	FString filePath = "C:\\Users\\Ross\\Documents\\Unreal Projects\\Escapist\\Source\\Escapist\\Z_inputMap.txt";

	FFileHelper::LoadFileToString(result, *filePath);
	//TODO: Note that right now the file must have 0 whitespace for this splitting to work, find a way to remove all whitespaces before splitting.
	TArray<FString> gameMap;
	result.ParseIntoArray(gameMap, TEXT(","), false);
	return gameMap;
}

void AEscapistBlockGrid::buildBoard(TArray<FString> gameMap) {
	//use this to print shit
	//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("spwaning a block")));
	int rowNumber = 0;
	int blockIndexInRow = 0;
	for (FString blockOrPiece : gameMap)
	{
		float zigzag = 0;

		if (blockIndexInRow % 2 == 0)
		{
			zigzag = -WorldMapConstants::BLOCK_SPACING_X / 2;
		}
		if (blockOrPiece.Compare(WorldMapConstants::BLOCK_DEFAULT) == 0)
		{
			insertIntoBlockGrid(spwanBlockDefault(rowNumber, blockIndexInRow, zigzag), rowNumber);
		}
		else if (blockOrPiece.Compare(WorldMapConstants::BLOCK_OBSTACLE) == 0)
		{
			insertIntoBlockGrid(spwanBlockObstacle(rowNumber, blockIndexInRow, zigzag), rowNumber);
		}
		else if (blockOrPiece.Compare(WorldMapConstants::BLOCK_EMPTY) == 0)
		{
			//Do nothing
		}
		else if (blockOrPiece.Compare(WorldMapConstants::PIECE_USER) == 0)
		{
			AEscapistBlock* block = spwanBlockDefault(rowNumber, blockIndexInRow, zigzag);
			insertIntoBlockGrid(block, rowNumber);
			insertUserPiece(spwanPieceUser(block));
		}
		else if (blockOrPiece.Compare(WorldMapConstants::PIECE_AI) == 0)
		{
			AEscapistBlock* block = spwanBlockDefault(rowNumber, blockIndexInRow, zigzag);
			insertIntoBlockGrid(block, rowNumber);
			insertAiPiece(spwanPieceAi(block));
		}
		if (blockOrPiece.Compare(WorldMapConstants::END_OF_ROW) == 0)
		{
			blockIndexInRow = 0;
			rowNumber++;
		}
		else
		{
			blockIndexInRow++;
		}
	}
	//TODO remove general output when it stops spazzing out.
	FString outputSize = std::to_string(blockGrid.size()).c_str();
	FString outputRow1 = std::to_string(blockGrid[0].size()).c_str();
	FString outputRow2 = std::to_string(blockGrid[1].size()).c_str();
	FString outputRow3 = std::to_string(blockGrid[2].size()).c_str();
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, outputSize);
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, outputRow1);
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, outputRow2);
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, outputRow3);
}

AEscapistBlock* AEscapistBlockGrid::spwanBlockDefault(int rowNumber, int blockIndexInRow, float zigzag) {
	//set default spwan location (getActorLocation will add to x/y/z coords to center the blocks on the map.
	const FVector BlockLocation = FVector(
		((rowNumber * WorldMapConstants::BLOCK_SPACING_X) + zigzag),
		(blockIndexInRow * WorldMapConstants::BLOCK_SPACING_Y), 0.0f) + GetActorLocation();
	// Spawn block on location
	AEscapistBlock* NewBlock = GetWorld()->SpawnActor<AEscapistBlock>(BlockLocation, FRotator(0, 0, 0));
	if (NewBlock != nullptr)
	{
		NewBlock->OwningGrid = this;
		NewBlock->location = Point(rowNumber, blockIndexInRow);
	}
	return NewBlock;
}

AObstacleBlock* AEscapistBlockGrid::spwanBlockObstacle(int rowNumber, int blockIndexInRow, float zigzag) {
	//set default spwan location (getActorLocation will add to x/y/z coords to center the blocks on the map.
	const FVector BlockLocation = FVector(
		((rowNumber * WorldMapConstants::BLOCK_SPACING_X) + zigzag),
		(blockIndexInRow * WorldMapConstants::BLOCK_SPACING_Y), 0.0f) + GetActorLocation();
	// Spawn block on location
	AObstacleBlock* NewBlock = GetWorld()->SpawnActor<AObstacleBlock>(BlockLocation, FRotator(0, 0, 0));
	if (NewBlock != nullptr)
	{
		NewBlock->OwningGrid = this;
		NewBlock->location = Point(rowNumber, blockIndexInRow);
	}
	return NewBlock;
}

void  AEscapistBlockGrid::insertIntoBlockGrid(AEscapistBlock* block, int rowNumber)
{
	if (blockGrid.size() <= rowNumber)
	{
		std::vector<AEscapistBlock*> innerGrid(1, block);
		blockGrid.push_back(innerGrid);
	}
	else
	{
		blockGrid[rowNumber].push_back(block);
	}
}

AUser_Piece* AEscapistBlockGrid::spwanPieceUser(AEscapistBlock* block) {

	FVector PawnLocation = FVector(0.0f, 0.0f, WorldMapConstants::BLOCK_PIECE_SPACING_Z) + block->GetActorLocation();

	// Spawn pawn on location
	AUser_Piece* Pawn = GetWorld()->SpawnActor<AUser_Piece>(PawnLocation, FRotator(0, 0, 0));

	if (Pawn != nullptr) {
		Pawn->OwningGrid = this;
		Pawn->location = block->location;
	}
	return Pawn;
}

void AEscapistBlockGrid::insertAiPiece(APiece* aiPiece)
{
	aiPieces.push_back(aiPiece);
}

APiece* AEscapistBlockGrid::spwanPieceAi(AEscapistBlock* block) {

	FVector PawnLocation = FVector(0.0f, 0.0f, WorldMapConstants::BLOCK_PIECE_SPACING_Z) + block->GetActorLocation();

	// Spawn pawn on location
	APiece* Pawn = GetWorld()->SpawnActor<APiece>(PawnLocation, FRotator(0, 0, 0));

	if (Pawn != nullptr) {
		Pawn->OwningGrid = this;
		Pawn->location = block->location;
		Pawn->setAiMaterial();
	}
	return Pawn;
}

void AEscapistBlockGrid::insertUserPiece(AUser_Piece* userPiece)
{
	userPieces.push_back(userPiece);
}

void AEscapistBlockGrid::validateMovePiece(APiece* piece)
{
	moveValidation.SetValidMoves(piece, &blockGrid);
	selectedUserPiece = piece;
}

MoveResult AEscapistBlockGrid::MovePiece(AEscapistBlock* destinationBlock) {
	for (int inc = 0; inc < aiPieces.size(); inc++)
	{
		APiece* aiPiece = aiPieces[inc];
		if (destinationBlock->location.getX() == aiPiece->location.getX() && destinationBlock->location.getY() == aiPiece->location.getY())
		{
			aiPieces.erase(aiPieces.begin() + inc);
			aiPiece->GetWorld()->DestroyActor(aiPiece, true);
		}
	}
	
	FVector PawnLocation = FVector(0.0f, 0.0f, WorldMapConstants::BLOCK_PIECE_SPACING_Z) + destinationBlock->GetActorLocation();
	selectedUserPiece->SetActorLocation(PawnLocation);
	selectedUserPiece->location = destinationBlock->location;
	for (int dec = blockGrid.size()-1; dec >= 0; dec--)
	{
		vector<AEscapistBlock*> gridRow = blockGrid.at(dec);
		for (int inc = 0; inc < gridRow.size(); inc++)
		{
			AEscapistBlock* block = gridRow.at(inc);
			block->SetValidMove(false);
		}
	}
	//just put it here for now!
	return MoveResult::AiPieceTaken;
};

void AEscapistBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
