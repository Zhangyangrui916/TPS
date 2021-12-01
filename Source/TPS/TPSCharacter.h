#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "TPSCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyTESTSignature, float, nHealth);
UCLASS(config = Game)
class ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
		FMyTESTSignature OnHurtDelegate;

public:
	ATPSCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, Category = Gun)
		USceneComponent* MuzzleLocation; //ǹ��λ��,��������������ͳһǹ��������˵�λ�á�
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* WeaponComponent;	//����set��ͬ��mesh��������ɲ�ͬ��������
	UPROPERTY(EditAnywhere, Category = Camera)
		float BaseTurnRate = 45.f;
	UPROPERTY(EditAnywhere, Category = Camera)
		float BaseLookUpRate=45.f;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Camera)
		AWeapon* Weapon;

	TArray<UClass*> Bag;	//�����е���Ʒ�ࡣ���ڿ���ӵ�ж������Ʒ��������Ӧ�С���������Ա��

	void HoldWeapon(UClass* p);
	void MouseLeftPressed();
	void Pick(UClass* p);

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
	void WalkOrRun();
	void SwitchWeapon();
	void UseCtrlRotYaw();
	uint8 IndexOfWeapon = 0;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	// APawn interface


public:
	void OnHurt(uint32 damage);		//�ܵ�����


};

