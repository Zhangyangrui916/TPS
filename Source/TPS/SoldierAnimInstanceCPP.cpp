#include "SoldierAnimInstanceCPP.h"
#include "GameFramework/CharacterMovementComponent.h"

void USoldierAnimInstanceCPP::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = (ATPSCharacter*)TryGetPawnOwner();
	UE_LOG(LogTemp, Warning, TEXT("Your message: set OwningCharacter"));
}

void USoldierAnimInstanceCPP::NativeUpdateAnimation(float DeltaTimeX)
{
	if(OwningCharacter)
		bIsFalling = OwningCharacter->GetMovementComponent()->IsFalling();
	else
		UE_LOG(LogTemp, Warning, TEXT("Your message:OwningCharacter = nullptr"));


}
