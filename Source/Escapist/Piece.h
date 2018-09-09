// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"
#include <vector>
#include "Move.h"
#include "Point.h"
#include "Piece.generated.h"

UCLASS(minimalapi)
class APiece : public AActor
{
	GENERATED_BODY()

private:
	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

	/*ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial = (TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> ClayBrickMaterial = (TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterial> RedMaterialOpt = (TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"));*/
	UMaterialInstance* OrangeMat;
	UMaterialInstance* ClayBrick;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	APiece();

	Point location;

	//will expand on this later!
	int moveDistance = 1;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Grid that owns us */
	UPROPERTY()
	class AEscapistBlockGrid* OwningGrid;

	void setAiMaterial();
	UMaterialInstance* RedMaterial;

	//###########################################
	//THESE SHOULD BE ONLY USABLE BY USER_PIECE'S
	//###########################################

	//THis has to be public so we can add clickable for user pieces.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OurVisibleComponent;

	// Handle the block being clicked 
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	// Handle the block being touched  
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();
};
