// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Controller/BMPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ES/BMPlayerTypes.h"
#include "GameFramework/Character.h"
#include "Player/Character/BMPlayerCharacter.h"

void ABMPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem && InputMappingContext) 
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABMPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABMPlayerController::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABMPlayerController::Jump);
}

void ABMPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	ABMPlayerCharacter* BMCharacter = Cast<ABMPlayerCharacter>(GetCharacter());
	if (!IsValid(BMCharacter)) return;

	if (bIsJogging || LastIsJogging)
	{
		BMCharacter->SetCharacterGate(EBMCharacterGate::Run);
	}
	else
	{
		BMCharacter->SetCharacterGate(EBMCharacterGate::Walk);
	}
	bIsJogging = false;
	
	const FVector ForwardDirection = BMCharacter->GetActorForwardVector();
	const FVector RightDirection = BMCharacter->GetActorRightVector();

	BMCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	BMCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void ABMPlayerController::Jog(const FInputActionValue& Value)
{
	LastIsJogging = bIsJogging;
	bIsJogging = true;
}

void ABMPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookDirection = Value.Get<FVector2D>();
	ACharacter* BMCharacter = GetCharacter();
	if (!IsValid(BMCharacter)) return;

	BMCharacter->AddControllerYawInput(LookDirection.X);
	BMCharacter->AddControllerPitchInput(-LookDirection.Y);
}

void ABMPlayerController::Jump(const FInputActionValue& Value)
{
	ACharacter* BMCharacter = GetCharacter();
	if (!IsValid(BMCharacter)) return;
	BMCharacter->Jump();
}

void ABMPlayerController::LightAttack(const FInputActionValue& Value)
{
}

void ABMPlayerController::HeavyAttack(const FInputActionValue& Value)
{
}

void ABMPlayerController::Inventory(const FInputActionValue& Value)
{
}
