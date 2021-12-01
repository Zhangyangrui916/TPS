#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zoombie.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyOnHurt, uint8, damage);
UCLASS()
class AZoombie : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
		FEnemyOnHurt EnemyOnHurtDelegate;

public:
	// Sets default values for this character's properties
	AZoombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
		uint8 nHealth;

	UFUNCTION()
		void OnHurt(uint8 damage);


};
