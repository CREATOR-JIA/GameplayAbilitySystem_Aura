// Copyright CREATOR-JIA


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController(): LastActor(nullptr), ThisActor(nullptr)
{
	bReplicates = true; // 该控制器可以通过网络进行复制
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit; // 光标碰撞的结果
	// 获取鼠标碰撞结果（参数一是碰撞通道，可见性通道、参数二是跟踪复杂性为false简单跟踪、光标碰撞结果）
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit)return; // 如果碰撞结果中没有有效的碰撞，返回
	LastActor = ThisActor; // 首先最后的Actor等于当前这个Actor.最后的Actor存储当前这个Actor之前的身份
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor()); // 如果碰撞结果中所碰撞的Actor继承于IEnemyInterface，那么就可以进行转换，转换成功后可执行接口函数

	/**
	 * line trace form cursor. There are several scenarios: 追踪结果中有几种情况
	 * A. LastActor is null && ThisActor is null  最后的Actor为空，并且当前这个Actor也为空，例如与鼠标接触的是墙壁、桌子等类似的Actor,不做任何事情
	 *    - Do nothing
	 * B. LastActor is null && ThisActor is valid 最后的Actor为空，且当前这个Actor有效，当前Actor突出显示
	 *    - Highlight ThisActor
	 * C. LastActor is valid && ThisActor is null 最后的Actor有效，并且当前的这个Actor无效，最后的Actor不突出显示
	 *    - UnHighlight LastActor
	 * D. Both actors are valid, but LastActor != ThisActor 最后的Actor与当前的Actor均有效，但是最后的Actor不是当前的Actor,最后的Actor不突出显示，当前这个Actor突出显示
	 *    - UnHighLight LastActor, and HighLight ThisActor
	 * E. Both actors are valid, and are the same actor 最后的Actor与当前的Actor均有效，都是同一种Actor,这意味着鼠标一直悬停在Actor上，因此不需做任何事情
	 *    - Do nothing
	 */
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighLightActor();
		}
		else
		{
			// Case A - both are null, do nothing 
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighLightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
			else
			{
				// Case E - do nothing
				
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	/*增加一个断言，因为AuraContext被我们定义成一个指针，并且在蓝图中需要进行设置，如果未设置该指针，就会出现错误，因此这里我们清加一个断言。
	 * 如果上下文尚未设置，那么就不执行下面任何代码；
	 */
	check(AuraContext);

	// 通过本地玩家来获取增强输入本地玩家子系统，向该系统内添加上下文映射
	//如果增强输入本地玩家子系统有效，将AuraContext上下文映射到本地玩家子系统的上下文中（Priority:0为优先级，最优先即为0）
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) 
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true; // 显示鼠标
	DefaultMouseCursor = EMouseCursor::Default; // 鼠标样式为默认的样式

	FInputModeGameAndUI InputModeData; // 创建输入模式，设置光标在视口中的行为是不锁定，可随意移动。并且当光标出现在视口中后，将不隐藏光标。
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData); // 应用输入模式
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// 由于我们创建了增强输入动作，需要将其绑定到增强输入组件中。因此，需要在该方法中进行输入动作的绑定。但前提是要将输入组件转成增强输入组件
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent); //CastChecked自带检查的转换
	/*有了输入行为（如MoveAction），且还有了输入行为相对应的回调函数（如Move），那么接下来就是将这两者联系起来
	 * ETriggerEvent::Triggered为触发器事件，当触发器状态为Triggered时，也就是当触发器触发后就调用Move这个函数
	 */
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	/*if (GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}*/
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>(); // 在输入的操作值中获取到2D向量（X、Y）
	const FRotator Rotation = GetControlRotation(); // 获取控制器的旋转
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // 保留Z轴旋转，X与Y轴设置为0

	//FRotationMatrix中存放物体相对于世界坐标系的旋转角度信息
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); //前进方向，也就是获取YawRotation的X向单位长度轴
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 向右移动方向，也就是获取YawRotation的Y向单位长度轴

	if (APawn* ControlledPawn = GetPawn<APawn>()) // 如果获取玩家控制的Pawn有效
		{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y); // 设置移动输入，对于前后移动针对的是Y分量
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X); // 设置移动输入，对于左右移动针对的是X分量
		}
}
		