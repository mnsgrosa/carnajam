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
	PrimaryActorTick.bCanEverTick = true;

	DetectPlayerCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	DetectPlayerCollisionSphere->SetupAttachment(RootComponent);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 590.0f;
	CountdownTime = 3;

	AIControllerClass = AAIController::StaticClass();
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

void AFoliaoFollowerAI::BeginPlay()
{
	Super::BeginPlay();

	FollowerController = Cast<AAIController>( GetController());
}

void AFoliaoFollowerAI::MoveToTarget()
{
	if (FollowingTarget == nullptr) return;
	if (FollowerController == nullptr) return;

	FAIMoveRequest MoveRequest;
	
	FVector GoalLocation = GetActorLocation();
	GoalLocation.X = FollowingTarget->GetActorLocation().X;
	MoveRequest.SetGoalLocation(GoalLocation);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);

	FNavPathSharedPtr NavPath;
	FollowerController->MoveTo(MoveRequest, &NavPath);
	
	UE_LOG(LogTemp, Warning, TEXT("MoveToTarget"));
	if (NavPath.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("NavPath OK"));
		TArray<FNavPathPoint>& PathPoints = NavPath->GetPathPoints();
		for (auto& Point : PathPoints) {
			const FVector& Location = Point.Location;
			DrawDebugSphere(GetWorld(), Location, 12.f, 12, FColor::Green, false, 5.f);
		}
	}
}

// Called every frame
void AFoliaoFollowerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToTarget();
}

// Called to bind functionality to input
void AFoliaoFollowerAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}