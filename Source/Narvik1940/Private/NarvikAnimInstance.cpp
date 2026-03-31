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
			UE_LOG(LogTemp, Warning, TEXT("OwnerCharacter : %s"),
				OwnerCharacter ? TEXT("Found") : TEXT("NULL"))
		}
	}

	if (!OwnerCharacter) return;

	MovementSpeed = OwnerCharacter->GetVelocity().Size();
	bIsInAir = OwnerCharacter->GetCharacterMovement()->IsFalling();
	bIsFiring = OwnerCharacter->bIsFiring;
	bIsReloading = OwnerCharacter->GetCurrentWeapon() ?
		OwnerCharacter->GetCurrentWeapon()->GetIsReloading() : false;
	bIsSprinting = OwnerCharacter->bIsSprinting;
}
