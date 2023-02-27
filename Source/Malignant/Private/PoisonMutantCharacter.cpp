// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonMutantCharacter.h"

APoisonMutantCharacter::APoisonMutantCharacter()
{
	Label = "Poison";
}

void APoisonMutantCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APoisonMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APoisonMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APoisonMutantCharacter::Interact()
{
	Super::Interact(); 
}
