// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
// 声明几个动态多播委托：因为我们只是对键康值或法术值进行广播，这只是针对于单个变量，因此这里我们使用一个参数的动态多播委托
// 参数第一个是委拖类型、第二个是被广播的变量的类型、第三个是被广播的变量的名称
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,NewHealth); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana); 

/**
 * Overlay小部件控制器（该小部件控制器将在HUD中进行构建，也就是在HUD中创建该Overlay小部件控制器及Overlay小部件）
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override; // 广播初始值函数，什么时候调用该函数？在AuraHUD.cpp中将小部件与小部件控制器关联起来之后就可以调用该函数
	/**
	 * 绑定回调函数的方法，该函数主要处理委托绑定回调函数的内容。在哪里调用该函数？在AuraHUD类中，当小部件控制器参数成功设置完成之后就开始调用该绑定函数
	 * 在该绑定函数中发生了属性的更改，并调用了属性对应的回调函数。回调函数中进行属性值的广播，相应的小部件做出响应
	 */
	virtual void BindCallbacksToDependencies() override; 

	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged; // 创建委托
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged; // 创建委托
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged; // 创建委托
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged; // 创建委托

protected:
	/**
	 * 角色健康值发生变化后的回调函数,当属性发生变化时，可使用UAbilitySystemComponent::GetGameplayAttributeValueChangeDelegate(FGameplayAttribute Attribute)方法
	 * 该方法将返回一个委托，可以自由的绑定回调函数。当对应的Attribute发生变化时就会自动执行这个回调函数。委托提供了FOnAttributeChangeData参数参数。
	 * 该回调函数的参数签名要与委托提供的参数一致*/
	void HealthChanged(const FOnAttributeChangeData& Data) const; // 当健康值发生变化时的回调函数
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const; // 当最大健康值发生充化时的回调函数
	void ManaChanged(const FOnAttributeChangeData& Data)const; // 当法术值发生变化时的回调函数
	void MaxManaChanged(const FOnAttributeChangeData& Data)const; // 当最大法术值发生充化时的回调函数 
};
