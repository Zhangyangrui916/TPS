#include "Grenade.h"
#include "TPSCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
AGrenade::AGrenade()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(1.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	RootComponent = CollisionComp;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	MeshComponent->SetupAttachment(CollisionComp);
	MeshComponent->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/G67_Grenade/SK_G67.SK_G67'")));
}

void AGrenade::Fire()
{
	if (!Mesh) {//����һ��û�õĳ�Ա��Ϊ��ǣ�ʹ�øú���ִֻ��һ�Ρ�
		Mesh = (USkeletalMesh*)MeshComponent;
		CollisionComp->SetSimulatePhysics(true);
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		CollisionComp->AddImpulse(Owner->GetActorForwardVector() * 32);
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AGrenade::Boom, 3.f, false);
	}
}

void AGrenade::Boom()
{
	UWorld* World = GetWorld();
	FVector thisLocation = this->GetActorLocation();

	//��Ч����
	if (FApp::CanEverRender() && World && !World->IsNetMode(NM_DedicatedServer))
	{
		AActor* WorldSettings = World->GetWorldSettings();
		UParticleSystemComponent*  PSC = NewObject<UParticleSystemComponent>((WorldSettings ? WorldSettings : (UObject*)World));
		PSC->bAutoDestroy = true;
		PSC->bAllowAnyoneToDestroyMe = true;
		PSC->SecondsBeforeInactive = 0.0f;
		PSC->SetTemplate(EmitterTemplate);
		PSC->SetUsingAbsoluteLocation(true);
		PSC->SetUsingAbsoluteRotation(true);
		PSC->SetRelativeLocation_Direct(thisLocation);
		PSC->SetRelativeRotation_Direct(this->GetActorRotation());
		PSC->SetRelativeScale3D_Direct(FVector(4,4,4));
		PSC->RegisterComponentWithWorld(World);
		PSC->ActivateSystem(true);
	}

	//AOEЧ������
	TArray<TEnumAsByte <EObjectTypeQuery>>  destObjectTypes;
	//destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_Pawn); 
	//destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_WorldStatic);  //StaticMesh��ʾҪ��ΪMovable����AddImpulse����������ΪMovable���ͨ���ּ�ⲻ������ν����
	destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_PhysicsBody);
	//destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_WorldDynamic); 
	destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_Visibility);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	TArray<UPrimitiveComponent*> OverlapComponents;
	UKismetSystemLibrary::SphereOverlapComponents(World, thisLocation, 500, destObjectTypes, NULL, ActorsToIgnore, OverlapComponents);
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%d"), OverlapComponents.Num()));
	for (UPrimitiveComponent* comp : OverlapComponents) {
		FVector vecImpulse = comp->GetComponentLocation()- thisLocation;
		vecImpulse *= (10000000 / vecImpulse.SizeSquared());
		comp->AddImpulse(vecImpulse);
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, comp->GetFullName());
	}


	Destroy();
}

