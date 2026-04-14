// Copyright 2026. HyunJun. All rights reserved.

#include "NarvikAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"

void UNarvikAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter)
	{
		USkeletalMeshComponent* MeshComp = GetSkelMeshComponent();
		if (MeshComp)
		{
			OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		}
	}

	if (!OwnerCharacter) return;

	MovementSpeed = OwnerCharacter->GetVelocity().Size();
	bIsInAir = OwnerCharacter->GetCharacterMovement()->IsFalling();
	bIsFiring = OwnerCharacter->bIsFiring;
	bIsReloading = OwnerCharacter->GetCurrentWeapon() ?
				   OwnerCharacter->GetCurrentWeapon()->GetIsReloading() : false;
	bIsSprinting = OwnerCharacter->bIsSprinting;

	if (OwnerCharacter->GetCurrentWeapon())
	{
		USkeletalMeshComponent* WeaponMesh =
			OwnerCharacter->GetCurrentWeapon()->GetWeaponSkeletalMesh();
		if (WeaponMesh)
		{
			LeftHandTransform = WeaponMesh->GetSocketTransform(TEXT("LeftHandSocket"), RTS_World);
		}
	}

	float RawPitch = OwnerCharacter->GetControlRotation().Pitch;
	AimPitch = RawPitch > 180.f ? RawPitch - 360.f : RawPitch;
}
