// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MutantCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "FourArmMutantCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MALIGNANT_API AFourArmMutantCharacter : public AMutantCharacter
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere)
		float ThrowStrength = 3000;

	FHitResult GrabHit;

	AFourArmMutantCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Interact() override;

	bool GrabObject(UPrimitiveComponent* HitComponent);
	void ThrowObject();
};
