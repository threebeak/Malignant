// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "BaseGameItem.h"
#include "GameFramework/Actor.h"
#include "MixingTable.generated.h"

//Forward Declarations
class UMutantMapComponent;
class APlayerCharacter;
class UBoxComponent;
class UCameraComponent;

//To pass values to BottleSelect function
DECLARE_DELEGATE_OneParam(FBottleSelect, const int32)

UCLASS()
class MALIGNANT_API AMixingTable : public ABaseGameItem
{
	GENERATED_BODY()



	/* methods */
public:

	// Sets default values for this actor's properties
	AMixingTable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Primary function called when this object is interacted with. Overridden from IInteractable
	virtual bool Interact(AActor* CallingActor) override;

	//Set input action bindings the first time this object is used
	virtual bool SetActionBindings(APlayerCharacter* Character);

	//Determine mutant class and handle character spawning and controller assigning
	bool ChooseMutant(AActor* CallingActor);

	//Determine bottle choices based on input
	UFUNCTION()
		void BottleSelect(const int32 BottleValue);

	//Accessor for widget type
	TSubclassOf<UUserWidget> GetWidgetType() override;

	//Cease interaction with this object and clear all values such as Player and Controller
	void Exit();
	void Clear();


	/* members */
public:



	/* methods */
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/* members */
protected:


	//Values for the interacting player and corresponding controller to recieve input
	UPROPERTY()
	APlayerCharacter* Player;
	UPROPERTY()
	APlayerController* Controller;

	//Bottle meshes - YET TO BE ASSIGNED
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottleMesh1;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottleMesh2;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottleMesh3;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottleMesh4;


	/* methods */
private:

	
	/* members */
private:

	//Bottle choices
	TPair<bool, int32> Bottle1 = { false, 0 };
	TPair<bool, int32> Bottle2 = { false, 0 };

	//Widget to display when this object is viewed
	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		//TSubclassOf<UUserWidget> WidgetType;

	//Bottle collision
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* BoxCollision;


	//Camera for player to view / interact with mixing table from
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* TableCamera;

	//Mutant map to determine class selection from bottle choices 
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UMutantMapComponent* Mutants;

	//Mutant spawn params
	//UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FActorSpawnParameters SpawnParams;

	//Handles time of swap between player camera and mixing table camera
	FTimerHandle CameraTimerHandle;

	//Ensures that SetActionBindings will only be called the first time the object is interacted with
	bool ActionsBound = false;



	
};
