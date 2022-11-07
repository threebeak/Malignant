// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MutantCharacter.h"
#include "BoneBladeMutantCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MALIGNANT_API ABoneBladeMutantCharacter : public AMutantCharacter
{
	GENERATED_BODY()

	/* methods */
private:


	/* members */
private:



	/* methods */
public:

	ABoneBladeMutantCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Interact() override;

	/* members */
public:



	/* methods */
protected:



	/* members */
protected:



	
};
