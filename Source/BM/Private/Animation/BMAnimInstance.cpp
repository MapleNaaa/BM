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

	CharacterRotation = BMPlayerCharacter->GetActorRotation();
	
	UpdateCharacterTurn(DeltaSeconds);
}

void UBMAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!IsValid(BMPlayerCharacter)) return;

	CurrentCharacterGate = BMPlayerCharacter->GetCharacterGate();
	
	UpdateCharacterVelocity(DeltaSeconds);

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
		float Offset = BMPlayerCharacter->GetActorRotation().Yaw - BMPlayerCharacter->GetControlRotation().Yaw;
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(Offset); 
	}
	/*else if(RootYawOffsetMode == EBMRootYawOffsetMode::BlendOut)
	{
		float Tmp = UKismetMathLibrary::FloatSpringInterp(RootYawOffset, 0.f, RootYawOffsetSpring,
			80,1, DeltaSeconds,1,0.5);
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(Tmp);
	}*/
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

	LastTurnCurveYaw = CurrentTurnCurveYaw;
	float CurrentTurnCurveStageValue = GetCurveValue(TurnCurveStageName);
	// UE_LOG(LogTemp, Error, TEXT("CurrentTurnCurveStageValue: %f"), CurrentTurnCurveStageValue);
	if(CurrentTurnCurveStageValue < 0.1f)
	{
		LastTurnCurveYaw = 0.f;
		CurrentTurnCurveYaw = 0.f;
	}
	else
	{
		CurrentTurnCurveYaw = CurrentTurnCurveStageValue > 0 ? GetCurveValue(TurnCurveYawName) : 0.f;
		// UE_LOG(LogTemp, Warning, TEXT("CurrentTurnCurveYaw: %f"), CurrentTurnCurveYaw);
		if(LastTurnCurveYaw == 0.f) return;
		AbsMaxTurnYawValue = FMath::Abs(AbsMaxTurnYawValue) > FMath::Abs(CurrentTurnCurveYaw) ? AbsMaxTurnYawValue : CurrentTurnCurveYaw;
		float TempOffset = UKismetMathLibrary::NormalizeAxis(CurrentTurnCurveYaw - LastTurnCurveYaw);

		
		
		// UE_LOG(LogTemp, Warning, TEXT("TempOffset: %f"), TempOffset);
		// FRotator NewRotation = FRotator(CharacterRotation.Pitch,CharacterRotation.Yaw - TempOffset,CharacterRotation.Roll);
		// UE_LOG(LogTemp, Warning, TEXT("NewRotation: %s"), *NewRotation.ToString());
		// BMPlayerCharacter->SetActorRotation(NewRotation);
		

		// BMPlayerCharacter->SetActorTransform()
	}
	
}
