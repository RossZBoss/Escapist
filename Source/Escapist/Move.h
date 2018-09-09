// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Direction.h"

using namespace std;

class ESCAPIST_API AMove {
private:
	int _distance;
	Direction _direction;
	int _score = 0;

public:
	AMove(Direction direction, int distance);

	int getScore();

	void setScore(int score);

	Direction getDirection();

	int getDistance();

	AMove reverse();

	~AMove();
};
