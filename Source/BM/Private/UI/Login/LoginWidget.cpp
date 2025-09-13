// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Login/LoginWidget.h"
#include "CreateSessionCallbackProxy.h"
#include "CreateSessionCallbackProxyAdvanced.h"
#include "FindSessionsCallbackProxyAdvanced.h"
#include "FindSessionsCallbackProxy.h"
#include "DSP/BufferDiagnostics.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Setting/BMSettings.h"


void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULoginWidget::CreateRoom()
{	
	int32 MaxPlayers = UBMSettings::Get()->GetPlayerMaxNum();
	APlayerController* PC = GetOwningLocalPlayer()->GetPlayerController(GetWorld());
	UCreateSessionCallbackProxyAdvanced* ProxyAdvanced = UCreateSessionCallbackProxyAdvanced::CreateAdvancedSession(this,
	 	TArray<FSessionPropertyKeyPair>(), PC, MaxPlayers, 0, false, true,
	 	false,true, true, false, false,
	 	true,true, false, true);
	if(ProxyAdvanced)
	{
		ProxyAdvanced->OnSuccess.AddDynamic(this, &ThisClass::CreateRoomSuccess);
		ProxyAdvanced->OnFailure.AddDynamic(this, &ThisClass::CreateRoomFailed);
	}
	ProxyAdvanced->Activate();
	
}

void ULoginWidget::CreateRoomSuccess()
{
	TSoftObjectPtr<UWorld> DefaultMap =  UBMSettings::Get()->GetDefaultMap();
	FString MapName = DefaultMap.IsValid() ? DefaultMap.GetAssetName() : FString("MainMap");
	UGameplayStatics::OpenLevel(this, FName(MapName), true, "listen");
	UE_LOG(LogTemp, Warning, TEXT("Creating a new Gameplay Session"));
}

void ULoginWidget::CreateRoomFailed()
{
	UE_LOG(LogTemp, Warning, TEXT("Create Room Failed"));
}

void ULoginWidget::SearchRooms()
{
	int32 SearchRoomResultsNum = UBMSettings::Get()->GetSearchRoomsNum();
	APlayerController* PC = GetOwningLocalPlayer()->GetPlayerController(GetWorld());
	UFindSessionsCallbackProxyAdvanced* ProxyAdvanced = UFindSessionsCallbackProxyAdvanced::FindSessionsAdvanced(this,
		PC,SearchRoomResultsNum, false,
		EBPServerPresenceSearchType::AllServers,TArray<FSessionsSearchSetting>(), false, false,
		false, 0);

	if (ProxyAdvanced)
	{
		ProxyAdvanced->OnSuccess.AddDynamic(this, &ThisClass::SearchRoomsSuccess);
		ProxyAdvanced->OnFailure.AddDynamic(this, &ThisClass::SearchRoomsFailed);
	}
	ProxyAdvanced->Activate();
	// UFindSessionsCallbackProxy* Proxy = UFindSessionsCallbackProxy::FindSessions(this, PC, SearchRoomResultsNum, false, true);
	
}

void ULoginWidget::SearchRoomsSuccess(const TArray<FBlueprintSessionResult>& Results)
{
	if (Results.Num() == 0) return;
	RoomListScrollBox->ClearChildren();
	for (const FBlueprintSessionResult& Result : Results)
	{
		int32 PingInMs = Result.OnlineResult.PingInMs;
		int32 CurrentPlayers = Result.OnlineResult.Session.NumOpenPublicConnections;
		int32 MaxPlayers = Result.OnlineResult.Session.SessionSettings.NumPublicConnections;
		FString RoomName = Result.OnlineResult.Session.OwningUserName;

		TObjectPtr<URoomResult> RoomResult = CreateWidget<URoomResult>(GetWorld(), RoomResultClass);
		if (!IsValid(RoomResult)) continue;
		RoomResult->InitRoomResult(PingInMs, CurrentPlayers, MaxPlayers, RoomName);
		RoomResult->SetSearchResult(Result);
		RoomListScrollBox->AddChild(RoomResult);
	}
	
}

void ULoginWidget::SearchRoomsFailed(const TArray<FBlueprintSessionResult>& Results)
{
	UE_LOG(LogTemp, Warning, TEXT("Search Rooms Failed"));
}
