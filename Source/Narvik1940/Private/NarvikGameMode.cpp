// Copyright 2026. HyunJun. All rights reserved.

#include "NarvikGameMode.h"
#include "CharacterBase.h"
#include "NarvikPlayerController.h"


ANarvikGameMode::ANarvikGameMode()
{
	DefaultPawnClass = ACharacterBase::StaticClass();
	PlayerControllerClass = ANarvikPlayerController::StaticClass();
}