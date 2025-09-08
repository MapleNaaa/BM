// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BMBaseCharacter.h"
#include "ES/BMPlayerTypes.h"
#include "BMPlayerCharacter.generated.h"

class UBMAnimLayerInstance;

UCLASS()
class BM_API ABMPlayerCharacter : public ABMBaseCharacter
{
	GENERATED_BODY()

public:
	ABMPlayerCharacter();
	ABMPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetCharacterGate(EBMCharacterGate NewGate);
	EBMCharacterGate GetCharacterGate() const { return CurrentCharacterGate; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BM|Animation")
	TObjectPtr<UBMAnimLayerInstance> LinkAnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BM|Gate")
	EBMCharacterGate CurrentCharacterGate = EBMCharacterGate::Walk;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BM|Gate")
	TMap<EBMCharacterGate, FBMCharacterGateSetting> CharacterGateSettings;
};
