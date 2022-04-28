// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OwoCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AOwoCharacter::AOwoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void AOwoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOwoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &AOwoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOwoCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AOwoCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AOwoCharacter::LookUp);
}

void AOwoCharacter::MoveForward(float Value)
{
	
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AOwoCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void AOwoCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AOwoCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AOwoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

