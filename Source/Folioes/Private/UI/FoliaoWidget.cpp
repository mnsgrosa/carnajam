// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FoliaoWidget.h"

#include "Components/TextBlock.h"

UFoliaoWidget::UFoliaoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }
void UFoliaoWidget::NativeConstruct() { Super::NativeConstruct(); }

void UFoliaoWidget::UpdateFollowersCount(int Count)
{
	const FString Text = FString::FromInt(Count);
	FollowersCountTextBlock->SetText(FText::FromString(Text));
}

void UFoliaoWidget::UpdateScore(int Score)
{
	const FString Text = FString::FromInt(Score);

	ScoreTextBlock->SetText(FText::FromString(Text));
}

void UFoliaoWidget::OnClickPauseButton()
{
	// TODO: Pause Game
	// TODO: Show Paused Menu
}
