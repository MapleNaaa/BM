// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BMBaseCharacter.h"
#include "BMPlayerCharacter.generated.h"

UCLASS()
class BM_API ABMPlayerCharacter : public ABMBaseCharacter
{
	GENERATED_BODY()

public:
	ABMPlayerCharacter();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BM|Animation")
	UAnimInstance* LinkAnimInstance;
	
public:
};
