// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Operation.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

enum EOperation : int;
class UBoxComponent;

UCLASS()
class FOLIOES_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	float Speed;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EOperation> Operation = EOperation::Sum;
	
	UPROPERTY(EditAnywhere)
	int Amount;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
