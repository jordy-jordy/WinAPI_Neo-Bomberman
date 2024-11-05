#include "PreCompile.h"
#include "Bomb.h"

#include <EngineCore/SpriteRenderer.h>

ABomb::ABomb()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("01_Bomb");
	SpriteRenderer->SetComponentScale({ 32, 32 });

	SpriteRenderer->CreateAnimation("Bomb", "01_Bomb", { 0, 1, 2, 1 }, { 0.2f, 0.2f ,0.2f ,0.2f });

}

ABomb::~ABomb()
{
}

void ABomb::Tick(float _DeltaTime)
{
}