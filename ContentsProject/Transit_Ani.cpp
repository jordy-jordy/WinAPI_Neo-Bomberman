#include "PreCompile.h"
#include "Transit_Ani.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"


ATransit_Ani::ATransit_Ani()
{
	MAINRENDERER = CreateDefaultSubObject<USpriteRenderer>();
	MAINRENDERER->SetSprite("06_TRASIT_ANIMATION");
	MAINRENDERER->SetOrder(ERenderOrder::BACKGROUND0);
	FVector2D MapScale = MAINRENDERER->SetSpriteScale(1.0f);
	MAINRENDERER->SetComponentLocation(MapScale.Half());
	MAINRENDERER->CreateAnimation("Transit_Ani", "06_TRASIT_ANIMATION", 0, 218, 0.015f, false);
	MAINRENDERER->ChangeAnimation("Transit_Ani");
};

ATransit_Ani::~ATransit_Ani()
{

};

void ATransit_Ani::BeginPlay()
{
	Super::BeginPlay();
}

void ATransit_Ani::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
