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


//Player character movement state for movement control and anim BP state control
UENUM(BlueprintType)
enum ECharacterMovementState
{
	ECMS_Idle UMETA(DisplayName = "Idle"),
	ECMS_MoveStart UMETA(DisplayName = "MoveStart"),
	ECMS_MoveEnd UMETA(DisplayName = "MoveEnd"),
	ECMS_Moving UMETA(DisplayName = "Moving"),
	ECMS_Sprinting UMETA(DisplayName = "Sprinting"),
	ECMS_JumpStart UMETA(DisplayName = "JumpStart"),
	ECMS_JumpEnd UMETA(DisplayName = "JumpEnd"),
	ECMS_InAir UMETA(DisplayName = "InAir"),
	ECMS_WallRunning UMETA(DisplayName = "WallRunning"),
	ECMS_TurningInPlace UMETA(DisplayName = "TurningInPlace"),
	ECMS_DEFAULT UMETA(DisplayName = "DEFAULT")

};

UENUM(BlueprintType)
enum EWallRunSide
{
	EWRS_Left UMETA(DisplayName = "Wall_Left"),
	EWRS_Right UMETA(DisplayName = "Wall_Right"),
	EWRS_DEFAULT UMETA(DisplayName = "EWRS_DEFAULT")

};

UENUM(BlueprintType)
enum EWallRunEndReason
{
	EWRER_FellOff UMETA(DisplayName = "Fell Off"),
	EWRER_JumpOff UMETA(DisplayName = "Jump Off"),
	EWRER_DEFAULT UMETA(DisplayName = "EWRS_DEFAULT")

};