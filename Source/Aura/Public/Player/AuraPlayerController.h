// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; // 设置输入绑定

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext; // 输入映射上下文环境（UE5编辑器中我们创建的IMC），用来将按键与InputAction对应。在UE编辑器中加载；
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction; // 输入行为：移动，在UE编辑器中加载，在C++中的增强输入组件中进行绑定

	void Move(const FInputActionValue& InputActionValue); // 移动功能函数（参入参数是一个输入动作值类型的变量）
};
