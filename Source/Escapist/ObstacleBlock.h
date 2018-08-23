// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapistBlock.h"
#include "ObstacleBlock.generated.h"

/**
*
*/
UCLASS()
class ESCAPIST_API AObstacleBlock : public AEscapistBlock
{
	GENERATED_BODY()

private:
	FString baseMaterial = "/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial";

public:
	AObstacleBlock();
};
