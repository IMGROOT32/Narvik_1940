// Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "WeaponRifle.generated.h"

/**
 *
 */
UCLASS()
class NARVIK1940_API AWeaponRifle : public AWeaponBase
{
	GENERATED_BODY()

public:
	AWeaponRifle();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Damage = 75.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float HeadShotMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Range = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BoltActionTime = 2.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool bCanFire = true;

	FTimerHandle BoltActionTimer;

	void ResetBoltAction();

public:
	virtual void Fire() override;
};
