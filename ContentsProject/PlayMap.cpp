#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


APlayMap::APlayMap()
{
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND1);
	SpriteRenderer->SetSprite("01_Background");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());

	SpriteRenderer->CreateAnimation("Stage1_BG", "01_Background", 0, 22, 0.1f);
	SpriteRenderer->ChangeAnimation("Stage1_BG");
}

APlayMap::~APlayMap()
{
}

