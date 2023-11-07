// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ball.h"
#include "AI_Paddle.generated.h"


UCLASS()
class ZBPONG_API AAI_Paddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAI_Paddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Paddle")
		class UBoxComponent* AIPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Paddle")
		UStaticMeshComponent* VisualMesh;

	double currentVelocity;
	class UFloatingPawnMovement* FloatingPawnMovement;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(Transient)
	ABall* RealBall;
	void SetBall(ABall* Ball);
	float BallLocation() const;
	void MoveAI(float value);
	//AAI_Paddle getAIPaddle();
	float GetCurrentVelocity();
private:
	

	
};
