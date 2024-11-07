#include "PreCompile.h"
#include "Bomb.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ATileMap.h"


ABomb::ABomb()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("01_Bomb");
	SpriteRenderer->SetComponentScale({ 32, 32 });

	SpriteRenderer->CreateAnimation("Bomb", "01_Bomb", { 0, 1, 2, 1 }, { 0.2f, 0.2f ,0.2f ,0.2f });
	SpriteRenderer->ChangeAnimation("Bomb");

}

ABomb::~ABomb()
{
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		FVector2D PlayerPos = GetWorld()->GetPawn()->GetActorLocation();
		SpriteRenderer->SetComponentLocation(PlayerPos);
		SpriteRenderer->Destroy(2.0f);
		SpriteRenderer = nullptr;
	}



	//SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);

	//if (nullptr == WallTileMap)
	//{
	//	MSGASSERT("타일 맵이 세팅되지 않았습니다.")
	//}


}