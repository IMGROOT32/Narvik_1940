// Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NarvikAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class NARVIK1940_API UNarvikAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	float MovementSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	bool bIsInAir = false;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	bool bIsFiring = false;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	bool bIsReloading = false;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	bool bIsSprinting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	FTransform LeftHandTransform;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	float AimPitch = 0.0f;

private:
	UPROPERTY()
	class APlayerCharacter* OwnerCharacter;
};
