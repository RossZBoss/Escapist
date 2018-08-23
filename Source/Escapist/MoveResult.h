// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
*
*/
enum class ESCAPIST_API MoveResult
{
	AiPieceTaken,
	UserPieceTaken,
	InvalidMove,
	ValidMove,
	BlockInteraction
};