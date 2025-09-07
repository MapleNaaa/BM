// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BMAnimLayerInstance.h"
#include "Animation/BMAnimInstance.h"
#include "ChooserFunctionLibrary.h"

void UBMAnimLayerInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ACharacter* OwningCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(OwningCharacter)) return;
	BMAnimInstance = Cast<UBMAnimInstance>(OwningCharacter->GetMesh()->GetAnimInstance());
}

void UBMAnimLayerInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (!IsValid(BMAnimInstance)) return;

	CurrentCharacterGate = BMAnimInstance->CurrentCharacterGate;
	CurrentTurnType = BMAnimInstance->CharacterTurnType;
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
