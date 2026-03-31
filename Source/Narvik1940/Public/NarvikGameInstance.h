//  Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NarvikTeam.h"
#include "NarvikGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NARVIK1940_API UNarvikGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Team")
	ETeam SelectedTeam = ETeam::British;
};
