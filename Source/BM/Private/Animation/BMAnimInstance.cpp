// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BMAnimInstance.h"

#include "Animation/Debug/AnimDebug.h"

void UBMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BMPlayerCharacter = Cast<ABMPlayerCharacter>(TryGetPawnOwner());
	DebugAnimation = NewObject<UBMDebugAnimation>(this);
}

void UBMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(BMPlayerCharacter)) return;

	DebugAnimation->DebugFunc(this);
	
}

void UBMAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!IsValid(BMPlayerCharacter)) return;

	CurrentCharacterGate = BMPlayerCharacter->GetCharacterGate();
	
	UpdateCharacterVelocity(DeltaSeconds);
	UpdateCharacterTurn(DeltaSeconds);

}

void UBMAnimInstance::UpdateCharacterVelocity(float DeltaSeconds)
{
	// ~ Speed
	CharacterVelocity = BMPlayerCharacter->GetVelocity();
	CharacterVelocity2D = CharacterVelocity.GetSafeNormal2D();
	CharacterSpeed = CharacterVelocity2D.Size2D();
	// ~ End Speed
}

void UBMAnimInstance::UpdateCharacterTurn(float DeltaSeconds)
{
	// ~ Turn
	if(RootYawOffsetMode == EBMRootYawOffsetMode::Accumulate)
	{
		float Offset = BMPlayerCharacter->GetActorRotation().Yaw - LastCharacterYaw;
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(RootYawOffset - Offset); 
	}
	else if(RootYawOffsetMode == EBMRootYawOffsetMode::BlendOut)
	{
		float Tmp = UKismetMathLibrary::FloatSpringInterp(RootYawOffset, 0.f, RootYawOffsetSpring,
			80,1, DeltaSeconds,1,0.5);
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(Tmp);
	}
	LastCharacterYaw = BMPlayerCharacter->GetActorRotation().Yaw;
	// ~ End Turn

	CharacterTurnType = EBMTurnType::None;
	if(RootYawOffset > BackAngle)
	{
		CharacterTurnType = EBMTurnType::LeftToBack;
	}
	else if(RootYawOffset > FrontAngle)
	{
		CharacterTurnType = EBMTurnType::Left;
	}
	else if(RootYawOffset < -BackAngle)
	{
		CharacterTurnType = EBMTurnType::RightToBack;
	}
	else if(RootYawOffset < -FrontAngle)
	{
		CharacterTurnType = EBMTurnType::Right;
	}
	
}
