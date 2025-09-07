// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Animation/BMAnimInstance.h"
#include "ES/BMAnimationTypes.h"
#include "ES/BMPlayerTypes.h"
#include "AnimDebug.generated.h"

class UBMAnimInstance;
/**
 * 
 */
namespace DebugAnim
{
	static bool bShowDebug = false;
	static bool bShowVelocity = false;
	static bool bShowTurn = false;

	static FAutoConsoleCommand CVarShowDebug(
		TEXT("DebugAnim.bShowDebug"),
		TEXT("Show the debug information in the top left corner of the screen. use [1/0]."),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& InArgs)
		{
			bShowDebug = FCString::Atoi(*InArgs[0]) == 1;
			
			bShowVelocity = bShowDebug;
			bShowTurn = bShowDebug;
		})
	);

	static FAutoConsoleVariableRef CVarShowVelocity(
		TEXT("DebugAnim.bShowVelocity"),
		bShowVelocity,
		TEXT("Show the current character velocity in the top left corner of the screen. use [true/false]."),
		ECVF_Default
	);
	
	static FAutoConsoleVariableRef CVarShowTurn(
		TEXT("DebugAnim.bShowTurn"),
		bShowTurn,
		TEXT("Show the current character turn in the top left corner of the screen. use [true/false]."),
		ECVF_Default
	);
}


UCLASS()
class UBMDebugAnimation : public UObject
{
	GENERATED_BODY()

public:
	 void DebugFunc(UBMAnimInstance* AnimInstance) const;
};

