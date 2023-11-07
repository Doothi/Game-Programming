// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class ZBPONG_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();
	TArray<AAI_Paddle*> Spawners;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UBoxComponent* Top;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* VisualMeshRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UBoxComponent* Bottom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UBoxComponent* Left;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UBoxComponent* Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		class UArrowComponent* SpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Class to spawn")
		TSubclassOf<class ABall> BallTemplate;
	UPROPERTY(EditAnywhere, Category = "Class to spawn")
		TSubclassOf<class AAI_Paddle> AIPaddleTemplate;
	UPROPERTY(Transient)
		class ABall* SpawnedBall;
	bool bCanSpawn = true;
	int AIScore;
	int PlayerScore;
	//UPROPERTY(Transient)
		class APongGameState* PongGameState;
	UPROPERTY(Transient)
		class AAI_Paddle* AI_Paddle;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "AAA")
		void SetCanSpawn(bool bNewCanSpawn);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "AAA")
		void SpawnBall();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "AAA")
		void SetAI_Paddle(class AAI_Paddle* NewAI_Paddle) {
		AI_Paddle = NewAI_Paddle;
	}
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "AAA")
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
