#include "TPSCharacter.h"
#include "Gun_Colorful.h"

AGun_Colorful::AGun_Colorful() 
{
	Mesh=LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	nMaxAmmo = 30;
	nAmmo = nMaxAmmo;
	nDamage = 25;
	
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> tmp(TEXT("Blueprint'/Game/Weapon/Bullet_BP.Bullet_BP'"));
	if (tmp.Object)
	{
		BlueprintBullet = (UClass*)tmp.Object->GeneratedClass;
	}
}



void AGun_Colorful::Fire()
{	
	bKeepFiring = true;
	AutoFire();
}

void AGun_Colorful::AutoFire()
{
	if (bKeepFiring)
	{
		if (nAmmo == 0) {
			bKeepFiring = false;
			//枪支让自己的所有者开始换弹
		}
		else {
			UWorld* w = GetWorld();
			w->GetTimerManager().SetTimer(FireTimerHandle, this, &AGun_Colorful::AutoFire, ShootIntervel, false);
			nAmmo--;
			GetWorld()->SpawnActor<ABullet>(BlueprintBullet
				, Owner->MuzzleLocation->GetComponentLocation()
				, Owner->GetControlRotation());

		}
	}
	else {
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
	}
}
