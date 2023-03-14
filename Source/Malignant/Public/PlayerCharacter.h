// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"
#include "Engine/World.h"
#include "PlayerCharacter.generated.h"




UCLASS()
class MALIGNANT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


	/* methods */
public:

	// Sets default values for this pawn's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement Functions
	virtual void MoveForward(float AxisValue);
	virtual void MoveRight(float AxisValue);
	virtual void LookUp(float AxisValue);
	virtual void LookRight(float AxisValue);
	virtual void Jump();

	//Proxies for Enable/Disable Input
	void Lock();
	void Release(APlayerController* PCont);

	//Used to interact with IInteractables 
	virtual void Interact();

	//Attack method
	virtual void LightAttack();
	virtual void HeavyAttack();


	/* members */
public:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UCameraComponent* MainCamera;

	//Object currently being interacted with or viewed and interactable
	IInteractable* InteractingObject;

	//InteractingObject's assigned widget to be displayed Ex. "Press E to Interact"
	UPROPERTY()
		UUserWidget* DisplayWidget;

	//Default distance for line trace
	UPROPERTY(EditAnywhere, Category = Traces)
		float LookDistance = 200;


	/* methods */
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Handle LookResult and DisplayWidget
	void HandleTrace();
	void HandleDisplay(bool Visible);


	/* members */
protected:
	

	//Pointer to PlayerController to avoid casting
	UPROPERTY()
		APlayerController* PController;

	//Result from line trace
	FHitResult LookResult;


	/* methods */
private:


	/* members */
private:




};
