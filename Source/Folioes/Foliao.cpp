// Fill out your copyright notice in the Description page of Project Settings.


#include "Foliao.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FoliaoFollowerAI.h"

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
	const FVector UpDown = GetActorRightVector();
	//UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *MovementVector.ToString(), *UpDown.ToString());
	AddMovementInput(UpDown, MovementVector.X);
}

float AFoliao::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (LastFollower == nullptr)
	{
		// TODO: Game Over
	} else
	{
		// TODO: Blink Meshes (?)
		LastFollower->Kill(DamageAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AFoliao::AddFollower(int Amount)
{
	UWorld* World = GetWorld();
	
	if (World == nullptr) return;
	
	for (int i = 0; i < Amount; i++) {
		// TODO: Spawn behind foliao

		const AActor* Reference = this;

		if (LastFollower != nullptr)
		{
			Reference  = LastFollower;
		}
		
		FVector Location(Reference->GetActorLocation() + Reference->GetActorForwardVector() * -10);
		FActorSpawnParameters SpawnParameters;
		
		AActor* Actor = World->SpawnActor<AActor>(FollowerClass, Location, GetActorRotation(), SpawnParameters);

		if (AFoliaoFollowerAI* Follower = Cast<AFoliaoFollowerAI>(Actor))
		{
			if (LastFollower == nullptr)
			{
				Follower->SetTarget(this);
			} else
			{
				Follower->SetTarget(LastFollower);
			}
			
			LastFollower = Follower;
		}
	}
}
