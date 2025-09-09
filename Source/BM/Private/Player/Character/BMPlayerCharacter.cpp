// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Character/BMPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Component/BMCharacterMovementComponent.h"


ABMPlayerCharacter::ABMPlayerCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UBMCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	
	PrimaryActorTick.bCanEverTick = true;
	// 创建根运动组件
	RootMotionComponent = CreateDefaultSubobject<UBMRootMotionComponent>(TEXT("RootMotionComponent"));
}

void ABMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (RootMotionComponent)
	{
		RootMotionComponent->SetRootMotionEnabled(true);
		RootMotionComponent->EnableAutoExtractFromAnimation(true);
	}
	
}

void ABMPlayerCharacter::SetCharacterGate(EBMCharacterGate NewGate)
{
	CurrentCharacterGate = NewGate;

	FBMCharacterGateSetting* GateSetting = CharacterGateSettings.Find(NewGate);
	if(GateSetting == nullptr) return;

	GetCharacterMovement()->MaxWalkSpeed = GateSetting->MaxWalkSpeed;
	GetCharacterMovement()->MaxAcceleration = GateSetting->MaxAcceleration;
	GetCharacterMovement()->BrakingDecelerationWalking = GateSetting->BrakingDeceleration;
	GetCharacterMovement()->BrakingFrictionFactor = GateSetting->BrakingFrictionFactor;
	GetCharacterMovement()->BrakingFriction = GateSetting->BrakingFriction;
	GetCharacterMovement()->bUseSeparateBrakingFriction = GateSetting->UseSeparateBrakingFriction;
}
