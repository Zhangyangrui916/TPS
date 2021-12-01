#pragma once
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "Weapon.h"
#include "Grenade.generated.h"



UCLASS()
class TPS_API AGrenade : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComp;
	UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* EmitterTemplate;
	
public:	
	AGrenade();

	UPROPERTY(EditAnywhere)
		int n;	//ÊýÁ¿

	void Fire() override;

	void Boom();

};
