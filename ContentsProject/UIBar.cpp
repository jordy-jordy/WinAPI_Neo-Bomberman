#include "PreCompile.h"
#include "UIBar.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineTimer.h>

#include "ContentsEnum.h"
#include "Score.h"


AUIBar::AUIBar()
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

	PUSHSTART = CreateDefaultSubObject<USpriteRenderer>();
	PUSHSTART->SetSprite("PushStart_Anim");
	PUSHSTART->CreateAnimation("StartPlz", "PushStart_Anim", 0, 1, 0.2f, true);
	PUSHSTART->ChangeAnimation("StartPlz");
	PUSHSTART->SetComponentScale({ 158, 14 });
	PUSHSTART->SetComponentLocation({ 475, 15 });
	PUSHSTART->SetPivotType(PivotType::Top);
	PUSHSTART->SetOrder(ERenderOrder::UI);

};

AUIBar::~AUIBar()
{

};

void AUIBar::BeginPlay()
{
	Super::BeginPlay();

}

void AUIBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

