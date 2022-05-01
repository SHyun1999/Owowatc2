// Fill out your copyright notice in the Description page of Project Settings.


#include "OwoComponents/CombatComponent.h"
#include "Owowatch2/Public/Weapon/Weapon.h"
#include "Owowatch2/Public/Character/OwoCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"


UCombatComponent::UCombatComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCombatComponent::SetAiming(bool bIsAiming)
{
	bAiming = bIsAiming; // replicate right away to display the pose immediately

	ServerSetAiming(bIsAiming); // if on server, it'll run there. if on client, it will be executed on the client.
}

void UCombatComponent::OnRep_EquippedWeapon()
{

	if (EquippedWeapon && Char)
	{
		Char->GetCharacterMovement()->bOrientRotationToMovement = false;
		Char->bUseControllerRotationYaw = true;
	}
}

void UCombatComponent::ServerSetAiming_Implementation(bool bIsAiming)
{
	bAiming = bIsAiming;
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, EquippedWeapon);
	DOREPLIFETIME(UCombatComponent, bAiming);
}



void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (Char == nullptr || WeaponToEquip == nullptr) return;

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	const USkeletalMeshSocket* HandSocket = Char->GetMesh()->GetSocketByName(FName("RHandSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(EquippedWeapon, Char->GetMesh());
	}
	EquippedWeapon->SetOwner(Char);
	Char->GetCharacterMovement()->bOrientRotationToMovement = false;
	Char->bUseControllerRotationYaw = true;
}

