//  Copyright 2026. HyunJun. All rights reserved.


#include "AI/NarvikAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ANarvikAIController::ANarvikAIController()
{
	bWantsPlayerState = false;
}

void ANarvikAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ANarvikAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (Blackboard)
	{
		Blackboard->SetValueAsBool(IsAliveKey, true);
		Blackboard->SetValueAsObject(TargetActorKey, nullptr);
	}
}

