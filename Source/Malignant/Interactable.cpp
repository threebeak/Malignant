// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

bool IInteractable::Interact(AActor* CallingActor)
{
	return false;
}

TSubclassOf<UUserWidget> IInteractable::GetWidgetType()
{
	return nullptr;
}
