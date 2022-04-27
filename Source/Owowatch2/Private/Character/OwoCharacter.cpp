// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OwoCharacter.h"

// Sets default values
AOwoCharacter::AOwoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOwoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOwoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOwoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

