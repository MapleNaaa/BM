// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chooser.h"
#include "Animation/AnimInstance.h"
#include "ES/BMAnimationTypes.h"
#include "ES/BMPlayerTypes.h"
#include "Player/Character/BMPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "BMAnimLayerInstance.generated.h"

class UBMDebugAnimation;
class UBMAnimInstance;
/**
 * 
 */
UCLASS()
class BM_API UBMAnimLayerInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(BlueprintThreadSafe), Category=Animation)
	UAnimSequence* GetAnimSequenceFromChooserTable(UChooserTable* ChooserTable);
	
protected:
	virtual void UpdateCharacterTurn(float DeltaSeconds);
	virtual void UpdateCharacterVelocity(float DeltaSeconds);
	
protected:
	UPROPERTY()
	ABMPlayerCharacter* OwnerCharacter = nullptr;
	UPROPERTY()
	UBMAnimStateComponent* AnimStateComponent = nullptr;
	UPROPERTY()
	UBMRootMotionComponent* RootMotionComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="State")
	EBMCharacterGate CharacterGate = EBMCharacterGate::Walk;

	UPROPERTY(BlueprintReadWrite, Category="State")
	FName RootAnimTimeName = FName(TEXT("TimeSec"));

	UPROPERTY(BlueprintReadWrite, Category="State")
	UAnimSequence* RootAnimSequence = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="State")
	float RootAnimTime = 0.0f;

	FTransform RootMotionTransform;

	// ~ Transform
	UPROPERTY(BlueprintReadOnly, Category="Transform")
	FRotator CharacterRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category="Transform")
	FRotator ControlRotation = FRotator::ZeroRotator;
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
	UPROPERTY(BlueprintReadWrite, Category="State")
	EBMRootYawOffsetMode RootYawOffsetMode = EBMRootYawOffsetMode::Accumulate;
	
	UPROPERTY(BlueprintReadOnly, Category="Turn")
	float RootYawOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turn")
	float BackAngle = 160.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Turn")
	float FrontAngle = 90.0f;
	
	UPROPERTY(BlueprintReadOnly, Category="Turn")
	EBMTurnType CharacterTurnType = EBMTurnType::None;

	FFloatSpringState RootYawOffsetSpring;
	// ~ End Turn

	// ~ Animation Chooser Tables
	// These tables are used to choose animations based on the current state of the character.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimationChooserTable")
	TObjectPtr<UChooserTable> IdleChooserTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimationChooserTable")
	TObjectPtr<UChooserTable> TurnChooserTable;

	UPROPERTY()
	UBMDebugAnimation* DebugAnimation;

private:
	friend class UBMDebugAnimation;
};
