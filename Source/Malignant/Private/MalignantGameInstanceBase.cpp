// Fill out your copyright notice in the Description page of Project Settings.


#include "MalignantGameInstanceBase.h"
#include "MutagenBase.h"
#include "CompoundBase.h"

bool UMalignantGameInstanceBase::DecrementMutagen(TSubclassOf<UMutagenBase> MutagenClass)
{
	for (int32 Index = 0; Index < AvailableMutagens.Num(); Index++)
	{
		if (AvailableMutagens[Index].Mutagen == MutagenClass)
		{
			AvailableMutagens[Index].Amount--;
			if (AvailableMutagens[Index].Amount <= 0)
			{
				AvailableMutagens[Index] = FMutagens();
			}
			return true;
		}
	}
	return false;
}

bool UMalignantGameInstanceBase::DecrementCompound(TSubclassOf<UCompoundBase> CompoundClass)
{
	for (int32 Index = 0; Index < AvailableCompounds.Num(); Index++)
	{
		if (AvailableCompounds[Index].Compound == CompoundClass)
		{
			AvailableCompounds[Index].Amount--;
			if (AvailableCompounds[Index].Amount <= 0)
			{
				AvailableCompounds[Index] = FCompounds();
			}
			return true;
		}
	}
	return false;
}
