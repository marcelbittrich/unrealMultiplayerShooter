// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverHeadWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverHeadWidget::SetNameText(const FString& Name)
{
	if (NameText)
	{
		NameText->SetText(FText::FromString(Name));
	}
}

void UOverHeadWidget::SetDisplayText(const FString& TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverHeadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	// Configure Network Role Text
	ENetRole NetRole = InPawn->GetLocalRole();
	FString Role;
	switch (NetRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;
	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;
	case ROLE_None:
		Role = FString("None");
		break;
	default:
		Role = FString("Default");
		break;
	}
	FString RoleString = FString::Printf(TEXT("Local Role: %s"), *Role);
	SetDisplayText(RoleString);

	// Set Player Name
	APlayerState* PlayerState = GetOwningPlayerState();
	if (PlayerState)
	{
		FString Name = PlayerState->GetPlayerName();
		SetNameText(Name);
	}
}

void UOverHeadWidget::ShowPlayerName(APawn* InPawn)
{
	// Set Player Name
	APlayerState* PlayerState = GetOwningPlayerState();
	if (PlayerState)
	{
		FString Name = PlayerState->GetPlayerName();
		SetNameText(Name);
		SetDisplayText(FString(""));
	}
}

void UOverHeadWidget::NativeConstruct()
{
	RemoveFromParent();
	Super::NativeConstruct();
}
