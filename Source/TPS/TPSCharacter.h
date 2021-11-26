
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
		USceneComponent* MuzzleLocation; //ǹ��λ��,��������������ͳһǹ��������˵�λ�á�
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* GunComponent;	//����set��ͬ��mesh��������ɲ�ͬ����ǹ
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
	//�ƶ�ʱ������������������������ֵ������tick�м����ƶ����� �� �˷����ƶ���Blend2D����ά����
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
	void OnHurt(uint32 damage);		//�ܵ�����


};

