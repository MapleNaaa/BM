// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BMBaseCharacter.h"
#include "ES/BMPlayerTypes.h"
#include "BMPlayerCharacter.generated.h"

class UBMAnimStateComponent;
class UBMAnimLayerInstance;
class UBMRootMotionComponent;

UCLASS()
class BM_API ABMPlayerCharacter : public ABMBaseCharacter
{
	GENERATED_BODY()

public:
	ABMPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void SetCharacterGate(EBMCharacterGate NewGate);
	EBMCharacterGate GetCharacterGate() const { return CurrentCharacterGate; }
	UFUNCTION()
	void OnRep_CharacterGate();

	TSubclassOf<UBMAnimLayerInstance> GetLinkAnimInstance() const { return LinkAnimInstance; }
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(Server, Reliable)
	void Server_CharacterGate(EBMCharacterGate NewGate);

protected:
	
	/** 根运动管理组件 */
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBMRootMotionComponent* RootMotionComponent;*/

	/** 动画状态管理组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBMAnimStateComponent* AnimStateComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BM|Animation")
	TSubclassOf<UBMAnimLayerInstance> LinkAnimInstance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CharacterGate, Category="BM|Gate")
	EBMCharacterGate CurrentCharacterGate = EBMCharacterGate::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BM|Gate")
	TMap<EBMCharacterGate, FBMCharacterGateSetting> CharacterGateSettings;
};
