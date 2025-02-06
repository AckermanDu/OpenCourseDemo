// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "Game2/Myself/MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (MyCharacter == nullptr)
	{
		MyCharacter = Cast<AMyCharacter >(TryGetPawnOwner());
	}
	if (MyCharacter == nullptr) return;

	FVector Velocity = MyCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = MyCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = MyCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

}