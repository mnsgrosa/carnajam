// Fill out your copyright notice in the Description page of Project Settings.


#include "FoliaoFollowerAI.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AFoliaoFollowerAI::AFoliaoFollowerAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectPlayerCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	DetectPlayerCollisionSphere->SetupAttachment(RootComponent);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

// Called when the game starts or when spawned
void AFoliaoFollowerAI::BeginPlay()
{
	Super::BeginPlay();
	
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

