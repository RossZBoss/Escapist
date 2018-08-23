// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EscapistBlockGrid.h"
#include "EscapistBlock.h"
#include "Direction.h"
#include "ObstacleBlock.h"
#include <vector>
#include "WorldMapConstants.h"
#include "FileHelper.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AEscapistBlockGrid::AEscapistBlockGrid()
{
	// Set defaults
	Size = 6;
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
			spwanBlockDefault(rowNumber, blockIndexInRow, zigzag);
		}
		else if (blockOrPiece.Compare(WorldMapConstants::BLOCK_OBSTACLE) == 0)
		{
			spwanBlockObstacle(rowNumber, blockIndexInRow, zigzag);
		}
		else if (blockOrPiece.Compare(WorldMapConstants::BLOCK_EMPTY) == 0)
		{
			//Do nothing
		}
		else if (blockOrPiece.Compare(WorldMapConstants::PIECE_USER) == 0)
		{
			spwanBlockDefault(rowNumber, blockIndexInRow, zigzag);
			spwanPieceUser(rowNumber, blockIndexInRow, zigzag);
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
}

void AEscapistBlockGrid::spwanBlockDefault(int rowNumber, int blockIndexInRow, float zigzag) {
	//set default spwan location (getActorLocation will add to x/y/z coords to center the blocks on the map.
	const FVector BlockLocation = FVector(
		((rowNumber * WorldMapConstants::BLOCK_SPACING_X) + zigzag),
		(blockIndexInRow * WorldMapConstants::BLOCK_SPACING_Y), 0.0f) + GetActorLocation();
	// Spawn block on location
	AEscapistBlock* NewBlock = GetWorld()->SpawnActor<AEscapistBlock>(BlockLocation, FRotator(0, 0, 0));
	if (NewBlock != nullptr)
	{
		NewBlock->OwningGrid = this;
	}
}

void AEscapistBlockGrid::spwanBlockObstacle(int rowNumber, int blockIndexInRow, float zigzag) {
	//set default spwan location (getActorLocation will add to x/y/z coords to center the blocks on the map.
	const FVector BlockLocation = FVector(
		((rowNumber * WorldMapConstants::BLOCK_SPACING_X) + zigzag),
		(blockIndexInRow * WorldMapConstants::BLOCK_SPACING_Y), 0.0f) + GetActorLocation();
	// Spawn block on location
	AObstacleBlock* NewBlock = GetWorld()->SpawnActor<AObstacleBlock>(BlockLocation, FRotator(0, 0, 0));
	if (NewBlock != nullptr)
	{
		NewBlock->OwningGrid = this;
	}
}

void AEscapistBlockGrid::spwanPieceUser(int rowNumber, int blockIndexInRow, float zigzag) {
	//set default spwan location (getActorLocation will add to x/y/z coords to center the blocks on the map.
	const FVector PawnLocation = FVector(
		((rowNumber * WorldMapConstants::BLOCK_SPACING_X) + zigzag),
		(blockIndexInRow * WorldMapConstants::BLOCK_SPACING_Y), WorldMapConstants::BLOCK_PIECE_SPACING_Z) + GetActorLocation();
	// Spawn pawn on location
	APiece* Pawn = GetWorld()->SpawnActor<APiece>(PawnLocation, FRotator(0, 0, 0));

	if (Pawn != nullptr) {
		Pawn->OwningGrid = this;
	}
}

MoveResult AEscapistBlockGrid::MovePiece(AEscapistBlock* block) {

	FVector pieceDestination = block->GetActorLocation() + FVector(-1500, 0, 200);

//	UE_LOG(LogTemp, Warning, TEXT("Moving user to location: %s"), *pieceDestination.ToString());

	userPiece->SetActorLocation(pieceDestination);

//	UE_LOG(LogTemp, Warning, TEXT("User rootcomp location: %s"), *(RootComponent->GetComponentLocation().ToString()));

	// TODO Need to calculate distance between block and user
	float xDistanceToBlock = userPiece->GetActorLocation().X - block->GetActorLocation().X;
	float yDistanceToBlock = userPiece->GetActorLocation().Y - block->GetActorLocation().Y;
	int xCoord = xDistanceToBlock / 250;
	int yCoord = yDistanceToBlock / 250;

	AMove* x;
	//AMove* y;

	if (xCoord > 0) {
		x = new AMove(Direction::Down, xCoord);
	}
	else if (xCoord < 0) {
		x = new AMove(Direction::Down, xCoord);
	}
	MoveResult moveResult = MoveResult::ValidMove;

	return moveResult;
};

void AEscapistBlockGrid::SpawnActor(std::string character, int x, int y) {
	// Make position vector, offset from Grid location
	const FVector BlockLocation = FVector(x * WorldMapConstants::BLOCK_SPACING_X, y * WorldMapConstants::BLOCK_SPACING_Y, 0.f);// + GetActorLocation();
	const FVector PawnLocation = FVector(y * WorldMapConstants::BLOCK_SPACING_X, x * WorldMapConstants::BLOCK_SPACING_Y, WorldMapConstants::BLOCK_PIECE_SPACING_Z);// + GetActorLocation();
	AEscapistBlock* NewBlock = NULL;
	APiece* Pawn = NULL;
	if (character == "0") {
		NewBlock = GetWorld()->SpawnActor<AObstacleBlock>(BlockLocation, FRotator(0, 0, 0));
	}
	// Spawn a block
	else {
		NewBlock = GetWorld()->SpawnActor<AEscapistBlock>(BlockLocation, FRotator(0, 0, 0));
	}

	if (character == "D") {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Pawn = GetWorld()->SpawnActor<APiece>(PawnLocation, FRotator(0, 0, 0));
		Pawn->Init(x, y);
		this->userPiece = Pawn;
	}
	// Tell the block about its owner
	if (NewBlock != nullptr) {
		NewBlock->OwningGrid = this;
		NewBlock->Init(x, y);
//		UE_LOG(LogTemp, Warning, TEXT("Spawning tile at expected location %s, Tile is at real location: %s"), *BlockLocation.ToString(), *NewBlock->GetActorLocation().ToString());

	}

	tiles.push_back(NewBlock);
}


void AEscapistBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
