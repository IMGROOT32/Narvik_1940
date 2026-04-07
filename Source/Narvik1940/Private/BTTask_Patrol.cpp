//  Copyright 2026. HyunJun. All rights reserved.


#include "BTTask_Patrol.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	if (!AIC) return EBTNodeResult::Failed;

	APawn* Pawn = AIC->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	bool bFound = NavSystem->GetRandomReachablePointInRadius(
		Pawn->GetActorLocation(), PatrolRadius, NavLocation);

	if (!bFound) return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(
		PatrolLocationKey.SelectedKeyName, NavLocation.Location);

	return EBTNodeResult::Succeeded;
}