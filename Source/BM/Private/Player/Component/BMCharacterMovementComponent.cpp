// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Component/BMCharacterMovementComponent.h"

#include "Animation/BMAnimInstance.h"

/*
FRootMotionSource_DynamicTransform::FRootMotionSource_DynamicTransform()
	: StartTransform(FTransform::Identity)
	, InitialTargetTransform(FTransform::Identity)
	, TargetTransform(FTransform::Identity)
	, bRestrictSpeedToExpected(false)
	, PathOffsetCurve(nullptr)
	, TimeMappingCurve(nullptr)
{
}

void FRootMotionSource_DynamicTransform::SetTargetTransform(FTransform NewTargetTransform)
{
	TargetTransform = NewTargetTransform;
}

FRootMotionSource* FRootMotionSource_DynamicTransform::Clone() const
{
	FRootMotionSource_DynamicTransform* CopyPtr = new FRootMotionSource_DynamicTransform(*this);
	return CopyPtr;
}

bool FRootMotionSource_DynamicTransform::Matches(const FRootMotionSource* Other) const
{
	if (!FRootMotionSource::Matches(Other))
	{
		return false;
	}

	// We can cast safely here since in FRootMotionSource::Matches() we ensured ScriptStruct equality
	const FRootMotionSource_DynamicTransform* OtherCast = static_cast<const FRootMotionSource_DynamicTransform*>(Other);

	return bRestrictSpeedToExpected == OtherCast->bRestrictSpeedToExpected &&
		PathOffsetCurve == OtherCast->PathOffsetCurve &&
		TimeMappingCurve == OtherCast->TimeMappingCurve;
}

bool FRootMotionSource_DynamicTransform::MatchesAndHasSameState(const FRootMotionSource* Other) const
{
	// Check that it matches
	if (!FRootMotionSource::MatchesAndHasSameState(Other))
	{
		return false;
	}
	
	// We can cast safely here since in FRootMotionSource::Matches() we ensured ScriptStruct equality
	const FRootMotionSource_DynamicTransform* OtherCast = static_cast<const FRootMotionSource_DynamicTransform*>(Other);

	return (StartTransform.Equals(OtherCast->StartTransform) &&
			TargetTransform.Equals(OtherCast->TargetTransform));
}

bool FRootMotionSource_DynamicTransform::UpdateStateFrom(const FRootMotionSource* SourceToTakeStateFrom, bool bMarkForSimulatedCatchup)
{
	if (!FRootMotionSource::UpdateStateFrom(SourceToTakeStateFrom, bMarkForSimulatedCatchup))
	{
		return false;
	}

	// We can cast safely here since in FRootMotionSource::UpdateStateFrom() we ensured ScriptStruct equality
	const FRootMotionSource_DynamicTransform* OtherCast = static_cast<const FRootMotionSource_DynamicTransform*>(SourceToTakeStateFrom);

	StartTransform = OtherCast->StartTransform;
	TargetTransform = OtherCast->TargetTransform;

	return true;
}

void FRootMotionSource_DynamicTransform::SetTime(float NewTime)
{
	FRootMotionSource::SetTime(NewTime);

	// TODO-RootMotionSource: Check if reached destination?
}

FTransform FRootMotionSource_DynamicTransform::GetPathOffsetInWorldSpace(const float MoveFraction) const
{
	if (PathOffsetCurve)
	{
		// Calculate path offset
		const FTransform PathOffsetInFacingSpace = EvaluateVectorCurveAtFraction(*PathOffsetCurve, MoveFraction);
		FRotator FacingRotation((TargetTransform-StartTransform).Rotation());
		FacingRotation.Pitch = 0.f; // By default we don't include pitch in the offset, but an option could be added if necessary
		return FacingRotation.RotateVector(PathOffsetInFacingSpace);
	}

	return FTransform::ZeroVector;
}

void FRootMotionSource_DynamicTransform::PrepareRootMotion
	(
		float SimulationTime, 
		float MovementTickTime,
		const ACharacter& Character, 
		const UCharacterMovementComponent& MoveComponent
	)
{
	RootMotionParams.Clear();

	if (Duration > UE_SMALL_NUMBER && MovementTickTime > UE_SMALL_NUMBER)
	{
		float MoveFraction = (GetTime() + SimulationTime) / Duration;
		
		if (TimeMappingCurve)
		{
			MoveFraction = EvaluateFloatCurveAtFraction(*TimeMappingCurve, MoveFraction);
		}

		FTransform CurrentTargetTransform = FMath::Lerp<FTransform, float>(StartTransform, TargetTransform, MoveFraction);
		CurrentTargetTransform += GetPathOffsetInWorldSpace(MoveFraction);

		const FTransform CurrentTransform = Character.GetActorTransform();

		FTransform Force = (CurrentTargetTransform - CurrentTransform) / MovementTickTime;

		if (bRestrictSpeedToExpected && !Force.IsNearlyZero(UE_KINDA_SMALL_NUMBER))
		{
			// Calculate expected current Transform (if we didn't have collision and moved exactly where our velocity should have taken us)
			float PreviousMoveFraction = GetTime() / Duration;
			if (TimeMappingCurve)
			{
				PreviousMoveFraction = EvaluateFloatCurveAtFraction(*TimeMappingCurve, PreviousMoveFraction);
			}

			FTransform CurrentExpectedTransform = FMath::Lerp<FTransform, float>(StartTransform, TargetTransform, PreviousMoveFraction);
			CurrentExpectedTransform += GetPathOffsetInWorldSpace(PreviousMoveFraction);

			// Restrict speed to the expected speed, allowing some small amount of error
			const FTransform ExpectedForce = (CurrentTargetTransform - CurrentExpectedTransform) / MovementTickTime;
			const float ExpectedSpeed = ExpectedForce.Size();
			const float CurrentSpeedSqr = Force.SizeSquared();

			const float ErrorAllowance = 0.5f; // in cm/s
			if (CurrentSpeedSqr > FMath::Square(ExpectedSpeed + ErrorAllowance))
			{
				Force.Normalize();
				Force *= ExpectedSpeed;
			}
		}

		// Debug
#if ROOT_MOTION_DEBUG
		if (RootMotionSourceDebug::CVarDebugRootMotionSources.GetValueOnGameThread() != 0)
		{
			const FTransform LocDiff = MoveComponent.UpdatedComponent->GetComponentTransform() - CurrentTransform;
			const float DebugLifetime = CVarDebugRootMotionSourcesLifetime.GetValueOnGameThread();

			// Current
			DrawDebugCapsule(Character.GetWorld(), MoveComponent.UpdatedComponent->GetComponentTransform(), Character.GetSimpleCollisionHalfHeight(), Character.GetSimpleCollisionRadius(), FQuat::Identity, FColor::Red, true, DebugLifetime);

			// Current Target
			DrawDebugCapsule(Character.GetWorld(), CurrentTargetTransform + LocDiff, Character.GetSimpleCollisionHalfHeight(), Character.GetSimpleCollisionRadius(), FQuat::Identity, FColor::Green, true, DebugLifetime);

			// Target
			DrawDebugCapsule(Character.GetWorld(), TargetTransform + LocDiff, Character.GetSimpleCollisionHalfHeight(), Character.GetSimpleCollisionRadius(), FQuat::Identity, FColor::Blue, true, DebugLifetime);

			// Force
			DrawDebugLine(Character.GetWorld(), CurrentTransform, CurrentTransform+Force, FColor::Blue, true, DebugLifetime);
		}
#endif

		FTransform NewTransform(Force);
		RootMotionParams.Set(NewTransform);
	}
	else
	{
		checkf(Duration > UE_SMALL_NUMBER, TEXT("FRootMotionSource_DynamicTransform prepared with invalid duration."));
	}

	SetTime(GetTime() + SimulationTime);
}

bool FRootMotionSource_DynamicTransform::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	if (!FRootMotionSource::NetSerialize(Ar, Map, bOutSuccess))
	{
		return false;
	}

	Ar << StartTransform; // TODO-RootMotionSource: Quantization
	Ar << InitialTargetTransform; // TODO-RootMotionSource: Quantization
	Ar << TargetTransform; // TODO-RootMotionSource: Quantization
	Ar << bRestrictSpeedToExpected;
	Ar << PathOffsetCurve;
	Ar << TimeMappingCurve;

	bOutSuccess = true;
	return true;
}

UScriptStruct* FRootMotionSource_DynamicTransform::GetScriptStruct() const
{
	return FRootMotionSource_DynamicTransform::StaticStruct();
}

FString FRootMotionSource_DynamicTransform::ToSimpleString() const
{
	return FString::Printf(TEXT("[ID:%u]FRootMotionSource_DynamicTransform %s"), LocalID, *InstanceName.GetPlainNameString());
}

void FRootMotionSource_DynamicTransform::AddReferencedObjects(class FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(PathOffsetCurve);
	Collector.AddReferencedObject(TimeMappingCurve);

	FRootMotionSource::AddReferencedObjects(Collector);
}
*/


UBMCharacterMovementComponent::UBMCharacterMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ProcessRootMotionPreConvertToWorld.BindStatic(UBMCharacterMovementComponent::FixRootMotionTransformStatic);
}

FTransform UBMCharacterMovementComponent::FixRootMotionTransformStatic(const FTransform& InTransform,
	UCharacterMovementComponent* InMovement, float DeltaSeconds)
{
	FTransform OutTransform = InTransform;
	if (ACharacter* Character = InMovement->GetCharacterOwner()) {
		if (UBMAnimInstance* AnimInst = Cast<UBMAnimInstance>(Character->GetMesh()->GetLinkedAnimGraphInstanceByTag(FName("BMAnimInstance")))) {
			// AnimInst->ModifyRootMotionTransform(OutTransform);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("FixRootMotionTransformStatic: %s"), *OutTransform.ToString());
	return OutTransform;
}


void UBMCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UBMCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("TickComponent: %f"), DeltaTime);
}

