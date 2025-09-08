// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BMCharacterMovementComponent.generated.h"

/** 
 * MoveToDynamicForce moves the target to a given location in world space over the duration, where the end location
 * is dynamic and can change during the move (meant to be used for things like moving to a moving target)
 */
 /*
USTRUCT()
struct FRootMotionSource_DynamicTransform : public FRootMotionSource
{
	GENERATED_USTRUCT_BODY()

	ENGINE_API FRootMotionSource_DynamicTransform();

	virtual ~FRootMotionSource_DynamicTransform() {}

	UPROPERTY()
	FTransform StartTransform;

	UPROPERTY()
	FTransform InitialTargetTransform;

	// Dynamically-changing location of target, which may be altered while this movement is ongoing 
	UPROPERTY()
	FTransform TargetTransform;

	UPROPERTY()
	bool bRestrictSpeedToExpected;

	UPROPERTY()
	TObjectPtr<UCurveVector> PathOffsetCurve;

	UPROPERTY()
	TObjectPtr<UCurveFloat> TimeMappingCurve;

	ENGINE_API void SetTargetTransform(FTransform NewTargetTransform);

	ENGINE_API FVector GetPathOffsetInWorldSpace(const float MoveFraction) const;

	ENGINE_API virtual FRootMotionSource* Clone() const override;

	ENGINE_API virtual bool Matches(const FRootMotionSource* Other) const override;

	ENGINE_API virtual bool MatchesAndHasSameState(const FRootMotionSource* Other) const override;

	ENGINE_API virtual bool UpdateStateFrom(const FRootMotionSource* SourceToTakeStateFrom, bool bMarkForSimulatedCatchup = false) override;

	ENGINE_API virtual void SetTime(float NewTime) override;

	ENGINE_API virtual void PrepareRootMotion(
		float SimulationTime, 
		float MovementTickTime,
		const ACharacter& Character, 
		const UCharacterMovementComponent& MoveComponent
		) override;

	ENGINE_API virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	ENGINE_API virtual UScriptStruct* GetScriptStruct() const override;

	ENGINE_API virtual FString ToSimpleString() const override;

	ENGINE_API virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;
};

template<>
struct TStructOpsTypeTraits< FRootMotionSource_DynamicTransform > : public TStructOpsTypeTraitsBase2< FRootMotionSource_DynamicTransform >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};*/

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BM_API UBMCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UBMCharacterMovementComponent();
	static FTransform FixRootMotionTransformStatic(const FTransform& InTransform, UCharacterMovementComponent* InMovement, float DeltaSeconds);

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
