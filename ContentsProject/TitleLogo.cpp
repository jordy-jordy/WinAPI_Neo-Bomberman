#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ContentsEnum.h"
#include "Score.h"


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

		LEVEL4 = CreateDefaultSubObject<USpriteRenderer>();
		LEVEL4->SetSprite("Level-4_112x16.png");
		LEVEL4->SetOrder(ERenderOrder::BACKGROUND1);
		LEVEL4->SetSpriteScale(1.0f);
		LEVEL4->SetPivotType(PivotType::Top);
		LEVEL4->SetComponentLocation({ 312, 432 });
		LEVEL4->SetActive(false);

		CREDIT = CreateDefaultSubObject<USpriteRenderer>();
		CREDIT->SetSprite("Credits_112x16.png");
		CREDIT->SetOrder(ERenderOrder::BACKGROUND1);
		CREDIT->SetSpriteScale(1.0f);
		CREDIT->SetPivotType(PivotType::Top);
		CREDIT->SetComponentLocation({ 488, 432 });
		CREDIT->SetActive(false);
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

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		if (MAINRENDERER->GetCurSpriteName() == "00_NEO-GEO_LOGO")
		{
			MAINRENDERER->ChangeAnimation("OP_Animation");
			BASE00->SetActive(true);
			BASE01->SetActive(true);
			LEVEL4->SetActive(true);
			CREDIT->SetActive(true);
		}
	}

	if (MAINRENDERER->GetCurSpriteName() == "00_NEO-GEO_LOGO" && CurAniEND() == true)
	{
		Delay += _DeltaTime;
		if (Delay >= Wait)
		{
			MAINRENDERER->ChangeAnimation("OP_Animation");
			BASE00->SetActive(true);
			BASE01->SetActive(true);
			LEVEL4->SetActive(true);
			CREDIT->SetActive(true);
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

void UTitleLogo::DestroyTitleLogo()
{
	Destroy();
}
