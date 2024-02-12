// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Foliao.generated.h"

class UFoliaoWidget;
class AFoliaoFollowerAI;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class FOLIOES_API AFoliao : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFoliao();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	void AddFollower(int Amount);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* FoliaoMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	void Move(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere)
	FTimerHandle CountdownTimerHandle;
	
	int32 CountdownTime;

	UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY()
	UFoliaoWidget* FoliaoWidget;


private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FoliaoMesh;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFoliaoFollowerAI> FollowerClass;

	UPROPERTY()
	AFoliaoFollowerAI* LastFollower;

	int FollowerCount = 1;

	void AdvanceTimer();
	void CountdownHasFinished();
};