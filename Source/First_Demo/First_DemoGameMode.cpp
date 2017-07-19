// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "First_DemoGameMode.h"
#include "First_DemoHUD.h"
#include "First_DemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirst_DemoGameMode::AFirst_DemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirst_DemoHUD::StaticClass();
}
