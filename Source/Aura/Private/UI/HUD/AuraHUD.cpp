// Copyright CREATOR-JIA


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		// 创建新小部件控制器（对于新对象，需传入的参数是：第一个是this,第二个是构造小部件控制器的UClass）
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams); // 设置小部件控制器的参数
		OverlayWidgetController->BindCallbacksToDependencies(); // Overlay小部件控制器绑定属性变化的回调函数
		
		return OverlayWidgetController; // 返回小部件控制器
	}
	
	return OverlayWidgetController;
}

void AAuraHUD::InitOverly(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
{
	// 断言Overlay小部件的UClass，如果该小闻件为空，那么输出下行文本,要去BP_AuraHUD进行选取
	checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	// 构造小部件：HUD类开始时，将小部件添加到视口中(参数一是拥有此HUD的对象，我们实际上是将HUD传递给世界，因此是GetWorld()。参数二是要添加到视口中的小部件，我们添加小部件类)
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget); // 将构造的Widget映射成AuraUserWidget，这样就可以设置它的小部件控制器
	// 构造小部件控制器
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS); // 初始化小部件控制器结构体对象
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams); // 构建小部件控制器
	
	OverlayWidget->SetWidgetController(WidgetController); // 将小部件控制器设置给Overlay小部件，将它们联系起来
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
	
}

