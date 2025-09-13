// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Login/RoomResult.h"

#include "JoinSessionCallbackProxy.h"
#include "GameFramework/GameSession.h"
class UTextBlock;

void URoomResult::NativeConstruct()
{
	Super::NativeConstruct();
}

void URoomResult::InitRoomResult(float InPingInMs, int32 InCurrentPlayers, int32 InMaxPlayers, const FString& InRoomName)
{
	PingInMs = InPingInMs;
	CurrentPlayers = InCurrentPlayers;
	MaxPlayers = InMaxPlayers;
	RoomName = InRoomName;
	PingTextBlock->SetText(FText::FromString(FString::Printf(TEXT("帧率: %.0fms "), InPingInMs)));
	PlayersTextBlock->SetText(FText::FromString(FString::Printf(TEXT("玩家: %d/%d "), InCurrentPlayers, InMaxPlayers)));
	RoomNameTextBlock->SetText(FText::FromString(FString::Printf(TEXT("房间: %s" ), *InRoomName)));
}
