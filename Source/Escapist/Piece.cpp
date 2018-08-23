#include "Piece.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include <iostream>
#include <sstream>

#include "Engine/StaticMesh.h"


// Sets default values
APiece::APiece()
{

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	UE_LOG(LogTemp, Warning, TEXT("Is collision enabled for this piece: %d"), RootComponent->IsCollisionEnabled());
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"));
	OurVisibleComponent->SetStaticMesh(PlaneMesh.Get());
	OrangeMat = BlueMaterial.Get();
	ClayBrick = ClayBrickMaterial.Get();
	OurVisibleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	OurCamera->SetupAttachment(RootComponent);
	//OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	//OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

void APiece::Init(int x, int y) {

	X = x;
	Y = y;
	OurVisibleComponent->SetRelativeLocation(FVector(x * 250, y * 250, 0.f));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurVisibleComponent->SetMaterial(0, OrangeMat);

	//OurVisibleComponent->GetComponentLocation().at(0) << ", " << OurVisibleComponent->GetComponentLocation()[1] << ", " << OurVisibleComponent->GetComponentLocation()[2];
	UE_LOG(LogTemp, Warning, TEXT("PieceActor location is: %s"), *(GetActorLocation().ToString()));//+ " is:" +

	UE_LOG(LogTemp, Warning, TEXT("Visible component location is: %s"), *(OurVisibleComponent->GetComponentLocation().ToString()));//+ " is:" +

};

std::vector<FVector> APiece::GetAllMoveCoordinatesToPostion(AMove* move) {
	std::vector<FVector> returnPoints;

	// figure out direction to position

	//

	switch (move->getDirection()) {
	case Direction::Up:
		//	returnPoints = getAllPointsOnPath(move, 0, -1);
		break;
	case Direction::UpLeft:
		//	returnPoints = getAllPointsOnPath(move, 0, -1);
		break;
	case Direction::UpRight:
		//	returnPoints = getAllPointsOnPath(move, 0, -1);
		break;
	case Direction::Down:
		//	returnPoints = getAllPointsOnPath(move, 0, 1);
		break;
	case Direction::DownLeft:
		//	returnPoints = getAllPointsOnPath(move, -1, 0);
		break;
	case Direction::DownRight:
		//	returnPoints = getAllPointsOnPath(move, 1, 0);
		break;
	}

	return returnPoints;
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

// Called to bind functionality to input
void APiece::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("Setup Player Input"));

}