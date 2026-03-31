// Copyright 2026. HyunJun. All rights reserved.


#include "PlayerCharacter.h"
#include "WeaponSMG.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraSet();
	MeshSet();
	MovementSet();
}

void APlayerCharacter::CameraSet()
{
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCamera->SetupAttachment(GetMesh(), TEXT("CameraSocket"));
	FPSCamera->bUsePawnControlRotation = true;
}

void APlayerCharacter::MeshSet()
{
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetupAttachment(RootComponent);
	ArmsMesh->bCastDynamicShadow = false;
	ArmsMesh->CastShadow = false;
	ArmsMesh->SetOnlyOwnerSee(true);
	GetMesh()->SetOwnerNoSee(true);
}

void APlayerCharacter::MovementSet()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	FPSCamera->AttachToComponent(ArmsMesh, FAttachmentTransformRules::SnapToTargetIncludingScale,
		TEXT("CameraSocket"));
	FPSCamera->SetFieldOfView(DefaultFOV);

	if (PrimaryWeaponClass)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = this;
		PrimaryWeapon = GetWorld()->SpawnActor<AWeaponBase>(PrimaryWeaponClass, Params);
	}

	if (SecondaryWeaponClass)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = this;
		SecondaryWeapon = GetWorld()->SpawnActor<AWeaponBase>(SecondaryWeaponClass, Params);
	}

	if (PrimaryWeapon)
	{
		EquipWeapon(PrimaryWeapon);
	}
	else if (SecondaryWeapon)
	{
		EquipWeapon(SecondaryWeapon);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &APlayerCharacter::SprintStart);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &APlayerCharacter::SprintEnd);
		EIC->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &APlayerCharacter::CrouchStart);
		EIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &APlayerCharacter::CrouchEnd);

		EIC->BindAction(IA_PrimaryWeapon, ETriggerEvent::Triggered, this, &APlayerCharacter::SwitchToPrimary);
		EIC->BindAction(IA_SecondaryWeapon, ETriggerEvent::Triggered, this, &APlayerCharacter::SwitchToSecondary);
		EIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &APlayerCharacter::FireStart);
		EIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &APlayerCharacter::FireEnd);
		EIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &APlayerCharacter::StartReload);
		EIC->BindAction(IA_ADS, ETriggerEvent::Started, this, &APlayerCharacter::ADSStart);
		EIC->BindAction(IA_ADS, ETriggerEvent::Completed, this, &APlayerCharacter::ADSEnd);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDir, MovementVector.Y);
		AddMovementInput(RightDir, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller)
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		AddControllerYawInput(-LookVector.X * DeltaTime * LookSensitivity);
		AddControllerPitchInput(LookVector.Y * DeltaTime * LookSensitivity);
	}
}

void APlayerCharacter::SprintStart(const FInputActionValue& Value)
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::SprintEnd(const FInputActionValue& Value)
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::CrouchStart(const FInputActionValue& Value)
{
	Crouch();
	GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}

void APlayerCharacter::CrouchEnd(const FInputActionValue& Value)
{
	UnCrouch();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::EquipWeapon(AWeaponBase* Weapon)
{
	if (!Weapon) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->OnUnEquip();
	}

	CurrentWeapon = Weapon;

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	CurrentWeapon->AttachToComponent(ArmsMesh, Rules, TEXT("hand_r_socket"));

	if (Weapon->WeaponAnimClass)
	{
		ArmsMesh->SetAnimInstanceClass(Weapon->WeaponAnimClass);
	}
	CurrentWeapon->OnEquip();
}

void APlayerCharacter::SwitchToPrimary(const FInputActionValue& Value)
{
	if (PrimaryWeapon == nullptr || CurrentWeapon == PrimaryWeapon)
	{
		return;
	}
	EquipWeapon(PrimaryWeapon);
}

void APlayerCharacter::SwitchToSecondary(const FInputActionValue& Value)
{
	if (SecondaryWeapon == nullptr || CurrentWeapon == SecondaryWeapon)
	{
		return;
	}
	EquipWeapon(SecondaryWeapon);
}

void APlayerCharacter::FireStart(const FInputActionValue& Value)
{
	if (CurrentWeapon)
	{
		if (CurrentWeapon->GetCurrentAmmo() <= 0) return;
		bIsFiring = true;
		CurrentWeapon->Fire();
		ApplyRecoil();
	}
}

void APlayerCharacter::FireEnd(const FInputActionValue& Value)
{
	if (AWeaponSMG* SMG = Cast<AWeaponSMG>(CurrentWeapon))
	{
		SMG->StopFire();
	}
}

void APlayerCharacter::StartReload(const FInputActionValue& Value)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Reload();
	}
}

void APlayerCharacter::ApplyRecoil()
{
	if (!CurrentWeapon) return;

	float Pitch = CurrentWeapon->GetRecoilPitch();
	float Yaw = FMath::RandRange(-CurrentWeapon->GetRecoilYaw(), CurrentWeapon->GetRecoilYaw());

	AddControllerPitchInput(-Pitch);
	AddControllerYawInput(Yaw);

	GetWorldTimerManager().ClearTimer(RecoilRecoveryTimer);
	GetWorldTimerManager().SetTimer(RecoilRecoveryTimer, this, &APlayerCharacter::RecoverRecoil,
		0.05f, true);
}

void APlayerCharacter::RecoverRecoil()
{
	FRotator Current = GetControlRotation();
	FRotator Target = FRotator(Current.Pitch + (Current.Pitch > 0 ? -1.0f : 0.0f),
		Current.Yaw, Current.Roll);

	Controller->SetControlRotation(FMath::RInterpTo(Current, Target,
		GetWorld()->GetDeltaSeconds(), RecoilRecoverySpeed));
}

void APlayerCharacter::SetAimSwayIntensity(float Intensity)
{
	AimSwayIntensity = Intensity;

	if (AimSwayIntensity > 0.0f)
	{
		GetWorldTimerManager().SetTimer(AimSwayTimer, this, &APlayerCharacter::AimSway,
			0.05f, true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(AimSwayTimer);
	}
}

void APlayerCharacter::AimSway()
{
	if (AimSwayIntensity <= 0.0f) return;

	float Time = GetWorld()->GetTimeSeconds();
	float PitchSway = FMath::Sin(Time * AimSwaySpeed) * AimSwayIntensity;
	float YawSway = FMath::Cos(Time * AimSwaySpeed * 0.7f) * AimSwayIntensity;

	AddControllerPitchInput(PitchSway);
	AddControllerYawInput(YawSway);
}

void APlayerCharacter::ADSStart(const FInputActionValue& Value)
{
	bIsADS = true;
	GetWorldTimerManager().SetTimer(ADSTimer, this, &APlayerCharacter::UpdateADS,
		0.016f, true);
}

void APlayerCharacter::ADSEnd(const FInputActionValue& Value)
{
	bIsADS = false;
}

void APlayerCharacter::UpdateADS()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float TargetFOV = bIsADS ? ADSFOV : DefaultFOV;

	float CurrentFOV = FPSCamera->FieldOfView;
	float NewFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, ADSSpeed);
	FPSCamera->SetFieldOfView(NewFOV);

	if (!bIsADS && FMath::IsNearlyEqual(CurrentFOV, NewFOV, 0.1f))
	{
		GetWorldTimerManager().ClearTimer(ADSTimer);
	}
}
