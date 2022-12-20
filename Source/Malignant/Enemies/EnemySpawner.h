// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ABaseEnemy;
class UBoxComponent;

UCLASS()
class MALIGNANT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()



	// methods 
public:

	// Sets default values for this actor's properties
	AEnemySpawner();

	void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Spawns enemies of spawner enemy type
	//@Param int - number of enemies to spawn
	void SpawnEnemies(int numEnemies);

	//Setters

	void SetMaxNumEnemies(int maxNumEnemies) { MaxNumEnemies = maxNumEnemies; }
	
	void SetSpawnerEnemyType(TSubclassOf<ABaseEnemy> enemyType);

	//Getters

	//members
public:


	//methods
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

	//members
protected:


	//methods
private:


	//members
private:

	//Type of enemy the spawner produces
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Stats", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseEnemy> SpawnerEnemyType;

	//Maximum number of enemies this spawner can spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawner Stats", meta = (AllowPrivateAccess = "true"))
	int MaxNumEnemies;

	//Current number of spawned enemies
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawner Stats", meta = (AllowPrivateAccess = "true"))
	int NumEnemiesSpawned;

	//list of areas the enemies can spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Stats", meta = (AllowPrivateAccess = "true", MakeEditWidget = true))
	TArray<FTransform> SpawnLocations;


};
