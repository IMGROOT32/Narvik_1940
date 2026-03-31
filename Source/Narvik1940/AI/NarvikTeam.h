// Copyright 2026. HyunJun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "NarvikTeam.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	German UMETA(DisplayName = "German"),
	British UMETA(DisplayName = "British"),
	Norway UMETA(DisplayName = "Norway")
};
