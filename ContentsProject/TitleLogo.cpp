#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ContentsEnum.h"

UTitleLogo::UTitleLogo()
{
	{
		BASE00 = CreateDefaultSubObject<USpriteRenderer>();
		BASE00->SetSprite("TITLE_000.png");
		BASE00->SetOrder(ERenderOrder::BACKGROUND1);
		BASE00->SetPivotType(PivotType::Top);
		BASE00->SetComponentScale({48, 448});
		BASE00->SetComponentLocation({24, 0});
		BASE00->SetActive(false);

		BASE01 = CreateDefaultSubObject<USpriteRenderer>();
		BASE01->SetSprite("TITLE_000.png");
		BASE01->SetOrder(ERenderOrder::BACKGROUND1);
		BASE01->SetPivotType(PivotType::Top);
		BASE01->SetComponentScale({ 48, 448 });
		BASE01->SetComponentLocation({ 584, 0 });
		BASE01->SetActive(false);

		MAINRENDERER = CreateDefaultSubObject<USpriteRenderer>();
		MAINRENDERER->SetSprite("BASIC_000.png");
		MAINRENDERER->SetOrder(ERenderOrder::BACKGROUND0);
		FVector2D MapScale = MAINRENDERER->SetSpriteScale(1.0f);
		MAINRENDERER->SetComponentLocation(MapScale.Half());
		MAINRENDERER->CreateAnimation("Neo-Geo_Logo", "00_Neo-Geo_LOGO", 0, 275, 0.015f, false);
		MAINRENDERER->CreateAnimation("OP_Animation", "03_OP_ANIMATION", 0, 890, 0.018f, false);
		MAINRENDERER->ChangeAnimation("Neo-Geo_Logo");

		COIN_INSERT = CreateDefaultSubObject<USpriteRenderer>();
		COIN_INSERT->SetSprite("TITLE_04_COIN_INSERT_000.png");
		COIN_INSERT->SetOrder(ERenderOrder::BACKGROUND0);
		COIN_INSERT->SetComponentScale({ 262, 28 });
		COIN_INSERT->SetComponentLocation(MapScale.Half());
		COIN_INSERT->CreateAnimation("COIN_INSERT", "04_COIN_INSERT", 0, 0, 1, false);
		COIN_INSERT->ChangeAnimation("COIN_INSERT");
		COIN_INSERT->SetActive(false);

	}
}

UTitleLogo::~UTitleLogo()
{
}

void UTitleLogo::BeginPlay()
{
	Super::BeginPlay();
}

void UTitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress('F'))
	{
		BASE00->SetActive(true);
		BASE01->SetActive(true);
		COIN_INSERT->SetActive(true);
		MAINRENDERER->ChangeAnimation("OP_Animation");
	}

	if (MAINRENDERER->GetCurSpriteName() == "00_NEO-GEO_LOGO" && CurAniEND() == true)
	{
		Delay += _DeltaTime;
		if (Delay >= 3.0f)
		{
			BASE00->SetActive(true);
			BASE01->SetActive(true);
			COIN_INSERT->SetActive(true);
			MAINRENDERER->ChangeAnimation("OP_Animation");
			Delay = 0.0f;
		}
	}
}

bool UTitleLogo::CurAniEND()
{
	if (MAINRENDERER->IsCurAnimationEnd() == true)
	{
		return true;
	}
	return false;
}

