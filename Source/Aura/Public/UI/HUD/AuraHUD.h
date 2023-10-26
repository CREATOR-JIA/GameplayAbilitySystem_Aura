// Copyright CREATOR-JIA

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 该类主要用于将小部件添加到游戏主UI界面上，并进行显示
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget; // 这个堆叠小部件指针，我们需要将其添加到界面上

	// 获取小部件控制器,传入的参数是结构体对象，为什么要传入一个结构体？因为该结构体中有四个关键变量，传入关键变量后可进行变量设置
	UFUNCTION()
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams); 

	// 初始化Overlay小部件及Overlay小部件控制器，用于构建Overlay小部件及Overlay小部件控制器
	// 思考：在哪里调用InitOverly（）函数，以及在何时何地才能知道那四个关键变量都已被初始化？ 我们可以在AuraCharacter.cpp中的InitAbilityActorInfo()函数中调用此函数。
	void InitOverly(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS); 
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass; // 通过TSubclassOf，可以接受UAuraUserWidget类的子类(可以在蓝图编辑器中直接指定)

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController; // 用来保存小部件控制器

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass; // OverlayWidgetController的UClass
};
