//Copyright 2026. HyunJun.All rights reserved.
#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	RootComponent = WeaponSkeletalMesh;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	WeaponStaticMesh->SetupAttachment(RootComponent);
	WeaponStaticMesh->SetVisibility(false);

}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
}

void AWeaponBase::OnEquip()
{
	WeaponSkeletalMesh->SetVisibility(true);
	WeaponStaticMesh->SetVisibility(true);
	WeaponSkeletalMesh->SetRelativeLocation(WeaponOffSet);
	WeaponSkeletalMesh->SetRelativeRotation(WeaponRotation);
	WeaponSkeletalMesh->SetRelativeScale3D(WeaponScale);
	UE_LOG(LogTemp, Warning, TEXT("WeaponOffset: %s"), *WeaponOffSet.ToString());
	UE_LOG(LogTemp, Warning, TEXT("WeaponRotation: %s"), *WeaponRotation.ToString());

}

void AWeaponBase::OnUnEquip()
{
	WeaponSkeletalMesh->SetVisibility(false);
	WeaponStaticMesh->SetVisibility(false);
}

void AWeaponBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("WeaponBase Fire Called"));
}

void AWeaponBase::Reload()
{
	if (bIsReloading) return;
	if (CurrentAmmo == MagazineSize) return;
	if (ReserveAmmo <= 0) return;

	bIsReloading = true;
	UE_LOG(LogTemp, Warning, TEXT("Reloading"));

	GetWorldTimerManager().SetTimer(ReloadTimer, this, &AWeaponBase::FinishReload,
		ReloadTime, false);
}

void AWeaponBase::FinishReload()
{
	int32 AmmoNeeded = MagazineSize - CurrentAmmo;
	int32 AmmoToAdd = FMath::Min(AmmoNeeded, ReserveAmmo);

	CurrentAmmo += AmmoToAdd;
	ReserveAmmo -= AmmoToAdd;

	bIsReloading = false;
	UE_LOG(LogTemp, Warning, TEXT("Reload Complete : Ammo : %d / %d"), CurrentAmmo, ReserveAmmo)
}
