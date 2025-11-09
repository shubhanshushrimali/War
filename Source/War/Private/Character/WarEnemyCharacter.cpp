// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/DataAssetEnemyStartUpData.h"
#include "Component/UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/WarWidgetBase.h"


AWarEnemyCharacter::AWarEnemyCharacter()
{

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

	EnemyHealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthBarWidgetComponent"));

	EnemyHealthBarWidgetComponent->SetupAttachment(GetMesh());
}

UPwanCombatComponent* AWarEnemyCharacter::GetPawnCombactComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AWarEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AWarEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AWarEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	UWarWidgetBase* HealthWidget = Cast<UWarWidgetBase>(EnemyHealthBarWidgetComponent->GetUserWidgetObject());

	if (HealthWidget)
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
	//InitEnemyStartUpData();
}

void AWarEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData(); 
}

void AWarEnemyCharacter::InitEnemyStartUpData()
{

	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
			  
				UDataAsset_StartUpDataBase* LoadedStartUpData = CharacterStartUpData.Get();
				if (LoadedStartUpData)
				{
					LoadedStartUpData->GiveToAbilitySystemComponent(WarAbilitySystemComponent);
				}
			}
		)
	);

}
