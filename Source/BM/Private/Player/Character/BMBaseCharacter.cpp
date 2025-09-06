// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Character/BMBaseCharacter.h"

// Sets default values
ABMBaseCharacter::ABMBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called to bind functionality to input
void ABMBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

