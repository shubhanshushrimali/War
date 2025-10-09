// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarHeroCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Component/Input/WarInputComponent.h"
#include "WarGameplayTags.h"	
#include "EnhancedInput/Public/InputActionValue.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"

#include "WarDebugHelper.h"


AWarHeroCharacter::AWarHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));	
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);	
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AWarHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (WarAbilitySystemComponent && WarAttributeSet)
	{
		Debug::Print(FString::Printf(TEXT("Ability sys6tem is vaild ")));
	}
}

void AWarHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    checkf(InputConfigDataAsset, TEXT("forgot to assign a vaild data assest as a input config"));

   ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

   UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

   check(Subsystem);	

   Subsystem->AddMappingContext(InputConfigDataAsset->DefaultInputMappingContext, 0);

   UWarInputComponent* WarInputComponent = CastChecked<UWarInputComponent>(PlayerInputComponent);

   WarInputComponent->BindNativeInputAction(InputConfigDataAsset, WarGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

   WarInputComponent->BindNativeInputAction(InputConfigDataAsset, WarGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
}

void AWarHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print(FString::Printf(TEXT("Hero Character Begin Play: %s"), *GetName()));
}

void AWarHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();	
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector FowardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(FowardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void AWarHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{

	const FVector2D LoookAxisVector = InputActionValue.Get<FVector2D>();

	if (LoookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LoookAxisVector.X);
	}

	if (LoookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LoookAxisVector.Y);
	} 

}
