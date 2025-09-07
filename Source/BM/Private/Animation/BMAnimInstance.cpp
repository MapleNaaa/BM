// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BMAnimInstance.h"

void UBMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BMPlayerCharacter = Cast<ABMPlayerCharacter>(TryGetPawnOwner());
}

void UBMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(BMPlayerCharacter)) return;

	// ~ Speed
	CharacterVelocity = BMPlayerCharacter->GetVelocity();
	GroundSpeed = CharacterVelocity.Size2D();
	// ~ End Speed

	// ~ Turn
	LastTurnInPlaceAngle = TurnInPlaceAngle;
	FRotator DeltaRot = BMPlayerCharacter->GetBaseAimRotation() - BMPlayerCharacter->GetActorRotation();
	// DeltaRot.Normalize();
	TurnInPlaceAngle = DeltaRot.Yaw;
	DeltaTurnInPlaceAngle = TurnInPlaceAngle - LastTurnInPlaceAngle;
	UE_LOG(LogTemp, Warning, TEXT("[AnimDebug]: TurnInPlaceAngle: %f"), TurnInPlaceAngle);
	UE_LOG(LogTemp, Warning, TEXT("[AnimDebug]: DeltaTurnInPlaceAngle: %f"), DeltaTurnInPlaceAngle);
	// ~ End Turn

	
}

void UBMAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);


}
