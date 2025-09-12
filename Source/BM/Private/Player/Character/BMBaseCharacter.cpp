// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Character/BMBaseCharacter.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"

// Sets default values
ABMBaseCharacter::ABMBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ABMBaseCharacter::ABMBaseCharacter(const FObjectInitializer& ObjectInitializer)
{
	
}

// Called when the game starts or when spawned
void ABMBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 获取玩家状态和网络角色
	APlayerState* TmpPlayerState = GetPlayerState();
	FString ClientID = TmpPlayerState ? FString::Printf(TEXT("ClientID:%d"), TmpPlayerState->GetPlayerId()) : TEXT("NoPlayerState");
	FString RoleStr = GetLocalRole() == ROLE_Authority ? TEXT("Server") : TEXT("Client");
    
	/*UE_LOG(LogTemp, Log, TEXT("ABMBaseCharacter::Tick - %s [%s] Name: %s Location %s Rotation: %s"), 
		*RoleStr, 
		*ClientID, 
		*GetName(), 
		*(GetActorLocation() - LastLocation).ToString(),
		*GetActorRotation().ToString());*/

	LastLocation = GetActorLocation();
}

// Called to bind functionality to input
void ABMBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

