// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chooser.h"
#include "Animation/AnimInstance.h"
#include "ES/BMAnimationTypes.h"
#include "ES/BMPlayerTypes.h"
#include "BMAnimLayerInstance.generated.h"

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
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(BlueprintThreadSafe), Category=Animation)
	UAnimSequence* GetAnimSequenceFromChooserTable(UChooserTable* ChooserTable);
	
protected:
	UPROPERTY(BlueprintReadWrite, Category="BM")
	TObjectPtr<UBMAnimInstance> BMAnimInstance;
	
	UPROPERTY(BlueprintReadWrite, Category="BM")
	EBMSMStage CurrentSMStage = EBMSMStage::Idle;

	UPROPERTY(BlueprintReadWrite, Category="BM")
	EBMCharacterGate CurrentCharacterGate = EBMCharacterGate::Walk;

	UPROPERTY(BlueprintReadWrite, Category="BM")
	EBMTurnType CurrentTurnType = EBMTurnType::None;


	// ~ Animation Chooser Tables
	// These tables are used to choose animations based on the current state of the character.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimationChooserTable")
	TObjectPtr<UChooserTable> IdleChooserTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimationChooserTable")
	TObjectPtr<UChooserTable> TurnChooserTable;
};
