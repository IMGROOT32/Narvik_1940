// Copyright 2026. HyunJun. All rights reserved.


#include "WeaponRifle.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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
