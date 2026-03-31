//  Copyright 2026. HyunJun. All rights reserved.


#include "AI/AICharacterBase.h"
#include "AI/NarvikAIController.h"
#include "PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"

AAICharacterBase::AAICharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = SightAngle;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(
		this, &AAICharacterBase::OnPerceptionUpdated);
}

void AAICharacterBase::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor || !bIsAlive) return;
	if (!IsEnemy(Actor)) return;

	ANarvikAIController* AIC = Cast<ANarvikAIController>(GetController());
	if (!AIC) return;
	
	if (Stimulus.WasSuccessfullySensed())
	{
		TargetActor = Actor;
		AIC->SetTargetActor(Actor);
		UE_LOG(LogTemp, Warning, TEXT("AI : Enemy Detected - %s"), *Actor->GetName());
	}
	else
	{
		TargetActor = nullptr;
		AIC->SetTargetActor(nullptr);
		UE_LOG(LogTemp, Warning, TEXT("AI : Enemy Lost"));
	}
}

bool AAICharacterBase::IsEnemy(AActor* Actor) const
{
	ETeam OtherTeam;

	APlayerCharacter* Player = Cast<APlayerCharacter>(Actor);
	AAICharacterBase* OtherAI = Cast<AAICharacterBase>(Actor);

	if (Player)
	{
		OtherTeam = Player->PlayerTeam;
	}
	else if (OtherAI)
	{
		OtherTeam = OtherAI->GetTeam();
	}
	else return false;

	if (Team == ETeam::German && OtherTeam != ETeam::German) return true;
	if (Team != ETeam::German && OtherTeam == ETeam::German) return true;

	return false;
}

void AAICharacterBase::OnDead()
{
	bIsAlive = false;

	GetCharacterMovement()->DisableMovement();
	SetActorEnableCollision(false);
	GetMesh()->SetSimulatePhysics(true);

	UE_LOG(LogTemp, Warning, TEXT("AI : Dead - %s"), *GetName());

	SetLifeSpan(5.0f);
}
