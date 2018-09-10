// Fill out your copyright notice in the Description page of Project Settings.

#include "User_Piece.h"
#include "Piece.h"

AUser_Piece::AUser_Piece() : APiece() {
	APiece::OurVisibleComponent->OnClicked.AddDynamic(this, &APiece::BlockClicked);
	APiece::OurVisibleComponent->OnInputTouchBegin.AddDynamic(this, &APiece::OnFingerPressedBlock);
}
