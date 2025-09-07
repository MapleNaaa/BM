
#pragma once

#include "CoreMinimal.h"
#include "BMAnimationTypes.generated.h"


UENUM(BlueprintType)
enum class EBMSMStage : uint8
{
    Idle = 0,
    Start = 1,
    Loop = 2,
    Stop = 3,
    Pivot = 4,
    Jump = 5,
    Turn = 6,
};