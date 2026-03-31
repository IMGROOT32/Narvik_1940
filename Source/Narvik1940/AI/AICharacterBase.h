//  Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "NarvikTeam.h"
#include "Perception/AIPerceptionComponent.h"
#include "AICharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class NARVIK1940_API AAICharacterBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	AAICharacterBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	ETeam Team = ETeam::German;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	bool bIsAlive = true;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	AActor* TargetActor = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SightRadius = 1500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SightAngle = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float LoseSightRadius = 2000.0f;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	bool IsEnemy(AActor* Actor) const;

public:
	virtual void OnDead() override;

	ETeam GetTeam() const { return Team; }
	bool GetIsAlive() const { return bIsAlive; }
	AActor* GetTargetActor() const { return TargetActor; }
};
