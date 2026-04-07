//Copyright 2026. HyunJun.All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle UMETA(DisplayName = "Rifle"),
	SMG UMETA(DisplayName = "SMG"),
	Pistol UMETA(DisplayName = "Pistol")
};

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	Primary UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary")
};

UCLASS()
class NARVIK1940_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* WeaponSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	EWeaponSlot WeaponSlot;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Weight = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float WeaponRecoilPitch = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float WeaponRecoilYaw = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FVector WeaponOffSet = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FRotator WeaponRotation = FRotator::ZeroRotator;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FVector WeaponScale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MagazineSize = 30;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	int32 CurrentAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 ReserveAmmo = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool bRequiresBothArms = true;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	bool bIsReloading = false;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	float ReloadTime = 1.5f;
	FTimerHandle ReloadTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bShowDebugTrace = true;

	virtual void BeginPlay() override;
	void FinishReload();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UAnimInstance> WeaponAnimClass;
	
	FVector GetScopeSocketLocation() const;

	virtual void OnEquip();
	virtual void OnUnEquip();
	virtual void Fire();
	virtual void Reload();

	EWeaponSlot GetWeaponSlot() const { return WeaponSlot; }
	float GetWeight() const { return Weight; }
	bool GetRequiresBothArms() const { return bRequiresBothArms; }
	int32 GetCurrentAmmo() const { return CurrentAmmo; }
	int32 GetReserveAmmo() const { return ReserveAmmo; }
	bool GetIsReloading() const { return bIsReloading; }
	float GetRecoilPitch() const { return WeaponRecoilPitch; }
	float GetRecoilYaw() const { return WeaponRecoilYaw; }
};
