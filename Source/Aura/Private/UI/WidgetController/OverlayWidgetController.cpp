// Copyright CREATOR-JIA


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// 因小部件控制器中有AttributeSet变量，因此可对该变量内的属性进行设置
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth()); // 这将获取到健康值,并进行初始设置
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth()); // 这将获取到最大健康值,并进行初始设置
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana()); // 这将获取到法术值,并进行初始设置
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana()); // 这将获取到最大法术值,并进行初始设置
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// 在这里进行回调函数的绑定
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	/**
	 * GetGameplayAttributeValueChangeDelegate()方法返回一个多播委拖，通过调用委托的AddUObject方法给属性添加回调函数。为什么没用AddDynamic?
	 * 因为该委托的原型是：DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayAttributeValueChange, const FOnAttributeChangeData&);
	 * 原型中声明的委托并不是DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam，没有 “_DYNAMIC”字样
	 */
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this,&UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&UOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this,&UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::MaxManaChanged);
	
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	// 当健康值发生变化时，需要广播给健康值小部件，让其正确的做出响应
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	// 当健康值发生变化时，需要广播给健康值小部件，让其正确的做出响应
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	// 当法术值发生变化时，需要广播给法术值小部件，让其正确的做出响应
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	// 当法术值发生变化时，需要广播给法术值小部件，让其正确的做出响应
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
