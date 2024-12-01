#include "PreCompile.h"
#include "Ending.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"


AEnding::AEnding()
{
	BACKGROUND = CreateDefaultSubObject<USpriteRenderer>();
	BACKGROUND->SetSprite("BG_000.png");
	BACKGROUND->SetOrder(ERenderOrder::BACKGROUND1);
	BACKGROUND->SetPivotType(PivotType::Top);
	BACKGROUND->SetSpriteScale(1.0f);
	BACKGROUND->SetComponentLocation({ 113, 0 });

	GIRL = CreateDefaultSubObject<USpriteRenderer>();
	GIRL->SetSprite("girl_000.png");
	GIRL->SetOrder(ERenderOrder::BACKGROUND3);
	GIRL->SetPivotType(PivotType::Top);
	GIRL->SetSpriteScale(1.0f);
	GIRL->SetComponentLocation({ 91, 254 });
	GIRL->CreateAnimation("GIRL_MOVING", "02_Ending", 4, 7, 0.25f, true);
	GIRL->ChangeAnimation("GIRL_MOVING");

	BOYS = CreateDefaultSubObject<USpriteRenderer>();
	BOYS->SetSprite("boy_000.png");
	BOYS->SetOrder(ERenderOrder::BACKGROUND3);
	BOYS->SetPivotType(PivotType::Top);
	BOYS->SetSpriteScale(1.0f);
	BOYS->SetComponentLocation({ 163, 276 });
	BOYS->CreateAnimation("BOYS_MOVING", "02_Ending", 1, 3, 0.25f, true);
	BOYS->ChangeAnimation("BOYS_MOVING");

	THANKS = CreateDefaultSubObject<USpriteRenderer>();
	THANKS->SetSprite("myname.png");
	THANKS->SetOrder(ERenderOrder::BACKGROUND3);
	THANKS->SetPivotType(PivotType::Top);
	THANKS->SetSpriteScale(1.0f);
	THANKS->SetComponentLocation({ 426, 189 });

	BACK = CreateDefaultSubObject<USpriteRenderer>();
	BACK->SetSprite("BackBlack.png");
	BACK->SetOrder(ERenderOrder::BACKGROUND0);
	BACK->SetPivotType(PivotType::Top);
	BACK->SetSpriteScale(1.0f);
	BACK->SetComponentLocation({ 304, 0 });
};

AEnding::~AEnding()
{

};

void AEnding::BeginPlay()
{
	Super::BeginPlay();
}

void AEnding::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
