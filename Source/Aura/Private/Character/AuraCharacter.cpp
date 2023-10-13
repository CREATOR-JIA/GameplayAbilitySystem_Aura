// Copyright CREATOR-JIA


#include "Character/AuraCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AAuraCharacter::AAuraCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 750;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; //如果为真，角色旋转到加速方向
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); // 设置角色转身速度
	GetCharacterMovement()->bConstrainToPlane = true; // 将角色的移动限制在平面上
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 如果为true并且开启了平面约束，当更新组件时，将在第一次附着时捕捉到平面

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
