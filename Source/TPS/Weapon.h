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
		USkeletalMesh* Mesh;	//��������

	ATPSCharacter* Owner; //������ӵ����

	virtual void Fire(); //����������������ǹ/Ͷ��/�ӵ���

	FTimerHandle FireTimerHandle; //������ʱ����������������ʱ����ShootIntervelʱ���ʱʵ�����ٿ��ơ����������ڶ�ʱ��ը��

};
