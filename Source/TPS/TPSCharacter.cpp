#include "TPSCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gun_Colorful.h"

ATPSCharacter::ATPSCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetMesh()->SetupAttachment(GetCapsuleComponent());
	GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Soldier/Soldier.Soldier'")));

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = 150;
	GetCharacterMovement()->bOrientRotationToMovement = true;	//这样直线运动时才会面向运动方向

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	WeaponComponent->SetupAttachment(GetMesh(), "GunSocket");

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	MuzzleLocation->SetupAttachment(GetMesh());
	MuzzleLocation->SetRelativeLocation(FVector(0.f, 40.f, 100.f));
}


void ATPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("WalkOrRun", IE_Released, this, &ATPSCharacter::WalkOrRun);
	PlayerInputComponent->BindAction("UseCtrlRotYaw", IE_Pressed, this, &ATPSCharacter::UseCtrlRotYaw);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ATPSCharacter::SwitchWeapon);
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &ATPSCharacter::MouseLeftPressed);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPSCharacter::MoveRight);


	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATPSCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATPSCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATPSCharacter::TouchStopped);

}


void ATPSCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ATPSCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ATPSCharacter::WalkOrRun()
{
	if (GetCharacterMovement()->MaxWalkSpeed > 256) { GetCharacterMovement()->MaxWalkSpeed = 150; }
	else { GetCharacterMovement()->MaxWalkSpeed = 550; }
}

void ATPSCharacter::UseCtrlRotYaw()
{
	if (this->bUseControllerRotationYaw) 
	{
		GetMesh()->SetAnimInstanceClass(LoadObject<UAnimBlueprintGeneratedClass>(NULL, TEXT("/Game/Soldier/SoldierAnimBlueprint1.SoldierAnimBlueprint1_C")));
		this->bUseControllerRotationYaw = false;
	}
	else 
	{
		GetMesh()->SetAnimInstanceClass(LoadObject<UAnimBlueprintGeneratedClass>(NULL, TEXT("/Game/Soldier/SoldierAnimBlueprint2.SoldierAnimBlueprint2_C")));
		this->bUseControllerRotationYaw = true;
	}
}

void ATPSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATPSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATPSCharacter::MoveForward(float Value)
{
	MoveForwardValue = Value;
	//this->GetMovementComponent()->AddInputVector(FVector(isNegative ? -CY * MoveForwardValue : CY * MoveForwardValue, SY * MoveForwardValue, 0), false);
}

void ATPSCharacter::MoveRight(float Value)
{
	MoveRightValue = Value;
	//this->GetMovementComponent()->AddInputVector(FVector(-SY * MoveRightValue, isNegative ? -CY * MoveRightValue : CY * MoveRightValue, 0), false);
}

void ATPSCharacter::Tick(float DeltaTime)
{
	//为蓝图内tick生成的事件，暂时不需要。
	//ReceiveTick(DeltaTime);

	// 计算cosine of Yaw and sine of Yaw. 优化平面上角色移动，理论上比RotationMatrix减少6倍计算。
	float Y = Controller->GetControlRotation().Yaw * PI / (180.f);
	if (Y > PI) { Y -= 2 * PI; }
	bool isNegative = false;
	if (Y > PI / 2) { Y = PI - Y; isNegative = true; }
	else if (Y < -PI / 2) { Y = -PI - Y; isNegative = true; }

	float YSquared = Y * Y;

	float SY = 2.7525562e-06f;
	SY = SY * YSquared - 0.00019840874f;
	SY = SY * YSquared + 0.0083333310f;
	SY = SY * YSquared - 0.16666667f;
	SY = SY * YSquared + 1.0f;
	SY = SY * Y;

	float CY = 2.4760495e-05f;
	CY = CY * YSquared - 0.0013888378f;
	CY = CY * YSquared + 0.041666638f;
	CY = CY * YSquared - 0.5f;
	CY = CY * YSquared + 1.0f;
	if (isNegative) {
		CY = -CY;
	}

	this->GetMovementComponent()->AddInputVector(FVector(
		-SY * MoveRightValue +  CY * MoveForwardValue,
		SY * MoveForwardValue+  CY * MoveRightValue,
		0), false);

}


void ATPSCharacter::HoldWeapon(UClass* p) //传入武器类：在世界中生成类的对象，并将WeaponComponent变成类指定的样子
{
	Weapon = (AWeapon*)(GetWorld()->SpawnActor(p));
	Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"GunSocket");
	Weapon->Owner = this;
	WeaponComponent->SetSkeletalMesh(Weapon->Mesh);
}



void ATPSCharacter::Pick(UClass* p)
{
	if(p!=nullptr)
		Bag.Add(p);
	else
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Pick(nullptr)")));
}

void ATPSCharacter::SwitchWeapon() 
{
	int BagNum = Bag.Num();
	if (BagNum == 0) { return; }

	if(IndexOfWeapon >= BagNum){
		IndexOfWeapon -= BagNum;
	}
	HoldWeapon(Bag[IndexOfWeapon++]);
}

void ATPSCharacter::MouseLeftPressed()
{
	if (Weapon != nullptr)
	{
		Weapon->Fire();
	}
}

void ATPSCharacter::OnHurt(uint32 damage)
{

}


//UE_LOG(LogTemp, Warning, TEXT("Your message:Gun ! = nullptr"));
