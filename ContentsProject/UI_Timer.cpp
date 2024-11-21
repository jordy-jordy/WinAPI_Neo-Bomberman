#include "PreCompile.h"
#include "UI_Timer.h"

#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"

AUI_Timer::AUI_Timer()
{
	PLAYMODE_BAR = CreateDefaultSubObject<USpriteRenderer>();
	PLAYMODE_BAR->SetSprite("ScoreBar_Adventure.png");
	PLAYMODE_BAR->SetComponentScale({ 608, 44 });
	PLAYMODE_BAR->SetPivotType(PivotType::Top);
	PLAYMODE_BAR->SetOrder(ERenderOrder::UI);

};

AUI_Timer::~AUI_Timer()
{

};

void AUI_Timer::BeginPlay()
{
	Super::BeginPlay();
}

void AUI_Timer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}