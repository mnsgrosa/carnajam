// Fill out your copyright notice in the Description page of Project Settings.


#include "Policia.h"

// Sets default values
APolicia::APolicia()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APolicia::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APolicia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APolicia::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

