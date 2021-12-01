#pragma once
#include "CoreMinimal.h"

#include "Weapon.h"
#include "Ammo.h"
#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"
class ABullet;
class ATPSCharacter;


UCLASS()
class TPS_API AGun : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	UPROPERTY(EditAnywhere,Category = Ammo) 
		uint8 nMaxAmmo;	//一个弹匣里面子弹数量

	UPROPERTY(EditAnywhere, Category = Damage)
		uint8 nDamage;	//对击中对象所造成的伤害。这个数值将传给它发射出去的projectile。

	UPROPERTY(EditAnywhere)
		float ShootIntervel;	//射速的倒数，每隔ShootIntervel时间发射一枚子弹

	uint8 nAmmo;	//当前弹匣内子弹数量

	AmmoType AmmoType;	//该枪所使用的弹药类型

	bool bKeepFiring = false;	//用于连射时指示鼠标左键是否保持按下

	UPROPERTY(EditAnywhere, Category = Ammo)
	TSubclassOf<ABullet> BlueprintBullet; //将发射一个基于ABullet生成的蓝图类BlueprintBullet对象


};
