#include "PreCompile.h"
#include "Mushroom.h"

#include <EngineCore/SpriteRenderer.h>

#include "ATileMap.h"


AMushroom::AMushroom()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 38, 42 });

	SpriteRenderer->CreateAnimation("Mushroom_Idle", "01_Mushroom_00_Idle",   0, 1,  0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Left", "01_Mushroom_01_Left",   0, 5,  0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Right", "01_Mushroom_02_Right", 0, 5,  0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Up", "01_Mushroom_03_Up",       0, 5,  0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Down", "01_Mushroom_04_Down",   0, 5,  0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Uniq", "01_Mushroom_05_Uniq",   0, 10, 0.2f, true);

	SpriteRenderer->ChangeAnimation("Mushroom_Idle");

};

AMushroom::~AMushroom()
{

};

void AMushroom::BeginPlay()
{
	Super::BeginPlay();
}
void AMushroom::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
}
