// Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "WeaponSMG.generated.h"

/**
 *
 */
UCLASS()
class NARVIK1940_API AWeaponSMG : public AWeaponBase
{
	GENERATED_BODY()

public:
	AWeaponSMG();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Damage = 35.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float HeadShotMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Range = 2000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float FireRate = 0.1f;

	bool bIsFiring = false;
	FTimerHandle FireTimer;

public:
	virtual void Fire() override;
	void StopFire();

private:
	void FireOnce();
};
