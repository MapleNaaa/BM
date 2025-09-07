// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BMBasePlayerController.h"
#include "BMPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class BM_API ABMPlayerController : public ABMBasePlayerController
{
	GENERATED_BODY()


public:


protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void Jog(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void LightAttack(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);
	void Inventory(const FInputActionValue& Value);

protected:

#pragma region BM Input
	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputAction* JogAction;
	
	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputAction* LightAttackAction;
	
	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputAction* HeavyAttackAction;
	
	UPROPERTY(EditAnywhere, Category="BM|Input")
	UInputAction* InventoryAction;

	bool bIsJogging = false;
	bool LastIsJogging = false;
#pragma endregion

	
	
};
