// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameState.h"

APongGameState::APongGameState()
{
	PrimaryActorTick.bCanEverTick = false;
	PlayerScore = 0;
	AIScore = 0;
}

void APongGameState::AddAI()
{
	AIScore++;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Overlaps: %d"), AIScore));
	resetBall();
}

void APongGameState::AddPlayer()
{
	PlayerScore++;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Overlaps: %d"), PlayerScore));

	resetBall();
}

void APongGameState::resetBall()
{
}
