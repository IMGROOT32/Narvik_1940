//  Copyright 2026. HyunJun. All rights reserved.


#include "BTService_UpdateBlackboard.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AICharacterBase.h"

UBTService_UpdateBlackboard::UBTService_UpdateBlackboard()
{
	NodeName = TEXT("Update Blackboard");
	Interval = 0.5f;
}

void UBTService_UpdateBlackboard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	if (!AIC) return;

	AAICharacterBase* AIChar = Cast<AAICharacterBase>(AIC->GetPawn());
	if (!AIChar) return;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return;

	BB->SetValueAsObject(TargetActorKey.SelectedKeyName, AIChar->GetTargetActor());
	BB->SetValueAsBool(IsAliveKey.SelectedKeyName, AIChar->GetIsAlive());
}
