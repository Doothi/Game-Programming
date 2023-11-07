// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Ball.h"
#include "AI_Paddle.h"
#include "PongGameState.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>


// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMeshRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("VisualMeshRoot"));
	SetRootComponent(VisualMeshRoot);
	
	Top = CreateDefaultSubobject<UBoxComponent>(TEXT("TopBoard"));
	Top->SetupAttachment(RootComponent);
	Top->SetBoxExtent(FVector(1200.f, 500.f, 100.f));

	

	Bottom = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomBoard"));
	Bottom->SetupAttachment(RootComponent);
	Bottom->SetBoxExtent(FVector(1200.f, 500.f, 100.f));
	Left = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftBoard"));
	Left->SetupAttachment(RootComponent);
	Left->SetBoxExtent(FVector(100.f, 500.f, 800.f));
	Left->SetRelativeLocation(FVector(-1090.f, 0.f, 0.f));

	Right = CreateDefaultSubobject<UBoxComponent>(TEXT("RightBoard"));
	Right->SetupAttachment(RootComponent);
	Right->SetBoxExtent(FVector(100.f, 500.f, 800.f));
	Right->SetRelativeLocation(FVector(1090.f, 0.f, 0.f));

	Top->SetCollisionProfileName("BlockAll");
	Bottom->SetCollisionProfileName("BlockAll");
	Left->SetCollisionProfileName("OverlapAll");
	Right->SetCollisionProfileName("OverlapAll");

	Top->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Bottom->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Left->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Right->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCompoent"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.f, 1300.f, 0.f));
	Camera->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->ArrowSize = 5.f;
	SpawnPoint->SetRelativeLocation(FVector(50.f, 0.f, 0.f));
	SpawnPoint->SetRelativeRotation(FRotator(0.f, 100.f, 0.f));
	
	

	AIScore = 0;
	PlayerScore = 0;



}



// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
	
	Left->OnComponentBeginOverlap.AddDynamic(this, &ABoard::OnOverlap);
	Right->OnComponentBeginOverlap.AddDynamic(this, &ABoard::OnOverlap);
	
}

void ABoard::SetCanSpawn(bool bNewCanSpawn)
{
	bCanSpawn = bNewCanSpawn;
}

void ABoard::SpawnBall()
{
	if (bCanSpawn) {
		UWorld* const World = GetWorld();

		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform SpawnTransform = SpawnPoint->GetComponentTransform();
			
			SpawnedBall = World->SpawnActor<ABall>(BallTemplate, SpawnTransform, SpawnParams);
			
			TArray<AActor*> Paddles;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_Paddle::StaticClass(), Paddles);
			for (AActor* Paddle : Paddles) {
				AI_Paddle = Cast<AAI_Paddle>(Paddle);
			}
			if (SpawnedBall) {
				if (AI_Paddle) {
					AI_Paddle->SetBall(SpawnedBall);
				}
			}
		}
		SpawnedBall->FireInDirection(FVector(-1.f, 0.f, 0.f));
		bCanSpawn = false;
	}
}

void ABoard::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent->GetName().Equals("LeftBoard")) {
		AIScore += 1;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("AI Score: %d"), AIScore));
	}
	else {
		PlayerScore += 1;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerScore: %d"), PlayerScore));
	}
	SpawnedBall->Destroy();

	bCanSpawn = true;

}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bCanSpawn) {
	SpawnBall();
	}
	

}


