#include "PreCompile.h"
#include "Fade.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

AFade* AFade::MainFade = nullptr;

AFade::AFade()
{
	BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackSpriteRenderer->SetOrder(ERenderOrder::FADE);
	BackSpriteRenderer->SetSprite("Fade.bmp");
	FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
	BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	BackSpriteRenderer->SetCameraEffect(false);
	// BackSpriteRenderer->SetAlphaChar(200);
}

AFade::~AFade()
{
}

void AFade::FadeChange()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * FadeSpeed * FadeDir;

	if (true == IsFadeOut && true == IsHalfFade)
	{
		if (FadeValue > FadeOutLimite)
		{
			FadeValue = FadeOutLimite;
		}
	}
	if (true == IsFadeIn && true == IsHalfFade)
	{
		if (FadeValue > FadeInLimite)
		{
			FadeValue = FadeInLimite;
		}
	}

	BackSpriteRenderer->SetAlphafloat(FadeValue);
}

void AFade::FadeIn()
{
	FadeValue = 0.0f;
	FadeDir = 1.0f;
	IsFadeOut = false;
	IsFadeIn = true;
	TimeEventer.PushEvent(2.0f, std::bind(&AFade::FadeChange, this), true, false);
}

void AFade::FadeInHalf()
{
	FadeValue = FadeInLimite;
	FadeDir = 1.0f;
	IsFadeOut = false;
	IsFadeIn = true;
	TimeEventer.PushEvent(2.0f, std::bind(&AFade::FadeChange, this), true, false);
}

void AFade::FadeOut()
{
	FadeValue = 1.0f;
	FadeDir = -1.0f;
	IsFadeOut = true;
	IsFadeIn = false;
	TimeEventer.PushEvent(2.0f, std::bind(&AFade::FadeChange, this), true, false);
}

void AFade::LevelChangeStart()
{
	// BeginPlay나 생성자에서 했는데.
	// 이제부터 내가 mainFade야 라고 설정하게 됩니다.
	MainFade = this;
}