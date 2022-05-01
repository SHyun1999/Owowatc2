// Fill out your copyright notice in the Description page of Project Settings.


#include "OwoAnimInstance.h"
#include "Character/OwoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UOwoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwoCharacter = Cast<AOwoCharacter>(TryGetPawnOwner());
}

void UOwoAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (OwoCharacter == nullptr)
	{
		OwoCharacter = Cast<AOwoCharacter>(TryGetPawnOwner());
	}
	if (OwoCharacter == nullptr) return;

	FVector Velocity = OwoCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = OwoCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = OwoCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	bWeaponEquipped = OwoCharacter->IsWeaponEquipped();
	bIsCrouched = OwoCharacter->bIsCrouched;
}