#include "PreCompile.h"
#include "TestMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


ATestMap::ATestMap()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND1);
	SpriteRenderer->SetSprite("EX_BG");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());

	SpriteRenderer->CreateAnimation("Stage1_EX_BG", "EX_BG", 0, 0, 1.0f, false);
	SpriteRenderer->CreateAnimation("Boss_EX_BG", "EX_BG", 1, 1, 1.0f, false);

};

ATestMap::~ATestMap()
{

};