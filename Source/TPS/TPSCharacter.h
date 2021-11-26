
#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GameFramework/Character.h"
#include "TPSCharacter.generated.h"

UCLASS(config = Game)
class ATPSCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	ATPSCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, Category = Gun)
		USceneComponent* MuzzleLocation; //枪口位置,对于所有武器，统一枪口相对于人的位置。
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* GunComponent;	//给它set不同的mesh，让它变成不同外表的枪
	UPROPERTY(EditAnywhere, Category = Camera)
		float BaseTurnRate = 45.f;
	UPROPERTY(EditAnywhere, Category = Camera)
		float BaseLookUpRate=45.f;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Camera)
		AGun* Gun;

	void HoldGun(UClass* p);
	void MouseLeftPressed();

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	//移动时以上两个函数更新以下两个值，用于tick中计算移动方向 和 八方向移动中Blend2D的两维输入
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float MoveForwardValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float MoveRightValue;

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins./stops */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	void Pick();
	void WalkOrRun();

	void UseCtrlRotYaw();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	// APawn interface


public:
	void OnHurt(uint32 damage);		//受到攻击


};

