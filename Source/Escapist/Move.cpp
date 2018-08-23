// Fill out your copyright notice in the Description page of Project Settings.

#include "Move.h"

AMove::AMove(Direction direction, int distance) {
	_direction = direction;
	_distance = distance;
}

int AMove::getScore() {
	return _score;
}

void AMove::setScore(int score) {
	_score = score;
}

Direction AMove::getDirection() {
	return _direction;
}

int AMove::getDistance() {
	return _distance;
}

AMove AMove::reverse() {
	int reverseDirectionInt = ((int)_direction + 2) % 4;
	Direction reverseDirection;
	switch (reverseDirectionInt) {
		case 0: {
			reverseDirection = Direction::Up;
			break;
		}
		case 1: {
			reverseDirection = Direction::UpLeft;
			break;
		}
		case 2: {
			reverseDirection = Direction::UpRight;
			break;
		}
		case 3: {
			reverseDirection = Direction::Down;
			break;
		}
		case 4: {
			reverseDirection = Direction::DownLeft;
			break;
		}
		case 5: {
			reverseDirection = Direction::DownRight;
			break;
		}
	}
	return *new AMove(reverseDirection, _distance);
}

AMove::~AMove()
{
}