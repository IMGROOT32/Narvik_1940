// Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NarvikPlayerController.generated.h"


UCLASS()
class NARVIK1940_API ANarvikPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;

	virtual void BeginPlay() override;

private:
	void SetupEnhancedInput();
};
