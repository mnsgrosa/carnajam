// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FoliaoFollowerAI.generated.h"

class USphereComponent;
class UBoxComponent;
class UAnimMontage;
class AEnemyController;
class UNavigationSystemV1;
class AActor;
class AAIController;

UCLASS()
class FOLIOES_API AFoliaoFollowerAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFoliaoFollowerAI();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	USphereComponent* GetDetectPlayerCollisionSphere();

	/*
	* Navigation
	*/
	UPROPERTY()
	AAIController FollowerController;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* FollowingTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
	USphereComponent* DetectPlayerCollisionSphere;

	APawn* PlayerPawn;
	AEnemyController* MyChar;
	UNavigationSystemV1* NavArea;
	FVector RandomLocation = FVector();

	bool bMoveToPlayer;
	void MoveToPlayer();
	void StartChasingPlayer();
};
