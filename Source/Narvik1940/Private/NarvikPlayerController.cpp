// Copyright 2026. HyunJun. All rights reserved.

#include "NarvikPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ANarvikPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetupEnhancedInput();
}

void ANarvikPlayerController::SetupEnhancedInput()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}
}
