#include "Piece.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EscapistBlockGrid.h"
#include <iostream>
#include <sstream>
#include "Engine/World.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Engine/StaticMesh.h"


// Sets default values
APiece::APiece()
{
	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> ClayBrickMaterial = (TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterialOpt(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial = (TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedMaterialOpt(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"));
	OrangeMat = BlueMaterial.Get();
	ClayBrick = ClayBrickMaterial.Get();
	RedMaterial = RedMaterialOpt.Get();

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = DummyRoot;

	//UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	//UE_LOG(LogTemp, Warning, TEXT("Is collision enabled for this piece: %d"), RootComponent->IsCollisionEnabled());
	
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetStaticMesh(PlaneMesh.Get());
	OurVisibleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	OurVisibleComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	OurVisibleComponent->SetMaterial(0, OrangeMaterialOpt.Get());
	OurVisibleComponent->SetupAttachment(DummyRoot);
	//OurVisibleComponent->OnClicked.AddDynamic(this, &APiece::BlockClicked);
	//OurVisibleComponent->OnInputTouchBegin.AddDynamic(this, &APiece::OnFingerPressedBlock);
	//OurCamera->SetupAttachment(RootComponent);
	//OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	//OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
}


// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APiece::setAiMaterial()
{
	OurVisibleComponent->SetMaterial(0, RedMaterial);
}

//######################################
//THESE ARE ONLY USABLE BY USER_PIECE'S
//######################################
void APiece::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void APiece::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void APiece::HandleClicked()
{
	OwningGrid->validateMovePiece(this);
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("you clicked the piece"));
}