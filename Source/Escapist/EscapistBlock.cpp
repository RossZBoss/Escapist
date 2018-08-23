// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EscapistBlock.h"
#include "EscapistBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "EscapistBlockGrid.h"
#include "Materials/MaterialInstance.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

AEscapistBlock::AEscapistBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/ice_block_attempt.ice_block_attempt"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,1.f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,0.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AEscapistBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AEscapistBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();

	//Sean Added log
	//UE_LOG(LogTemp, Warning, TEXT("Current location is: %s"), *(GetActorLocation().ToString()))//+ " is:" +
}

//TODO refactor constructor to have reusable elements, use the basematerial parameter!!!!
AEscapistBlock::AEscapistBlock(FString& baseMaterial)
{
	//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("spwaning an obstacle block")));
	// Structure to hold one-time initialization

	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh(TEXT("/Game/Puzzle/Meshes/ice_block_attempt.ice_block_attempt"));
	ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterialOpt(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlackMaterialOpt(TEXT("/Game/Puzzle/Meshes/BlackMaterial.BlackMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterialOpt(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"));

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetMaterial(0, BlackMaterialOpt.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AEscapistBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AEscapistBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = BaseMaterialOpt.Get();

	//TODO: this should be cleaned later!
	obstacleBlockType = true;
}

void AEscapistBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void AEscapistBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AEscapistBlock::HandleClicked()
{
	//Sean Added
	//OwningGrid->MovePiece(this);

	// Check we are not already active
	if (!bIsActive && !obstacleBlockType)
	{
		bIsActive = true;

		// Change material
		BlockMesh->SetMaterial(0, OrangeMaterial);

		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->AddScore();
		}
	}
}

void AEscapistBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}

//Sean added
void AEscapistBlock::Init(int x, int y) {
	RootComponent->SetRelativeLocation(FVector(x * 250, y * 250, 0.f));
}
