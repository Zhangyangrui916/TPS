#include "Zoombie.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AZoombie::AZoombie()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetupAttachment(RootComponent);
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	nHealth = 255;


}

// Called when the game starts or when spawned
void AZoombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AZoombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZoombie::OnHurt(uint8 damage)
{
	if (nHealth > damage) {
		nHealth -= damage;
	}
	else {
		nHealth = 0;
		this->Destroy();
	}
	EnemyOnHurtDelegate.Broadcast(1);
}

