// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantCharacter.h"

AMutantCharacter::AMutantCharacter()
{
}

void AMutantCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMutantCharacter::Interact()
{
	//Uses APlayerCharacter::Interact
	Super::Interact();

}

FName AMutantCharacter::GetName()
{
	return Label;
}
