#include "PreCompile.h"
#include "ChooseStage.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


UChooseStage::UChooseStage()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND1);
		SpriteRenderer->SetSprite("00_00_BASIC");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());

		SpriteRenderer->CreateAnimation("Choose_Stage", "05_CHOOSE_STAGE", 8, 8, 0.035f, false);
		SpriteRenderer->ChangeAnimation("Choose_Stage");
	}

};

UChooseStage::~UChooseStage()
{

};