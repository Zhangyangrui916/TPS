#include "Bullet.h"
#include "TPSCharacter.h"
#include "Zoombie.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = CollisionComp;
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Bullet");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	InitialLifeSpan = 3.0f;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BulletMesh->SetupAttachment(CollisionComp);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->bShouldBounce = true;
}


void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity()*100, GetActorLocation());
		Destroy();
		AZoombie* otherCharacter = dynamic_cast<AZoombie*>(OtherActor);
		if (otherCharacter)
		{
			otherCharacter->OnHurt(5);
		}
	}
}
