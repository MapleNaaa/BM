// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BMAnimLayerInstance.h"
#include "Player/Component/BMAnimStateComponent.h"
#include "Animation/BMAnimInstance.h"
#include "ChooserFunctionLibrary.h"
#include "Animation/Debug/AnimDebug.h"
#include "Player/Component/BMRootMotionComponent.h"
#include "Net/UnrealNetwork.h"

void UBMAnimLayerInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	DebugAnimation = NewObject<UBMDebugAnimation>(this);
	
	OwnerCharacter = Cast<ABMPlayerCharacter>(TryGetPawnOwner());
	if (!IsValid(OwnerCharacter)) return;
	AnimStateComponent = OwnerCharacter->FindComponentByClass<UBMAnimStateComponent>();
	if (!IsValid(AnimStateComponent)) return;
	RootMotionComponent = OwnerCharacter->FindComponentByClass<UBMRootMotionComponent>();
	if (!IsValid(RootMotionComponent)) return;
}

void UBMAnimLayerInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(OwnerCharacter))
	{
		OwnerCharacter = Cast<ABMPlayerCharacter>(TryGetPawnOwner());
		if (!IsValid(OwnerCharacter)) return;
	};
	if (!IsValid(AnimStateComponent))
	{
		AnimStateComponent = OwnerCharacter->FindComponentByClass<UBMAnimStateComponent>();
		if (!IsValid(AnimStateComponent)) return;
	};

	UAnimInstance* MainAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	if(RootAnimSequence)
	{
		MainAnimInstance->SetRootMotionMode(ERootMotionMode::Type::RootMotionFromEverything);
		SetRootMotionMode(ERootMotionMode::Type::RootMotionFromEverything);
	}else
	{
		MainAnimInstance->SetRootMotionMode(ERootMotionMode::Type::RootMotionFromMontagesOnly);
		SetRootMotionMode(ERootMotionMode::Type::RootMotionFromMontagesOnly);
	}
	
	
	UpdateCharacterTurn(DeltaSeconds);

	// DebugAnimation->DebugFunc(this);
}

void UBMAnimLayerInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (!IsValid(OwnerCharacter))
	{
		OwnerCharacter = Cast<ABMPlayerCharacter>(TryGetPawnOwner());
		if (!IsValid(OwnerCharacter)) return;
	};
	if (!IsValid(AnimStateComponent))
	{
		AnimStateComponent = OwnerCharacter->FindComponentByClass<UBMAnimStateComponent>();
		if (!IsValid(AnimStateComponent)) return;
	};
	
	if (!IsValid(OwnerCharacter) || !IsValid(AnimStateComponent)) return;

	CharacterGate = OwnerCharacter->GetCharacterGate();
	ControlRotation = AnimStateComponent->ControlRotation;
	UpdateCharacterVelocity(DeltaSeconds);
	UpdateCharacterTurn(DeltaSeconds);
}

void UBMAnimLayerInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UBMAnimLayerInstance::UpdateCharacterTurn(float DeltaSeconds)
{
	if(RootYawOffsetMode == EBMRootYawOffsetMode::Accumulate)
	{
		float Offset = OwnerCharacter->GetActorRotation().Yaw - ControlRotation.Yaw;
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(Offset); 
	}
	else if(RootYawOffsetMode == EBMRootYawOffsetMode::BlendOut)
	{
		float Tmp = UKismetMathLibrary::FloatSpringInterp(RootYawOffset, 0.f, RootYawOffsetSpring,
			80,1, DeltaSeconds,1,0.5);
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(Tmp);
	}

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

void UBMAnimLayerInstance::UpdateCharacterVelocity(float DeltaSeconds)
{
	// ~ Speed
	CharacterVelocity = OwnerCharacter->GetVelocity();
	CharacterVelocity2D = CharacterVelocity.GetSafeNormal2D();
	CharacterSpeed = CharacterVelocity2D.Size2D();
	// ~ End Speed
}

UAnimSequence* UBMAnimLayerInstance::GetAnimSequenceFromChooserTable(UChooserTable* ChooserTable)
{
	UObject* Result = UChooserFunctionLibrary::EvaluateChooser(this,ChooserTable, UAnimSequence::StaticClass());
	if (!IsValid(Result))
	{
		UE_LOG(LogTemp, Warning, TEXT("[AnimDebug]: Chooser Table %s Result is not valid "), *GetNameSafe(ChooserTable));
		return nullptr;
	}
	return Cast<UAnimSequence>(Result);

}

void UBMAnimLayerInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

