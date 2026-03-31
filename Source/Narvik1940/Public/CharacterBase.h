// Copyright 2026. HyunJun. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UInputAction;

UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	Head UMETA(DisplayName = "Head"),
	Chest UMETA(DisplayName = "Chest"),
	LeftArm UMETA(DisplayName = "LeftArm"),
	RightArm UMETA(DisplayName = "RightArm"),
	LeftLeg UMETA(DisplayName = "LeftLeg"),
	RightLeg UMETA(DisplayName = "RightLeg")
};

UENUM(BlueprintType)
enum class EBodyStatus : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Injured UMETA(DisplayName = "Injured"),
	Disabled UMETA(DisplayName = "Disabled")
};

UCLASS()
class NARVIK1940_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 700.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float CrouchSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Health")
	TMap<EBodyPart, float> BodyPartHP =
	{
		{EBodyPart::Head, 35.0f},
		{EBodyPart::Chest, 100.0f},
		{EBodyPart::LeftArm, 60.0f},
		{EBodyPart::RightArm, 60.0f},
		{EBodyPart::LeftLeg, 70.0f},
		{EBodyPart::RightLeg, 70.0f}
	};

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	TMap<EBodyPart, EBodyStatus> BodyPartStatus =
	{
		{EBodyPart::Head, EBodyStatus::Normal},
		{EBodyPart::Chest, EBodyStatus::Normal},
		{EBodyPart::LeftArm, EBodyStatus::Normal},
		{EBodyPart::RightArm, EBodyStatus::Normal},
		{EBodyPart::LeftLeg, EBodyStatus::Normal},
		{EBodyPart::RightLeg, EBodyStatus::Normal}
	};

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float InjuredThreshold = 0.5f;

	UPROPERTY()
	TMap<EBodyPart, float> BodyPartMaxHP;

	virtual void OnArmInjury(EBodyPart BodyPart, EBodyStatus Status) {}
	virtual void BeginPlay() override;

	void UpdateBodyPartStatus(EBodyPart BodyPart);
	void ApplyInjuryPenalty(EBodyPart BodyPart, EBodyStatus Status);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void TakeDamageByPart(EBodyPart BodyPart, float Damage);
	virtual void OnDead();

	EBodyStatus GetBodyPartStatus(EBodyPart BodyPart) const;
	float GetBodyPartHP(EBodyPart BodyPart) const;
};
