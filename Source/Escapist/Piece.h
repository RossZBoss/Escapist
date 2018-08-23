// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"
#include <vector>
#include "Move.h"
#include "Piece.generated.h"

UCLASS()
class ESCAPIST_API APiece : public APawn
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	// Sets default values for this pawn's properties
	APiece();

	void Init(int x, int y);

	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial = (TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> ClayBrickMaterial = (TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"));
	UMaterialInstance* OrangeMat;
	UMaterialInstance* ClayBrick;
	int X = 0;
	int Y = 0;
	int LastX = 0;
	int LastY = 0;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OurVisibleComponent;

	std::vector<FVector> GetAllMoveCoordinatesToPostion(AMove* move);

	/** Grid that owns us */
	UPROPERTY()
	class AEscapistBlockGrid* OwningGrid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
