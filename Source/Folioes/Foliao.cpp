// Fill out your copyright notice in the Description page of Project Settings.


#include "Foliao.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AFoliao::AFoliao()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoliao::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(FoliaoMappingContext, 0);
		}
	}
	
}

// Called every frame
void AFoliao::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFoliao::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFoliao::Move);
	}
}

void AFoliao::Move(const FInputActionValue& Value) {
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, Forward.X + 5000.f);
	const FVector UpDown = GetActorRightVector();
	AddMovementInput(UpDown, MovementVector.X);
}