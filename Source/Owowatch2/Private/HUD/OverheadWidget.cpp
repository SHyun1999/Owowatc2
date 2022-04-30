// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString RoleText, FString NameText)
{

	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(RoleText));
	}

	if (NameDisplayText)
	{
		NameDisplayText->SetText(FText::FromString(NameText));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{

	ENetRole LocalRole = InPawn->GetLocalRole();

	FString Role;

	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString("Authority");
		break;

	case ENetRole::ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;

	case ENetRole::ROLE_AutonomousProxy:
		Role = FString("Autonomous Proxy");
		break;

	case ENetRole::ROLE_None:
		Role = FString("cheater?");
		break;
	}

	const APlayerState* PlayerState = InPawn->GetPlayerState();
	FString PlayerName = "";

	if (PlayerState)
	{
		PlayerName = PlayerState->GetPlayerName();
	}

	SetDisplayText(Role, PlayerName);
}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}


