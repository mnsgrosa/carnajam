// Fill out your copyright notice in the Description page of Project Settings.


#include "FoliaoFollowerAI.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h" 
#include "AIController.h"

// Sets default values
AFoliaoFollowerAI::AFoliaoFollowerAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DetectPlayerCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	DetectPlayerCollisionSphere->SetupAttachment(RootComponent);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 590.0f;
	CountdownTime = 3;
}

void AFoliaoFollowerAI::SetTarget(AActor* Target)
{
	FollowingTarget = Target;
}

void AFoliaoFollowerAI::Kill(int Amount)
{
	// TODO: Use object pooling
	
	if (Amount - 1 > 0)
	{
		if (AFoliaoFollowerAI* Target = Cast<AFoliaoFollowerAI>(FollowingTarget))
		Target->Kill(Amount - 1);
	}
	
	Destroy();
}

// Called when the game starts or when spawned
void AFoliaoFollowerAI::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AFoliaoFollowerAI::MoveToPlayer, 1.0f, true);

	
}

void AFoliaoFollowerAI::MoveToPlayer()
{
	if (FollowingTarget == nullptr) return;

	FollowerController = Cast<AAIController>(GetController());

	if (FollowerController == nullptr) return;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(FollowingTarget);
	MoveRequest.SetAcceptanceRadius(15.f);

	FNavPathSharedPtr NavPath;
	FollowerController->MoveTo(MoveRequest, &NavPath);
	TArray<FNavPathPoint>& PathPoints = NavPath->GetPathPoints();
	for (auto& Point : PathPoints) {
		const FVector& Location = Point.Location;
		DrawDebugSphere(GetWorld(), Location, 12.f, 12, FColor::Green, false, 10.f);
	}
}



void AFoliaoFollowerAI::AdvanceTime()
{
	if (CountdownTime < 1) {
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		MoveToPlayer();
	}
}

void AFoliaoFollowerAI::CountdownHasFinished()
{
	MoveToPlayer();
}


// Called every frame
void AFoliaoFollowerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void AFoliaoFollowerAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}