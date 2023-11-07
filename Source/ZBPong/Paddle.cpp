// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerPaddle = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Paddle"));
	VisualMeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VisualMeshRoot"));
	VisualMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh1"));
	VisualMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh2"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	PlayerPaddle->SetCollisionProfileName("BlockAll");
	PlayerPaddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(PlayerPaddle);
	PlayerPaddle->SetBoxExtent(FVector(5.f, 160.f, 60.f));

	VisualMeshRoot->SetupAttachment(RootComponent);
	VisualMesh1->SetupAttachment(VisualMeshRoot);
	VisualMesh1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VisualMesh1->SetCollisionProfileName(TEXT("IgnoreAll"));
	VisualMesh2->SetupAttachment(VisualMeshRoot);
	VisualMesh2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VisualMesh2->SetCollisionProfileName(TEXT("IgnoreAll"));


	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	

}

void APaddle::Slide(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorUpVector() * Amount);

	
}

float APaddle::GetCurrentVelocity() const
{
	return currentVelocity;
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector LastInputVector = GetLastMovementInputVector() + FloatingPawnMovement->Velocity;
	LastInputVector.Normalize(0.0001f);

	FVector direction = LastInputVector * DeltaTime;
	FRotator rotation(direction.X * -1, 0, direction.Y);


}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Slide", this, &APaddle::Slide);

}

