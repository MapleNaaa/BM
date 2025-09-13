#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Kismet/GameplayStatics.h"
#include "BMSettings.generated.h"

/**
 * 自定义设置，能出现在 Project Settings 里
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName="BM Settings"))
class BM_API UBMSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
	UBMSettings();
public:
	static const UBMSettings* Get() {return GetDefault<UBMSettings>();}
	void SetSensitivity(float Value);
	float GetSensitivity() const {return Sensitivity;}

	int32 GetPlayerMaxNum() const {return PlayerMaxNum;}
	int32 GetSearchRoomsNum() const {return SearchRoomsNum;}
	TSoftObjectPtr<UWorld> GetDefaultMap() const {return DefaultMap;}
	
protected:
	// 灵敏度
	UPROPERTY(Config, EditAnywhere, Category="BM|Input")
	float Sensitivity = 1.0f;

	UPROPERTY(Config, EditAnywhere, Category="BM|Input")
	float SensitivityMaxClamp = 3.0f;

	UPROPERTY(Config, EditAnywhere, Category="BM|Input")
	float SensitivityMinClamp = 0.1f;

	// 最大玩家数
	UPROPERTY(Config, EditAnywhere, Category="BM|Gameplay")
	int32 PlayerMaxNum = 4;

	// 搜索房间数量
	UPROPERTY(Config, EditAnywhere, Category="BM|Gameplay")
	int32 SearchRoomsNum = 10;

	// 默认地图
	UPROPERTY(Config, EditAnywhere, Category="BM|Gameplay")
	TSoftObjectPtr<UWorld> DefaultMap;
};
