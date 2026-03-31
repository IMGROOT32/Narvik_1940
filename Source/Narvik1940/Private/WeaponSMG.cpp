// Copyright 2026. HyunJun. All rights reserved.


#include "WeaponSMG.h"
#include "Engine/World.h"

AWeaponSMG::AWeaponSMG()
{
	WeaponType = EWeaponType::SMG;
	WeaponSlot = EWeaponSlot::Primary;
	MagazineSize = 25;
	bRequiresBothArms = true;
}

void AWeaponSMG::Fire()
{
	if (bIsFiring || CurrentAmmo <= 0) return;

	bIsFiring = true;
	FireOnce();

	GetWorldTimerManager().SetTimer(FireTimer, this, &AWeaponSMG::FireOnce, FireRate, true);
}

void AWeaponSMG::StopFire()
{
	bIsFiring = false;
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void AWeaponSMG::FireOnce()
{
	if (CurrentAmmo <= 0)
	{
		StopFire();
		return;
	}

	CurrentAmmo--;

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
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *HitActor->GetName());
		}
	}
}
