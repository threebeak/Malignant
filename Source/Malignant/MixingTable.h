// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "MutantMapComponent.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "MixingTable.generated.h"

DECLARE_DELEGATE_OneParam(FBottleSelect, const int32)

UCLASS()
class MALIGNANT_API AMixingTable : public AActor, public IInteractable
{
	GENERATED_BODY()

		bool ActionsBound = false;
public:	
	// Sets default values for this actor's properties
	AMixingTable();

	TPair<bool, int32> Bottle1 = { false, 0 };
	TPair<bool, int32> Bottle2 = { false, 0 };


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		APlayerCharacter* Player;
	UPROPERTY()
		APlayerController* Controller;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottleMesh1;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottleMesh2;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BottleMesh3;

public:	

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WidgetType;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
		UMutantMapComponent* Mutants;

	FActorSpawnParameters SpawnParams;
	FTimerHandle CameraHandle;

	UPROPERTY(EditAnywhere)
		UCameraComponent* TableCamera;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Interact(AActor* CallingActor) override;
	virtual bool SetActionBindings(APlayerCharacter* Character);

	bool ChooseMutant(AActor* CallingActor);

	UFUNCTION()
		void BottleSelect(const int32 BottleValue);

	TSubclassOf<UUserWidget> GetWidgetType() override;


		void Exit();
		void Clear();
};
