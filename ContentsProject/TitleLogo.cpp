#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


UTitleLogo::UTitleLogo()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND1);
		SpriteRenderer->SetSprite("00_Neo-Geo_LOGO");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());

		SpriteRenderer->CreateAnimation("Neo-Geo_Logo", "00_Neo-Geo_LOGO", 0, 88, 0.035f, false);
		SpriteRenderer->ChangeAnimation("Neo-Geo_Logo");


	}
	//{
	//	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND0);
	//	SpriteRenderer->SetSprite("01_WARNING");

	//	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	//	SpriteRenderer->SetComponentLocation(MapScale.Half());

	//}



}

UTitleLogo::~UTitleLogo()
{
}

