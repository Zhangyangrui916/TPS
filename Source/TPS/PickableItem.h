// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components\BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

UCLASS()
class TPS_API APickableItem : public AActor
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
		UBoxComponent* Root;

	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* StaticMesh; //可拾取物品的外观
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* SkeletalMesh; //可拾取物品的外观
public:	

	// Sets default values for this actor's properties
	APickableItem();

	UPROPERTY(EditAnywhere, Category = Class)
	UClass* uclass;	//该可拾取物品所对应的类（枪、手雷....etc）

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
