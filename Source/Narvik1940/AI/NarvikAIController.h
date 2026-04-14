//  Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NarvikAIController.generated.h"

/**
 * 
 */
UCLASS()
class NARVIK1940_API ANarvikAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ANarvikAIController();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	FName TargetActorKey = TEXT("TargetActor");
	FName IsAliveKey = TEXT("IsAlive");

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
};
