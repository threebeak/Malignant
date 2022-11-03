// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "MutantCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EMutantState { Human = 0, EMS_Base, EMS_Bone, EMS_FourArm };

UCLASS()
class MALIGNANT_API AMutantCharacter : public APlayerCharacter
{
	GENERATED_BODY()

protected:
	FName Label = "MutantBase";

public:
	

	AMutantCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Interact() override;

	virtual FName GetName();

	
};
