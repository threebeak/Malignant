// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MutantCharacter.h"
#include "BruteMutantCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MALIGNANT_API ABruteMutantCharacter : public AMutantCharacter
{
	GENERATED_BODY()


	
public:
	ABruteMutantCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Interact() override;


public:



protected:


protected:


private:



private:
	
};
