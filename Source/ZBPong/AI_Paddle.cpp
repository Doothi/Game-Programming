// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Paddle.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AAI_Paddle::AAI_Paddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPaddle = CreateDefaultSubobject<UBoxComponent>(TEXT("AIPaddle"));
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	AIPaddle->SetCollisionProfileName("BlockAll");
	AIPaddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(AIPaddle);
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	AIPaddle->SetCollisionProfileName("Pawn");
	VisualMesh->SetupAttachment(AIPaddle);
	VisualMesh->SetCollisionProfileName("NoCollision");

	currentVelocity = 0.f;
}

// Called when the game starts or when spawned
void AAI_Paddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Paddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//if (RealBall) {
		//if (RealBall->GetVelocity().Y > 0.f) {
			float location = BallLocation();

			if (location > GetActorLocation().Z) {
				MoveAI(1.f);

			}
			else if (location < GetActorLocation().Z) {
				MoveAI(-1.f);
			}
			else {
				MoveAI(0.f);
			}
		//}
	//}
}

// Called to bind functionality to input
void AAI_Paddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &AAI_Paddle::MoveAI);

}

float AAI_Paddle::BallLocation() const
{
	float location = 0.f;
	FVector PaddleLoc = GetActorLocation();

	FVector BallLocation = RealBall->GetActorLocation();

	FVector BallVelocity = RealBall->GetVelocity();

	float newLocation = (PaddleLoc.Y - BallLocation.Y);

	location = BallVelocity.Z * newLocation + BallLocation.Z;


	return location;
}

void AAI_Paddle::MoveAI(float value)
{
	if (value != 0.f) {

		float temp = 100.f;

		FVector Direction = FVector(0.f, 0.f, value);

		FloatingPawnMovement->AddInputVector(Direction);


	}
}

//AAI_Paddle AAI_Paddle::getAIPaddle()
//{
//	return;
//}

void AAI_Paddle::SetBall(ABall* Ball)
{
	this->RealBall = Ball;
}

float AAI_Paddle::GetCurrentVelocity()
{
	return currentVelocity;
}

