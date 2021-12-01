// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"
class ATPSCharacter;
UCLASS()
class TPS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMesh* Mesh;	//武器外形

	ATPSCharacter* Owner; //武器的拥有者

	virtual void Fire(); //武器发动攻击（开枪/投掷/挥刀）

	FTimerHandle FireTimerHandle; //武器计时器。比如用于连射时，对ShootIntervel时间计时实现射速控制。比如手雷在定时后爆炸。

};
