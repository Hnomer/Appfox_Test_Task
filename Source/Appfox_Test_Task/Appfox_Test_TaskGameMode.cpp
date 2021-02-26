// Copyright Epic Games, Inc. All Rights Reserved.

#include "Appfox_Test_TaskGameMode.h"
#include "Appfox_Test_TaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAppfox_Test_TaskGameMode::AAppfox_Test_TaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
