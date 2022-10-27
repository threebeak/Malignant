// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantBase.h"

// Sets default values
AMutantBase::AMutantBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMutantBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMutantBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMutantBase::LightAttack()
{
}

void AMutantBase::HeavyAttack()
{
}

void AMutantBase::Ability()
{
}

void AMutantBase::SetBaseStats(float Height, float Radius, float Health, float Defense, float MoveSpeed, float AttackSpeed)
{
	BaseStats.Height = Height;
	BaseStats.Radius = Radius;
	BaseStats.Health = Health;
	BaseStats.Defense = Defense;
	BaseStats.MovementSpeed = MoveSpeed;
	BaseStats.AttackSpeed = AttackSpeed;
}

UStaticMesh* AMutantBase::GetMutantMesh()
{
	return MutantMesh->GetStaticMesh();
}

FMutantStats AMutantBase::GetBaseStats()
{
	return BaseStats;
}

