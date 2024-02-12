// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FoliaoWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class FOLIOES_API UFoliaoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateFollowersCount(int Count);

	UFUNCTION(BlueprintCallable)
	void UpdateScore(int Score);
	

private:
	UFoliaoWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnClickPauseButton();
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FollowersCountTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PauseButton;
};
