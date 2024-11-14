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
	bool Check = WallTileMap->IsIndexOverFVector(_Pos);
	return Check;
}

int AMushroom::CheckNextPos(FVector2D _CurPos)
{
	Tile* GetTile_UP = WallTileMap->GetTileRef(_CurPos + UP);
	Tile* GetTile_DOWN = WallTileMap->GetTileRef(_CurPos + DOWN);
	Tile* GetTile_LEFT = WallTileMap->GetTileRef(_CurPos + LEFT);
	Tile* GetTile_RIGHT = WallTileMap->GetTileRef(_CurPos + RIGHT);

	if (GetTile_UP != nullptr)
	{
		if (GetTile_UP->SpriteIndex != 1 && GetTile_UP->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::UP);
		}
	}
	if (GetTile_DOWN != nullptr)
	{
		if (GetTile_DOWN->SpriteIndex != 1 && GetTile_DOWN->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::DOWN);
		}
	}
	if (GetTile_LEFT != nullptr)
	{
		if (GetTile_LEFT->SpriteIndex != 1 && GetTile_LEFT->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::LEFT);
		}
	}
	if (GetTile_RIGHT != nullptr)
	{
		if (GetTile_RIGHT->SpriteIndex != 1 && GetTile_RIGHT->SpriteIndex != 2)
		{
			MoveDir.push_back(FVector2D::RIGHT);
		}
	}

	int Size = MoveDir.size();

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

	CheckNextPos(Location_Target);

	UEngineRandom StartRandom;
	FVector2D Pos = MoveDir[StartRandom.RandomInt(0, static_cast<int>(MoveDir.size()) - 1)];
	int a = 0;

	AddActorLocation(MoveTO * _DeltaTime * Speed);

	if (true == CheckCantMove(Location_Target))
	{
		if (GetTileNext != nullptr)
		{
			if (GetTileNext->SpriteIndex == 1 || GetTileNext->SpriteIndex == 2)
			{
				MoveTO = Pos;
				AddActorLocation(MoveTO * _DeltaTime * Speed);
			}
			return;



		//if (MoveTO == FVector2D{ -1, 0 })
		//{
		//	MoveTO = FVector2D::RIGHT;
		//	AddActorLocation(MoveTO * _DeltaTime * Speed);
		//	return;
		//}
		//if (MoveTO == FVector2D{ 1, 0 })
		//{
		//	MoveTO = FVector2D::LEFT;
		//	AddActorLocation(MoveTO * _DeltaTime * Speed);
		//	return;
		//}
	}





}
