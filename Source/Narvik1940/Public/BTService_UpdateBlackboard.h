//  Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class NARVIK1940_API UBTService_UpdateBlackboard : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateBlackboard();

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector IsAliveKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	
};
