// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSCharacter.h"
#include "SoldierAnimInstanceCPP.generated.h"
/**
 * 
 */
UCLASS(transient, Blueprintable)
class TPS_API USoldierAnimInstanceCPP : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OwningCharacter")
		ATPSCharacter* OwningCharacter;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

};
