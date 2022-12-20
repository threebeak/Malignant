// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../Malignant.h"
#include "../../Mutants/PlayerCharacter.h"

// Sets default values
ABaseGameItem::ABaseGameItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemInteractArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Mixing Table Interact Area"));
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemStaticMesh->SetSimulatePhysics(true);
	RootComponent = ItemStaticMesh;

	ItemInteractArea->SetupAttachment(RootComponent);


}

bool ABaseGameItem::Interact(AActor* CallingActor)
{
	return false;
}

TSubclassOf<UUserWidget> ABaseGameItem::GetWidgetType()
{
	return WidgetType;
}

void ABaseGameItem::BeginOverlapMixingTable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
		PlayerCharacter->SetOverlappingTable(true);
}

void ABaseGameItem::EndOverlapMixingTable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
		PlayerCharacter->SetOverlappingTable(false);
}

// Called when the game starts or when spawned
void ABaseGameItem::BeginPlay()
{
	Super::BeginPlay();

	ItemInteractArea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemInteractArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemInteractArea->SetCollisionResponseToChannel(COLLISION_PLAYER, ECollisionResponse::ECR_Overlap);
	ItemInteractArea->OnComponentBeginOverlap.AddDynamic(this, &ABaseGameItem::BeginOverlapMixingTable);
	ItemInteractArea->OnComponentEndOverlap.AddDynamic(this, &ABaseGameItem::EndOverlapMixingTable);

	
}

// Called every frame
void ABaseGameItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

