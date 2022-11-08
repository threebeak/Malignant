#pragma once

#include "CoreMinimal.h"


//MutantCharacter ID for determining in MutantMap
UENUM(BlueprintType)
enum EMutantState
{
	Human,
	EMS_Base  UMETA(DisplayName = "BoneMutantType"),
	EMS_Bone UMETA(DisplayName = "BoneMutantType"),
	EMS_FourArm  UMETA(DisplayName = "BoneMutantType"),
	EMS_Poison UMETA(DisplayName = "BoneMutantType"),
	EMS_Brute UMETA(DisplayName = "BoneMutantType"),
	EMS_Fire UMETA(DisplayName = "BoneMutantType"),
	EMS_DefaultMax UMETA(DisplayName = "Default")
};