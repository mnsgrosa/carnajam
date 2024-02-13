// Fill out your copyright notice in the Description page of Project Settings.


#include "Foliao.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FoliaoFollowerAI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/FoliaoWidget.h"

// Sets default values
AFoliao::AFoliao()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	
	CountdownTime = 3;
	//GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AFoliao::AdvanceTimer, 1.0f, true);

	if (const UWorld* World = GetWorld(); WidgetClass && World)
	{
		FoliaoWidget = CreateWidget<UFoliaoWidget>(UGameplayStatics::GetPlayerController(World, 0), WidgetClass, TEXT("InteractionUI"));
		FoliaoWidget->AddToViewport(0);
		FoliaoWidget->UpdateFollowersCount(1);
		FoliaoWidget->UpdateScore(0);
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
		FollowerCount -= DamageAmount;
		FoliaoWidget->UpdateFollowersCount(FollowerCount);
		LastFollower->Kill(DamageAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AFoliao::AddFollower(int Amount)
{
	FollowerCount += Amount;
	FoliaoWidget->UpdateFollowersCount(FollowerCount);

	UWorld* World = GetWorld();
	
	if (World == nullptr) return;
	
	for (int i = 0; i < Amount; i++) {
		const AActor* Reference = this;

		if (LastFollower != nullptr)
		{
			Reference  = LastFollower;
		}
		
		FVector Location(Reference->GetActorLocation() + Reference->GetActorForwardVector() * -10);
		FActorSpawnParameters SpawnParameters;
		
		ACharacter* FollowerCharacter = World->SpawnActor<ACharacter>(FollowerClass, Location, GetActorRotation(), SpawnParameters);
		
		FollowerCharacter->SpawnDefaultController();
		
		if (AFoliaoFollowerAI* Follower = Cast<AFoliaoFollowerAI>(FollowerCharacter))
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


void AFoliao::AdvanceTimer() {
	if (CountdownTime < 1) {
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

void AFoliao::CountdownHasFinished()
{
	AddFollower(10);
}
