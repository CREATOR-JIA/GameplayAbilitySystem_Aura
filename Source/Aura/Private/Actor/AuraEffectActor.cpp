// Copyright CREATOR-JIA


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/**
	 *与其他Actor发生重叠碰撞时，我们需要知道与我们发生重叠的这个Actor是否具有技能组件系统，只要这个Acotr继承过AbilitySystemInterface这个接口，那么可以通过
	 *该接口类中的GetAbilitySystemComponent（）方法来获取到此Acotr的技能系统组件
	 *我们可以将与我们发生重叠的这个Acotr，也就是OtherActor投射成IAbilitySystemInterface接口，如果投射成功，那么就可以获取到此Acotr的技能系统组件
	*/
	// TODO: Change this to apply a Gameplay Effect. For now,using const_cast a hack! 
	if(const IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		// 因为我们要与Aura角色发生碰撞重叠，那么当Aura的技能系统接口有效时，我们就可以通过该接口获取到Aura的属性集，而Aura的属性集中有Health属性，因此我们可以改变Health的值
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		// 由于AuraAttributeSet标记为const，因此属性集中的SetHealth设置健康值是不能用的。所以我们使用const_cast来对常量进行修改
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth()+25.f);
		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana()-25.f);
		Destroy();
	}
	
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	// 进行碰撞体的函数绑定,某物与Sphere发生重叠时会调用绑定的重叠函数OnOverlap,结束重叠时会调用EndOverlap
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::EndOverlap);
}
