// Fill out your copyright notice in the Description page of Project Settings.


#include "Folioes/Public/Obstacle.h"

#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "Folioes/Foliao.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	RootComponent = Mesh;
	BoxCollision->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnBoxBeginOverlap);

}

void AObstacle::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AFoliao* Foliao = Cast<AFoliao>(OtherActor))
	{
		if (Operation == EOperation::Subtract)
		{
			Foliao->TakeDamage(Amount, FDamageEvent(), GetInstigatorController(), this);
		}
		else if (Operation == EOperation::Sum)
		{
			//Foliao->AddFollower(Amount);
		}
	}
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Forward = GetActorForwardVector();
	AddActorWorldOffset( Forward * Speed * DeltaTime);
}

