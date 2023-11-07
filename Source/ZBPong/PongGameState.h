// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"


/**
 * 
 */
UCLASS()
class ZBPONG_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()
	

public:

	APongGameState();

	void AddAI();
	void AddPlayer();

	int AIScore = 0;
	int PlayerScore = 0;

	void resetBall();
};
