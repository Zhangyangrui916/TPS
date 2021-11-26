#pragma once
#include "CoreMinimal.h"
#include "Ammo.h"
#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"
class ABullet;
class ATPSCharacter;
UCLASS()
class TPS_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();


	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMesh* Mesh;	//ǹ֧����

	ATPSCharacter* Owner; //���ǹ��ӵ����

	UPROPERTY(EditAnywhere,Category = Ammo) 
		uint8 nMaxAmmo;	//һ����ϻ�����ӵ�����

	UPROPERTY(EditAnywhere, Category = Damage)
		uint8 nDamage;	//�Ի��ж�������ɵ��˺��������ֵ�������������ȥ��projectile��

	UPROPERTY(EditAnywhere)
		float ShootIntervel;	//���ٵĵ�����ÿ��ShootIntervelʱ�䷢��һö�ӵ�

	uint8 nAmmo;	//��ǰ��ϻ���ӵ�����

	AmmoType AmmoType;	//��ǹ��ʹ�õĵ�ҩ����

	FTimerHandle FireTimerHandle; //��������ʱ����ShootIntervelʱ���ʱ

	bool bKeepFiring = false;	//��������ʱָʾ�������Ƿ񱣳ְ���

	UPROPERTY(EditAnywhere, Category = Ammo)
	TSubclassOf<ABullet> BlueprintBullet; //������һ������ABullet���ɵ���ͼ��BlueprintBullet����


public:	

	virtual void Fire();

};
