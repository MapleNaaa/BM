// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomResult.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "LoginWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class BM_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
protected:
	UFUNCTION(BlueprintCallable)
	virtual void CreateRoom();

	UFUNCTION(BlueprintCallable)
	virtual void CreateRoomSuccess();
	UFUNCTION(BlueprintCallable)
	virtual void CreateRoomFailed();

	UFUNCTION(BlueprintCallable)
	virtual void SearchRooms();

	UFUNCTION(BlueprintCallable)
	virtual void SearchRoomsSuccess(const TArray<FBlueprintSessionResult>& Results);

	UFUNCTION(BlueprintCallable)
	virtual void SearchRoomsFailed(const TArray<FBlueprintSessionResult>& Results);


protected:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CreateRoomButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> SearchRoomsButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> RoomListScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<URoomResult> RoomResultClass; 

};


