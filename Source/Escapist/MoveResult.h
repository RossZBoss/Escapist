// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
*
*/
enum class ESCAPIST_API MoveResult
{
	//AI stuff
	AiPieceTaken,
	UserPieceTaken,
	InvalidMove,
	ValidMove,
	BlockInteraction
};