// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAnimInstanceCPP.h"


void USoldierAnimInstanceCPP::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = (ATPSCharacter*)TryGetPawnOwner();
}

void USoldierAnimInstanceCPP::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
}
