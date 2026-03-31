//Copyright 2026. HyunJun.All rights reserved.

#include "CharacterBase.h"

#include "Algo/Contains.h"
#include "Chaos/PBDRigidsSOAs.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	BodyPartMaxHP = BodyPartHP;
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterBase::TakeDamageByPart(EBodyPart BodyPart, float Damage)
{
	if (!BodyPartHP.Contains(BodyPart)) return;

	float& HP = BodyPartHP[BodyPart];
	HP = FMath::Max(0.0f, HP - Damage);

	UE_LOG(LogTemp, Warning, TEXT("BodyPart : %d, HP : %.1f"), (int32)BodyPart, HP);

	UpdateBodyPartStatus(BodyPart);

	if (BodyPart == EBodyPart::Head || BodyPart == EBodyPart::Chest)
	{
		if (HP <= 0.0f) OnDead();
	}
}

void ACharacterBase::UpdateBodyPartStatus(EBodyPart BodyPart)
{
	if (!BodyPartHP.Contains(BodyPart)) return;

	float HP = BodyPartHP[BodyPart];
	float MaxHP = BodyPartMaxHP.Contains(BodyPart) ? BodyPartMaxHP[BodyPart] : 1.0f;

	EBodyStatus NewStatus;

	if (HP <= 0.0f)
	{
		NewStatus = EBodyStatus::Disabled;
	}
	else if (HP / MaxHP <= InjuredThreshold)
	{
		NewStatus = EBodyStatus::Injured;
	}
	else
	{
		NewStatus = EBodyStatus::Normal;
	}

	BodyPartStatus[BodyPart] = NewStatus;
	ApplyInjuryPenalty(BodyPart, NewStatus);
}

void ACharacterBase::ApplyInjuryPenalty(EBodyPart BodyPart, EBodyStatus Status)
{
	switch (BodyPart)
	{
	case EBodyPart::LeftArm:
	case EBodyPart::RightArm:
		if (Status == EBodyStatus::Disabled)
		{
			if (BodyPartStatus[EBodyPart::LeftArm] == EBodyStatus::Disabled &&
				BodyPartStatus[EBodyPart::RightArm] == EBodyStatus::Disabled)
			{
				OnDead();
			}
		}
		OnArmInjury(BodyPart, Status);
		break;

	case EBodyPart::LeftLeg:
	case EBodyPart::RightLeg:
		if (Status == EBodyStatus::Injured)
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		}
		else if (Status == EBodyStatus::Disabled)
		{
			GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;

			if (BodyPartStatus[EBodyPart::LeftLeg] == EBodyStatus::Disabled &&
				BodyPartStatus[EBodyPart::RightLeg] == EBodyStatus::Disabled)
			{
				OnDead();
			}
		}
		break;

	default:
		break;
	}
}

void ACharacterBase::OnDead()
{
}

EBodyStatus ACharacterBase::GetBodyPartStatus(EBodyPart BodyPart) const
{
	if (BodyPartStatus.Contains(BodyPart))
	{
		return BodyPartStatus[BodyPart];
	}
	return EBodyStatus::Normal;
}

float ACharacterBase::GetBodyPartHP(EBodyPart BodyPart) const
{
	if (BodyPartHP.Contains(BodyPart))
	{
		return BodyPartHP[BodyPart];
	}
	return 0.0f;
}
