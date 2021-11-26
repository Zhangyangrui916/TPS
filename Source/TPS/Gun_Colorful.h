// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Gun_Colorful.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AGun_Colorful : public AGun
{
	GENERATED_BODY()

public:
	AGun_Colorful();

	virtual void Fire() override;

	void AutoFire(); //这是一把全自动步枪
	
};
