// Copyright 2026. HyunJun. All rights reserved.


#include "WeaponSMG.h"
#include "Engine/World.h"
#include "AICharacterBase.h"
#include "DrawDebugHelpers.h"

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

    APlayerController* PC = Cast<APlayerController>(GetInstigatorController());
    if (!PC) return;

    int32 ViewportX, ViewportY;
    PC->GetViewportSize(ViewportX, ViewportY);

    FVector WorldLocation, WorldDirection;
    PC->DeprojectScreenPositionToWorld(
        ViewportX / 2.0f, ViewportY / 2.0f - 40.0f,
        WorldLocation, WorldDirection);

    float SpreadX = FMath::RandRange(-SpreadAngle, SpreadAngle);
    float SpreadY = FMath::RandRange(-SpreadAngle, SpreadAngle);
    WorldDirection = WorldDirection.RotateAngleAxis(SpreadX, FVector::UpVector);
    WorldDirection = WorldDirection.RotateAngleAxis(SpreadY, FVector::RightVector);

    FVector TraceEnd = WorldLocation + WorldDirection * Range;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult, WorldLocation, TraceEnd, ECC_Visibility, Params);

    if (bHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *HitResult.GetActor()->GetName());

        AAICharacterBase* HitAI = Cast<AAICharacterBase>(HitResult.GetActor());
        if (HitAI)
        {
            FName BoneName = HitResult.BoneName;
            EBodyPart BodyPart = EBodyPart::Chest;

            if (BoneName == "head")                                         BodyPart = EBodyPart::Head;
            else if (BoneName == "upperarm_l" || BoneName == "lowerarm_l") BodyPart = EBodyPart::LeftArm;
            else if (BoneName == "upperarm_r" || BoneName == "lowerarm_r") BodyPart = EBodyPart::RightArm;
            else if (BoneName == "thigh_l" || BoneName == "calf_l")      BodyPart = EBodyPart::LeftLeg;
            else if (BoneName == "thigh_r" || BoneName == "calf_r")      BodyPart = EBodyPart::RightLeg;

            HitAI->TakeDamageByPart(BodyPart, Damage);
        }

        if (bShowDebugTrace)
        {
            DrawDebugLine(GetWorld(), WorldLocation, HitResult.ImpactPoint, FColor::Green, false, 1.0f, 0, 1.0f);
            DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 8, FColor::Green, false, 1.0f);
        }
    }
    else
    {
        if (bShowDebugTrace)
        {
            DrawDebugLine(GetWorld(), WorldLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
        }
    }
}