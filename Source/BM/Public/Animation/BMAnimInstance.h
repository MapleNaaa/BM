// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ES/BMAnimationTypes.h"
#include "Player/Character/BMPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "BMAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BM_API UBMAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	void UpdateCharacterVelocity(float DeltaSeconds);
	void UpdateCharacterTurn(float DeltaSeconds);

protected:
	UPROPERTY()
	ABMPlayerCharacter* BMPlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category="State")
	EBMCharacterGate CurrentCharacterGate = EBMCharacterGate::None;

	// ~ Transform
	UPROPERTY(BlueprintReadOnly, Category="Transform")
	FRotator CharacterRotation = FRotator::ZeroRotator;
	// ~ End Transform

	// ~ Speed
	UPROPERTY(BlueprintReadOnly, Category="Velocity")
	float CharacterSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category="Velocity")
	FVector CharacterVelocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category="Velocity")
	FVector CharacterVelocity2D = FVector::ZeroVector;
	// ~ End Speed

	// ~ Turn
	float LastCharacterYaw = 0.0f;
	float LastTurnCurveYaw = 0.0f;
	float CurrentTurnCurveYaw = 0.0f;
	FFloatSpringState RootYawOffsetSpring;
	
	UPROPERTY(BlueprintReadWrite, Category="State")
	EBMRootYawOffsetMode RootYawOffsetMode = EBMRootYawOffsetMode::Accumulate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turn")
	float BackAngle = 160.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turn")
	float FrontAngle = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turn")
	FName TurnCurveStageName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turn")
	FName TurnCurveYawName;
	
	UPROPERTY(BlueprintReadOnly, Category="Turn")
	float RootYawOffset = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category="Turn")
	EBMTurnType CharacterTurnType = EBMTurnType::None;

	UPROPERTY(BlueprintReadOnly, Category="Turn")
	float AbsMaxTurnYawValue = 0.0f;
	
	// ~ End Turn


private:
	friend class UBMAnimLayerInstance;
	friend class UBMDebugAnimation;

	UPROPERTY()
	UBMDebugAnimation* DebugAnimation;
};
