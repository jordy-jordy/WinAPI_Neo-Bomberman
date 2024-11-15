#include "PreCompile.h"
#include "Mushroom.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineBase/EngineRandom.h>

#include "ATileMap.h"


AMushroom::AMushroom()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 38, 42 });
	FVector2D Scale = SpriteRenderer->GetComponentScale();
	SpriteRenderer->SetPivot({ 0, -8 });

	SpriteRenderer->CreateAnimation("Mushroom_Idle", "01_Mushroom_00_Idle", 0, 1, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Left", "01_Mushroom_01_Left", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Right", "01_Mushroom_02_Right", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Up", "01_Mushroom_03_Up", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Down", "01_Mushroom_04_Down", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Uniq", "01_Mushroom_05_Uniq", 0, 10, 0.2f, true);

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

	Mush_Order();
	Mush_Move(_DeltaTime);
}

void AMushroom::Mush_Order()
{
	SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
}



FVector2D AMushroom::InvertLOC(FVector2D _Loc)
{
	if (_Loc == FVector2D::ZERO)
	{
		return {0, 0};
	}

	if (_Loc == FVector2D::LEFT)
	{
		return {-17, 0};
	}

	if (_Loc == FVector2D::RIGHT)
	{
		return {17, 0};
	}

	if (_Loc == FVector2D::UP)
	{
		return {0, -17};
	}

	if (_Loc == FVector2D::DOWN)
	{
		return {0, 17};
	}
}

bool AMushroom::ISMOVE(FVector2D _NEXTPOS, Tile* _NEXTTILE)
{
	if (_NEXTPOS.X > TILE_INDEX_MIN_X &&
		_NEXTPOS.X < TILE_INDEX_MAX_X &&
		_NEXTPOS.Y > TILE_INDEX_MIN_Y &&
		_NEXTPOS.Y < TILE_INDEX_MAX_Y &&
		_NEXTTILE->SpriteIndex != 1 &&
		_NEXTTILE->SpriteIndex != 2 &&
		_NEXTTILE->SpriteIndex != 3)
	{
		return true;
	}
	return false;
}


void AMushroom::Mush_Move(float _DeltaTime)
{
	FVector2D Location = GetActorLocation();
	FVector2D WallTileMapLocation = WallTileMap->GetActorLocation();
	FVector2D LocalLocation = Location - WallTileMapLocation;

	FVector2D TileSize = WallTileMap->GetTileSize();
	FVector2D Location_Target = LocalLocation + InvertLOC(MoveTO);
	FVector2D Index_Target = Location_Target / TileSize;

	Tile* GetTileNext = WallTileMap->GetTileRef(Location_Target);

	// 현재 방향으로 이동 가능한 경우
	if (ISMOVE(Index_Target, GetTileNext))
	{
		AddActorLocation(MoveTO * _DeltaTime * Speed);
		return;
	}

	// 이동 불가능한 경우, 랜덤하게 새로운 방향 선택
	FVector2D PossibleDirections[4] = { FVector2D::LEFT, FVector2D::RIGHT, FVector2D::UP, FVector2D::DOWN };
	UEngineRandom Random;
	int RandomIndex = Random.RandomInt(0, 3);

	// 이동 가능한 방향을 찾을 때까지 반복
	for (int i = 0; i < 4; i++)
	{
		MoveTO = PossibleDirections[RandomIndex];
		FVector2D NewTarget = LocalLocation + InvertLOC(MoveTO);
		FVector2D NewIndex = NewTarget / TileSize;
		Tile* NewTile = WallTileMap->GetTileRef(NewTarget);

		if (ISMOVE(NewIndex, NewTile))
		{
			return;
		}

		// 다음 랜덤 방향으로 전환
		RandomIndex = (RandomIndex + 1) % 4;
	}
}



//void AMushroom::Mush_Move(float _DeltaTime)
//{
//	FVector2D Location = GetActorLocation();
//	FVector2D WallTileMapLocation = WallTileMap->GetActorLocation();
//	FVector2D LocalLocation = Location - WallTileMapLocation;
//
//	FVector2D TileSize = WallTileMap->GetTileSize();
//	FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
//
//	FVector2D Location_Target = LocalLocation + InvertLOC(MoveTO);
//	FVector2D Index_Target = Location_Target / TileSize;
//
//	FVector2D LOC_UP = (LocalLocation + UP) / TileSize;
//	FVector2D LOC_DOWN = (LocalLocation + DOWN) / TileSize;
//	FVector2D LOC_LEFT = (LocalLocation + LEFT) / TileSize;
//	FVector2D LOC_RIGHT = (LocalLocation + RIGHT) / TileSize;
//
//	Tile* GetTileNext = WallTileMap->GetTileRef(Location_Target);
//	Tile* GET_TILE_UP = WallTileMap->GetTileRef(LOC_UP);
//	Tile* GET_TILE_DOWN = WallTileMap->GetTileRef(LOC_DOWN);
//	Tile* GET_TILE_LEFT = WallTileMap->GetTileRef(LOC_LEFT);
//	Tile* GET_TILE_RIGHT = WallTileMap->GetTileRef(LOC_RIGHT);
//	UEngineDebug::CoreOutPutString("Location_Target : " + Location_Target.ToString());
//	UEngineDebug::CoreOutPutString("Index_Target : " + Index_Target.ToString());
//
//	if (true == ISMOVE(Index_Target, GetTileNext))
//	{
//		AddActorLocation(MoveTO * _DeltaTime * Speed);
//		return;
//	}
//
//	if (MoveTO == FVector2D::LEFT)
//	{
//		if (true == ISMOVE(LOC_UP, GET_TILE_UP))
//		{
//			MoveTO = FVector2D::UP;
//			return;
//		}
//		if (true == ISMOVE(LOC_DOWN, GET_TILE_DOWN))
//		{
//			MoveTO = FVector2D::DOWN;
//			return;
//		}
//		if (true == ISMOVE(LOC_RIGHT, GET_TILE_RIGHT))
//		{
//			MoveTO = FVector2D::RIGHT;
//			return;
//		}
//	}
//	else if (MoveTO == FVector2D::RIGHT)
//	{
//		if (true == ISMOVE(LOC_UP, GET_TILE_UP))
//		{
//			MoveTO = FVector2D::UP;
//			return;
//		}
//		if (true == ISMOVE(LOC_DOWN, GET_TILE_DOWN))
//		{
//			MoveTO = FVector2D::DOWN;
//			return;
//		}
//		if (true == ISMOVE(LOC_LEFT, GET_TILE_LEFT))
//		{
//			MoveTO = FVector2D::LEFT;
//			return;
//		}
//	}
//	else if (MoveTO == FVector2D::UP)
//	{
//		if (true == ISMOVE(LOC_RIGHT, GET_TILE_RIGHT))
//		{
//			MoveTO = FVector2D::RIGHT;
//			return;
//		}
//		if (true == ISMOVE(LOC_DOWN, GET_TILE_DOWN))
//		{
//			MoveTO = FVector2D::DOWN;
//			return;
//		}
//		if (true == ISMOVE(LOC_LEFT, GET_TILE_LEFT))
//		{
//			MoveTO = FVector2D::LEFT;
//			return;
//		}
//	}
//	else if (MoveTO == FVector2D::DOWN)
//	{
//		if (true == ISMOVE(LOC_LEFT, GET_TILE_LEFT))
//		{
//			MoveTO = FVector2D::LEFT;
//			return;
//		}
//		if (true == ISMOVE(LOC_RIGHT, GET_TILE_RIGHT))
//		{
//			MoveTO = FVector2D::RIGHT;
//			return;
//		}
//		if (true == ISMOVE(LOC_UP, GET_TILE_UP))
//		{
//			MoveTO = FVector2D::UP;
//			return;
//		}
//	}
//
//}
