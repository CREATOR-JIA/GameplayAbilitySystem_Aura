// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class AAuraPlayerController;
class AAuraPlayerState;
class UAuraAbilitySystemComponent;
class UAuraAttributeSet;

USTRUCT(BlueprintType) // 有可能会在蓝图中使用这种类型，因此添加上BlueprintType说明符
struct FWidgetControllerParams // 结构体，小部件控制器参数。这个结构体进行小部件控制器的初始化很方便
{
	GENERATED_BODY() // 若要进行反射，这个宏必须添加上

	FWidgetControllerParams() {} // 构造函数
	// 有参构造，利用初始化列表直接对变量进行初始化
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}
	// 下面是这个结构体的变量
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr; // 当创建结构体对象时，如果不事先初始化指针变量，系统有可能会给出警告

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 技能系统组件中，属性集中设置了相关的属性。而我们的小部件会用到这些属性的数据，因此将由我们的小部件控制器来获取这些属性的数据，也就是UAureWidgetController来获取这些属性数据
 * 获取到的属性数据将会广播给任何设置了该小部件控制器的的Widget
 * 我们的小部件控制器需要一组变量,通过这些变量来获取相应的信息内容
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject // 这是所有小部件控制器的基类，是个Object类
{
	GENERATED_BODY()

public:
	// 该方法用于设置小部件控制器参数，通过结构体传参
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues(); // 广播初始值（也就是将健康值与法术值的初始值广播给相应的小部件）
	virtual void BindCallbacksToDependencies(); // 用于多播委托（非动态多播）的绑定函数，主要用于绑定回调函数。声明在基类上，这样所有小部件控制器都可以实现该功能
	
protected:
	// 需要以下这些变量，通过它们来获取到相应的信息内容
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	
};
