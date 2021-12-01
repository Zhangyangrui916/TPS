// Fill out your copyright notice in the Description page of Project Settings.

#include "TPSCharacter.h"
#include "PickableItem.h"

// Sets default values
APickableItem::APickableItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("RootScene"));
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Root);

	Root->SetSimulatePhysics(false);
	Root->SetGenerateOverlapEvents(true);
	Root->SetCollisionProfileName(TEXT("OverlapAll"));
	Root->OnComponentBeginOverlap.AddDynamic(this, &APickableItem::OnOverlapBegin);
}

void APickableItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ATPSCharacter* c =  Cast<ATPSCharacter>(OtherActor);
	if (c != nullptr) {
		c->Pick(uclass);
		Destroy();
	}
	
}

