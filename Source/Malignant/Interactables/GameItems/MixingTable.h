// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interactable.h"
#include "../../Components/MutantMapComponent.h"
#include "Components/BoxComponent.h"
#include "../../Mutants/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "MixingTable.generated.h"

//To pass values to BottleSelect function
DECLARE_DELEGATE_OneParam(FBottleSelect, const int32)

UCLASS()
class MALIGNANT_API AMixingTable : public AActor, public IInteractable
{
	GENERATED_BODY()

		//Ensures that SetActionBindings will only be called the first time the object is interacted with
		bool ActionsBound = false;
public:	
	// Sets default values for this actor's properties
	AMixingTable();

	//Bottle choices
	TPair<bool, int32> Bottle1 = { false, 0 };
	TPair<bool, int32> Bottle2 = { false, 0 };


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

public:	

	//Widget to display when this object is viewed
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WidgetType;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere)
		UCameraComponent* TableCamera;

	//Mutant map to determine class selection from bottle choices 
	UPROPERTY(VisibleAnywhere)
		UMutantMapComponent* Mutants;

	FActorSpawnParameters SpawnParams;

	FTimerHandle CameraHandle;


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
};
