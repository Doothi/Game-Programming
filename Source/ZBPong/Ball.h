// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Ball.generated.h"


UCLASS()
class ZBPONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pong")
		class USphereComponent* CollisionPong;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pong")
		USceneComponent* VisualMeshRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pong")
		UStaticMeshComponent* VisualMesh;
		//UClass* BallTemplate;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		UProjectileMovementComponent* PMComp;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UFloatingPawnMovement* FloatingPawnMovement;

	float CurrentVelocity = 0;
	float hits = 0;
	UFUNCTION()
		void OnCollisionPongHit(
			UPrimitiveComponent* OverlappedComponent, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			FVector NormalImpulse,
			const FHitResult& Hit);

	UFUNCTION()
		void OnCollisionPongBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	

	

private:
		FTimerHandle StartGameTimerHandle;
		UFUNCTION()
		void StartGameTimer();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector GetVelocity() const;
	UFUNCTION()
		void FireInDirection(const FVector& ShootDirection);
};
