#include "PreCompile.h"
#include "Tile_Destroy.h"

#include <EngineCore/SpriteRenderer.h>

#include "ATileMap.h"

ATile_Destroy::ATile_Destroy()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Destroy_Anim");
	SpriteRenderer->SetComponentScale({ 32, 32 });
	SpriteRenderer->CreateAnimation("Destroy_Wall", "Destroy_Anim", 0, 10, 0.1f, false);
	SpriteRenderer->ChangeAnimation("Destroy_Wall");

	SpriteRenderer->SetOrder(10000);
};

ATile_Destroy::~ATile_Destroy()
{
	ClearObjectTile();
};

void ATile_Destroy::SetWallTileMap(ATileMap* _TileMap, FIntPoint _Index)
{
	WallTileMap = _TileMap;
	ObjectTileIndex = _Index;
}

void ATile_Destroy::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Object_Destroy();
}

void ATile_Destroy::Object_Destroy()
{
	if (nullptr != SpriteRenderer)
	{
		if (true == SpriteRenderer->IsCurAnimationEnd())
		{
			// 오브젝트 제거
			Destroy();
		}
	}
}

void ATile_Destroy::ClearObjectTile()
{
	if (WallTileMap != nullptr)
	{
		WallTileMap->SetBomb(ObjectTileIndex, nullptr); // 오브젝트 포인터를 nullptr로 설정
	}
}
