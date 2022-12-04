// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "../Enemies/BaseEnemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner() :
	MaxNumEnemies(2)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::OnConstruction(const FTransform& Transform)
{
	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemies(int numEnemies)
{
	//Don't allow spawning if full
	if (NumEnemiesSpawned == MaxNumEnemies)
		return;

	//check if num enemies is too many, find difference between current and max: spawn that many enmies instead
	if (numEnemies + NumEnemiesSpawned > MaxNumEnemies)
	{
		int dif(MaxNumEnemies - NumEnemiesSpawned);
		numEnemies = dif;
	}

	//Select random spawn location from spawn location array
	int spawnLocationIdx = FMath::RandRange(0, SpawnLocations.Num() - 1);
	for (int i = 0; i < numEnemies; i++)
	{
		UWorld* curWorld = GetWorld();
		if (curWorld)
		{
			//Spawn actor and randomly chosen spawn location
			ABaseEnemy* spawnedEnemy = curWorld->SpawnActor<ABaseEnemy>(SpawnerEnemyType, SpawnLocations[spawnLocationIdx]);
			if (spawnedEnemy)
			{
				NumEnemiesSpawned++;
			}
		}
	}
}

void AEnemySpawner::SetSpawnerEnemyType(TSubclassOf<ABaseEnemy> enemyType)
{
	SpawnerEnemyType = enemyType;
}

