#include "PreCompile.h"
#include "Portal.h"

#include <EngineCore/SpriteRenderer.h>

APortal::APortal()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 32, 32 });
	SpriteRenderer->SetPivot({ 0, 0 });

	SpriteRenderer->CreateAnimation("Portal_OFF", "03_Portal", 0, 1, 0.2f, true);
	SpriteRenderer->CreateAnimation("Portal_ON", "03_Portal", 2, 8, 0.2f, true);

	SpriteRenderer->ChangeAnimation("Portal_OFF");
};

APortal::~APortal()
{

};