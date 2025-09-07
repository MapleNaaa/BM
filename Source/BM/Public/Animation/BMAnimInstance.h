// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player/Character/BMPlayerCharacter.h"
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

protected:
	UPROPERTY()
	ABMPlayerCharacter* BMPlayerCharacter;

	// ~ Speed
	UPROPERTY(BlueprintReadOnly, Category="BM|Animation")
	float GroundSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category="BM|Animation")
	FVector CharacterVelocity = FVector::ZeroVector;
	// ~ End Speed

	// ~ Turn
	float LastTurnInPlaceAngle = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category="BM|Animation")
	float TurnInPlaceAngle = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category="BM|Animation")
	float DeltaTurnInPlaceAngle = 0.0f;
	// ~ End Turn


	
};
