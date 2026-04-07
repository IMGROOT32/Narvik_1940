// Copyright 2026. HyunJun. All rights reserved.


#include "WeaponRifle.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "AI/AICharacterBase.h"
#include "CharacterBase.h"

AWeaponRifle::AWeaponRifle()
{
	WeaponType = EWeaponType::Rifle;
	WeaponSlot = EWeaponSlot::Primary;
	MagazineSize = 5;
	ReserveAmmo = 20;
	ReloadTime = 2.5f;
	bRequiresBothArms = true;
}

void AWeaponRifle::Fire()
{
	if (!bCanFire) return;

	if (CurrentAmmo <= 0)
	{
		APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwner());
		if (PC) PC->bIsFiring = false;
		return;
	}

	bCanFire = false;
	CurrentAmmo--;

	GetWorldTimerManager().SetTimer(
		BoltActionTimer, this, &AWeaponRifle::ResetBoltAction,
		BoltActionTime, false);

	APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController());
	if (!PC) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector TraceEnd = CameraLocation + CameraRotation.Vector() * Range;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd,
		ECC_Visibility, Params);

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *HitResult.GetActor()->GetName());

		AAICharacterBase* HitAI = Cast<AAICharacterBase>(HitResult.GetActor());
		if (HitAI)
		{
			FName BoneName = HitResult.BoneName;
			EBodyPart BodyPart = EBodyPart::Chest;

			if (BoneName == "head") BodyPart = EBodyPart::Head;
			else if (BoneName == "upperarm_l" || BoneName == "lowerarm_l") BodyPart = EBodyPart::LeftArm;
			else if (BoneName == "upperarm_r" || BoneName == "lowerarm_r") BodyPart = EBodyPart::RightArm;
			else if (BoneName == "thigh_l" || BoneName == "calf_l") BodyPart = EBodyPart::LeftLeg;
			else if (BoneName == "thigh_r" || BoneName == "calf_r") BodyPart = EBodyPart::RightLeg;

			HitAI->TakeDamageByPart(BodyPart, Damage);
			UE_LOG(LogTemp, Warning, TEXT("Bone: %s, Damage: %.1f"), *BoneName.ToString(), Damage);
		}

		if (bShowDebugTrace)
		{
			DrawDebugLine(GetWorld(), CameraLocation, HitResult.ImpactPoint, FColor::Blue,
				false, 2.0f, 0, 1.0f);
		}
	}
	else
	{
		if (bShowDebugTrace)
		{
			DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Red);
		}
	}
}

void AWeaponRifle::ResetBoltAction()
{
	bCanFire = true;

	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwner());
	if (PC)
	{
		PC->bIsFiring = false;
	}
}
