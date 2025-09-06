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
	// Sets default values for this character's properties
	ABMPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
};
