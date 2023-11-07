// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Paddle.h"
#include "AI_Paddle.h"
#include "PongGameState.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionPong = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionPong"));
	VisualMeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VisualMeshRoot"));
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	//CollisionPong->SetCollisionProfileName("Pong");
	CollisionPong->SetCollisionProfileName("BlockAll");
	CollisionPong->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	SetRootComponent(CollisionPong);
	VisualMeshRoot->SetupAttachment(RootComponent);
	VisualMesh->SetupAttachment(VisualMeshRoot);
	
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VisualMesh->SetCollisionProfileName(TEXT("IgnoreAll"));
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PMComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	PMComp->SetUpdatedComponent(CollisionPong);
	PMComp->InitialSpeed = 0.0f;
	PMComp->MaxSpeed = 300.f;
	PMComp->bRotationFollowsVelocity = false;
	PMComp->bShouldBounce = true;
	PMComp->Bounciness = 1.f;
	PMComp->ProjectileGravityScale = 0.f;
	


}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	//FireInDirection(FVector(-1.f, 0.f, 0.f));
	CollisionPong->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnCollisionPongBeginOverlap);
	CollisionPong->OnComponentHit.AddDynamic(this, &ABall::OnCollisionPongHit);
	
	//GetWorld()->GetTimerManager().SetTimer(StartGameTimerHandle, this, &ABall::StartGameTimer, 5, false);

}

void ABall::OnCollisionPongHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	hits += 3;
	PMComp->MaxSpeed += hits;
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		
		FVector ReflectedVelocity;

		if (APaddle* Paddle = Cast<APaddle>(OtherActor)) {
			float PaddleVelocity = Paddle->GetCurrentVelocity();
			
			FVector direction = FVector(10.f, 0.f, PaddleVelocity);
			ReflectedVelocity = direction * (PMComp->MaxSpeed);
		}
		else if (AAI_Paddle* AI_Paddle = Cast<AAI_Paddle>(OtherActor)) 
		{
			
			float PaddleVelocity = AI_Paddle->GetCurrentVelocity();
			FVector direction = FVector(-10.f, 0.f, PaddleVelocity);
			ReflectedVelocity = direction * (PMComp->MaxSpeed);
		}
		else {
			FVector BallVelocity = PMComp->Velocity;
			ReflectedVelocity = FVector(BallVelocity.X, BallVelocity.Y, -BallVelocity.Z) * PMComp->MaxSpeed;

		}

		if (ReflectedVelocity.Z == 0.f) {
			float random = FMath::RandRange(-4.f, 4.f);

			if (random < 0.f) {
				ReflectedVelocity.Z = -4.f * (PMComp->MaxSpeed + hits);
			}
			else {
				ReflectedVelocity.Z = 4.f * (PMComp->MaxSpeed + hits);
			}

		}
		
		PMComp->Velocity = ReflectedVelocity;
		


	}
}

void ABall::OnCollisionPongBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ABall::StartGameTimer()
{
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABall::FireInDirection(const FVector& ShootDirection)
{
	PMComp->Velocity = ShootDirection * PMComp->MaxSpeed;
}

FVector ABall::GetVelocity() const
{
	return PMComp->Velocity;
}

