// Copyright CREATOR-JIA


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


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

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 完成ASC在服务端的初始化
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 完成ASC在客户端的初始化
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo() // 初始化技能角色信息方法
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); // 首先要获取到玩家状态PlayerState
	check(AuraPlayerState); // 断言玩家状态是否有效，无效直接退出
	// 如果玩家状态有效，通过玩家状态获取到技能系统组件，并调用组件中的初始化技能参与者信息方法进行初始化
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent(); // 通过玩家状态获取到技能系统组件
	AttributeSet = AuraPlayerState->GetAttributeSet(); // 通过玩家状态获取到属性集

	if(AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))// 将获取的Controller映射成AAuraPlayerController
	{
		// 只有当AuraPlayerController不是空指针时才可以继续下面的代码
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverly(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	
}
