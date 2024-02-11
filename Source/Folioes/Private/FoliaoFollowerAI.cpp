// Fill out your copyright notice in the Description page of Project Settings.


#include "FoliaoFollowerAI.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
}

// Called when the game starts or when spawned
void AFoliaoFollowerAI::BeginPlay()
{
	Super::BeginPlay();
	
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

