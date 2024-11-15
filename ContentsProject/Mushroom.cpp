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

bool AMushroom::CheckCantMove(FVector2D _Pos)
{
	if (true == WallTileMap->IsIndexOverFVector(_Pos))
	{
		return true;
	}

	return false;
}

int AMushroom::CheckNextPos(FVector2D _CurPos)
{
	FVector2D NextPos_UP = _CurPos + UP;
	FVector2D NextPos_DOWN = _CurPos + DOWN;
	FVector2D NextPos_LEFT = _CurPos + LEFT;
	FVector2D NextPos_RIGHT = _CurPos + RIGHT;

	Tile* GetTile_UP = WallTileMap->GetTileRef(NextPos_UP);
	Tile* GetTile_DOWN = WallTileMap->GetTileRef(NextPos_DOWN);
	Tile* GetTile_LEFT = WallTileMap->GetTileRef(NextPos_LEFT);
	Tile* GetTile_RIGHT = WallTileMap->GetTileRef(NextPos_RIGHT);

	if (true != CheckCantMove(NextPos_UP))
	{
		if (GetTile_UP->SpriteIndex != 1 && GetTile_UP->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::UP);
		}
	}

	if (true != CheckCantMove(NextPos_DOWN))
	{
		if (GetTile_DOWN->SpriteIndex != 1 && GetTile_DOWN->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::DOWN);
		}
	}

	if (true != CheckCantMove(NextPos_LEFT))
	{
		if (GetTile_LEFT->SpriteIndex != 1 && GetTile_LEFT->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::LEFT);
		}
	}

	if (true != CheckCantMove(NextPos_RIGHT))
	{
		if (GetTile_RIGHT->SpriteIndex != 1 && GetTile_RIGHT->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::RIGHT);
		}
	}

	return MoveDir.size();
}

void AMushroom::Mush_Move(float _DeltaTime)
{
	FVector2D Location = GetActorLocation();
	FVector2D WallTileMapLocation = WallTileMap->GetActorLocation();
	FVector2D TileSize = WallTileMap->GetTileSize();
	FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();

	//FVector2D LocalLocation = Location - WallTileMapLocation;
	FVector2D LocalLocation = Location - WallTileMapLocation - TileHalfSize;

	FVector2D Location_Target = LocalLocation + MoveTO;
	FVector2D Index_Target = Location_Target / TileSize;

	UEngineDebug::CoreOutPutString("Location_Target : " + Location_Target.ToString());
	UEngineDebug::CoreOutPutString("Index_Target : " + Index_Target.ToString());

	Tile* GetTileNext = WallTileMap->GetTileRef(Location_Target);



	int a = 0;

	if (true != CheckCantMove(Location_Target) && GetTileNext->SpriteIndex != 1 && GetTileNext->SpriteIndex != 2)
	{
		AddActorLocation(MoveTO * _DeltaTime * Speed);
		return;
	}
	else if (true == CheckCantMove(Location_Target) || GetTileNext->SpriteIndex == 1 || GetTileNext->SpriteIndex == 2)
	{
		CheckNextPos(LocalLocation);
		UEngineRandom StartRandom;
		FVector2D Pos = MoveDir[StartRandom.RandomInt(0, static_cast<int>(MoveDir.size()) - 1)];
		MoveTO = Pos;
		return;
	}


	//if (GetTileNext->SpriteIndex != 1 && GetTileNext->SpriteIndex != 2)
	//{
	//	AddActorLocation(MoveTO * _DeltaTime * Speed);
	//	return;
	//}
	//else if (GetTileNext->SpriteIndex == 1 || GetTileNext->SpriteIndex == 2)
	//{
	//	CheckNextPos(LocalLocation);
	//	UEngineRandom StartRandom;
	//	FVector2D Pos = MoveDir[StartRandom.RandomInt(0, static_cast<int>(MoveDir.size()) - 1)];
	//	MoveTO = Pos;
	//	AddActorLocation(MoveTO * _DeltaTime * Speed);
	//	return;
	//}



}
