#include "PreCompile.h"
#include "UI_Timer.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineTimer.h>

#include "ContentsEnum.h"
#include "Score.h"


AUI_Timer::AUI_Timer()
{
	TOPBAR = CreateDefaultSubObject<USpriteRenderer>();
	TOPBAR->SetSprite("ScoreBar_Adventure.png");
	TOPBAR->SetComponentScale({ 608, 44 });
	TOPBAR->SetComponentLocation({ 304, 0 });
	TOPBAR->SetPivotType(PivotType::Top);
	TOPBAR->SetOrder(ERenderOrder::UI);

	COLON = CreateDefaultSubObject<USpriteRenderer>();
	COLON->SetSprite("TimeCount.png", 10);
	COLON->SetComponentScale({ 16, 12 });
	COLON->SetComponentLocation({ 298, 18 });
	COLON->SetPivotType(PivotType::Top);
	COLON->SetOrder(ERenderOrder::UI);

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

