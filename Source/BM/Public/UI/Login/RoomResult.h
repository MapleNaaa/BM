// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FindSessionsCallbackProxy.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RoomResult.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class BM_API URoomResult : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void InitRoomResult(float InPingInMs, int32 InCurrentPlayers, int32 InMaxPlayers, const FString& InRoomName);
	virtual void SetSearchResult(const FBlueprintSessionResult& InSearchResult) { SearchResult = InSearchResult; }
	
protected:
	
	UPROPERTY(BlueprintReadWrite, Category="Room")
	float PingInMs = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category="Room")
	int32 CurrentPlayers = 0;
	
	UPROPERTY(BlueprintReadWrite, Category="Room")
	int32 MaxPlayers = 0;

	UPROPERTY(BlueprintReadWrite, Category="Room")
	FString RoomName = FString("Unknown");

	UPROPERTY(BlueprintReadWrite, Category="Room")
	FBlueprintSessionResult SearchResult;

	

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PingTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PlayersTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> RoomNameTextBlock;

	/** Logic in Blueprint */
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> JoinRoomButton;
};
