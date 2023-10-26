// Copyright CREATOR-JIA


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController; // 将结构体WCParams中的PlayerController赋给Aura小部件控制器中的变量PlayerController
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues(){} // 由子类去实现

void UAuraWidgetController::BindCallbacksToDependencies(){} // 由子类去实现
