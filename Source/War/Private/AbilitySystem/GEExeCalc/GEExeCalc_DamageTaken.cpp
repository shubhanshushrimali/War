// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExeCalc/GEExeCalc_DamageTaken.h"
#include "WarAttributeSet.h"
#include "WarGameplayTags.h"
#include "WarDebugHelper.h"

struct  FWarDamageCapture 
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)


	FWarDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarAttributeSet, DamageTaken, Target, false)
	}
};

static const FWarDamageCapture& DamageCaptureDef()
{
	static FWarDamageCapture CaptureDef;
	return CaptureDef;
}



UGEExeCalc_DamageTaken::UGEExeCalc_DamageTaken()
{


	RelevantAttributesToCapture.Add(DamageCaptureDef().AttackPowerDef);

	RelevantAttributesToCapture.Add(DamageCaptureDef().DefensePowerDef);

	RelevantAttributesToCapture.Add(DamageCaptureDef().DamageTakenDef);	

	//slow way of doing it 
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>
	//	(
	//		UWarAttributeSet::StaticClass(),
	//		GET_MEMBER_NAME_CHECKED(UWarAttributeSet, AttackPower)
	//	);

	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);

	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);
}

void UGEExeCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EfectSpec = ExecutionParams.GetOwningSpec();
	
	//EfectSpec.GetContext().GetSourceObject();
	//EfectSpec.GetContext().GetAbility(); 
	//EfectSpec.GetContext().GetInstigator();
	//EfectSpec.GetContext().GetEffectCauser();


	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = EfectSpec.CapturedSourceTags.GetAggregatedTags(); 
	EvaluationParameters.TargetTags = EfectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f; 
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageCaptureDef().AttackPowerDef,
		EvaluationParameters,
		SourceAttackPower
	);
	//Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;	
	int32 UsedHeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EfectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WarGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}

		if (TagMagnitude.Key.MatchesTagExact(WarGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}
		if (TagMagnitude.Key.MatchesTagExact(WarGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}



	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude
	(
		DamageCaptureDef().DefensePowerDef,
		EvaluationParameters,
		TargetDefensePower
	);
	//Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
		//Debug::Print(TEXT("BaseDamage"), BaseDamage);
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = (UsedHeavyAttackComboCount - 1) * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		//Debug::Print(TEXT("BaseDamage"), BaseDamage);
	}


	const float FinalDamage =  BaseDamage * (SourceAttackPower / TargetDefensePower);
	///Debug::Print(TEXT("FinalDamage"), FinalDamage);

	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier
		(
			FGameplayModifierEvaluatedData
			(
				DamageCaptureDef().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
}
