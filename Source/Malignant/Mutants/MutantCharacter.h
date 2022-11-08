// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "../MalignantEnums.h"
#include "MutantCharacter.generated.h"

//Forward Declarations


//This is an abstract class for all mutants to inherit from
UCLASS()
class MALIGNANT_API AMutantCharacter : public APlayerCharacter
{
	GENERATED_BODY()


	/* methods */
public:

	AMutantCharacter();

	//Base methods to be overridden in mutant subclasses
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Interact() override;

	virtual FName GetName();

	//Attack method
	virtual void Attack() override;


	/* members */
public:



	/* methods */
protected:



	/* members */
protected:

	FName Label = "MutantBase";


	/* methods */
private:


	/* members */
private:



	

	
};
