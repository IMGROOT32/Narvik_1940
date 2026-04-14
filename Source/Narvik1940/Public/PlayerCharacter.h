// Copyright 2026. HyunJun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "WeaponBase.h"
#include "InputActionValue.h"
#include "NarvikTeam.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.generated.h"

class UInputAction;

UCLASS()
class NARVIK1940_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FPSCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMeshComponent* ArmsMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Sprint;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Crouch;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float LookSensitivity = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Fire;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Reload;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	float MovementSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	bool bIsInAir = false;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase> PrimaryWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase>SecondaryWeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	AWeaponBase* PrimaryWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	AWeaponBase* SecondaryWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	AWeaponBase* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_PrimaryWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_SecondaryWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilRecoverySpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AimSway")
	float AimSwayIntensity = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AimSway")
	float AimSwaySpeed = 2.0f;

	FRotator RecoilTarget = FRotator::ZeroRotator;
	FTimerHandle RecoilRecoveryTimer;
	FTimerHandle AimSwayTimer;

	UPROPERTY(EditDefaultsOnly, Category = "ADS")
	float ADSSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "ADS")
	float ADSFOV = 75.0f;

	UPROPERTY(EditDefaultsOnly, Category = "ADS")
	float DefaultFOV = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "ADS")
	bool bIsADS = false;

	FTimerHandle ADSTimer;

	UPROPERTY(EditDefaultsOnly, Category = "ADS")
	UInputAction* IA_ADS;

	FVector DefaultCameraOffset;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY()
	UUserWidget* CrosshairWidget;

	void CameraSet();
	void MeshSet();
	void MovementSet();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SprintStart(const FInputActionValue& Value);
	void SprintEnd(const FInputActionValue& Value);
	void CrouchStart(const FInputActionValue& Value);
	void CrouchEnd(const FInputActionValue& Value);

	void EquipWeapon(AWeaponBase* Weapon);
	void SwitchToPrimary(const FInputActionValue& Value);
	void SwitchToSecondary(const FInputActionValue& Value);

	void FireStart(const FInputActionValue& Value);
	void FireEnd(const FInputActionValue& Value);
	void StartReload(const FInputActionValue& Value);
	void ApplyRecoil();
	void RecoverRecoil();
	void AimSway();
	void ADSStart(const FInputActionValue& Value);
	void ADSEnd(const FInputActionValue& Value);
	void UpdateADS();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Anim")
	bool bIsFiring = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsSprinting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Team")
	ETeam PlayerTeam = ETeam::British;

	AWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }

	void SetAimSwayIntensity(float Intensity);
	virtual void Tick(float DeltaTime) override;
};
