#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>


#include "ContentsEnum.h"
#include "Score.h"


UTitleLogo::UTitleLogo()
{
	BASE00 = CreateDefaultSubObject<USpriteRenderer>();
	BASE00->SetSprite("TITLE_000.png");
	BASE00->SetOrder(ERenderOrder::BACKGROUND1);
	BASE00->SetPivotType(PivotType::Top);
	BASE00->SetComponentScale({ 48, 448 });
	BASE00->SetComponentLocation({ 24, 0 });
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
	MAINRENDERER->CreateAnimation("OP_Animation", "03_OP_ANIMATION", 0, 890, 0.015f, false);
	MAINRENDERER->ChangeAnimation("Neo-Geo_Logo");


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
