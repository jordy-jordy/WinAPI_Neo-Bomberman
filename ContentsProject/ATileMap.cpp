#include "PreCompile.h"
#include "ATileMap.h"

#include <EngineCore/SpriteRenderer.h>

#include "PlayGameMode.h"

ATileMap::ATileMap()
{
	
}

ATileMap::~ATileMap()
{
}

void ATileMap::Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize)
{
	SpriteName = _Sprite;
	TileSize = _TileSize;
	TileCount = _Count;

	AllTiles.resize(_Count.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_Count.X);;
	}
}


// 해당 위치에 폭탄이 있는지 체크하는 함수
bool ATileMap::IsBomb(FIntPoint _Index)
{
	if (true == IsIndexOver(_Index))
	{
		return true;
	}

	return AllTiles[_Index.Y][_Index.X].Bomb != nullptr;
}

// 해당 위치에 폭탄을 세팅하는 함수
void ATileMap::SetBomb(FIntPoint _Index, class ABomb* _Bomb)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	AllTiles[_Index.Y][_Index.X].Bomb = _Bomb;
}

// 해당 위치에 제거되는 오브젝트를 세팅하는 함수
void ATileMap::SetDestroyObject(FIntPoint _Index, class ATile_Destroy* _Object)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	AllTiles[_Index.Y][_Index.X].Object = _Object;
}

FVector2D ATileMap::IndexToTileLocation(FIntPoint _Index)
{
	return FVector2D(_Index.X * TileSize.X, _Index.Y * TileSize.Y);
}

FIntPoint ATileMap::LocationToIndex(FVector2D _Location)
{
	FVector2D Location = _Location / TileSize;

	return FIntPoint(Location.iX(), Location.iY());
}

void ATileMap::SetTileLocation(FVector2D _Location, int _SpriteIndex)
{
	FVector2D TilePos = _Location - GetActorLocation();

	FIntPoint Point = LocationToIndex(TilePos);

	if (true == IsIndexOver(Point))
	{
		return;
	}

	SetTileIndex(Point, _SpriteIndex);
}



bool ATileMap::IsIndexOver(FIntPoint _Index)
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (TileCount.X - 1 < _Index.X)
	{
		return true;
	}

	if (TileCount.Y - 1 < _Index.Y)
	{
		return true;
	}

	return false;
}



void ATileMap::SetTileIndex(FIntPoint _Index, int _SpriteIndex)
{
	SetTileIndex(_Index, { 0,0 }, TileSize, _SpriteIndex);
}


void ATileMap::SetTileIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}


	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}


	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(SpriteName, _SpriteIndex);

	FVector2D TileLocation = IndexToTileLocation(_Index);
	FindSprite->SetComponentScale(_SpriteScale);
	FindSprite->SetOrder(_Index.Y * TileSize.Y);

	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);
	AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
	AllTiles[_Index.Y][_Index.X].Scale = _SpriteScale;
	AllTiles[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
}



Tile* ATileMap::GetTileRef(FVector2D _Location)
{
	FIntPoint Point = LocationToIndex(_Location);

	return GetTileRef(Point);
}

Tile* ATileMap::GetTileRef(FIntPoint _Index)
{
	if (true == IsIndexOver(_Index))
	{
		return nullptr;
	}

	return &AllTiles[_Index.Y][_Index.X];
}

void ATileMap::Serialize(UEngineSerializer& _Ser)
{


	_Ser << TileCount;
	_Ser << TileSize;
	_Ser << SpriteName;
	_Ser << AllTiles;
}

void ATileMap::DeSerialize(UEngineSerializer& _Ser)
{

	_Ser >> TileCount;
	_Ser >> TileSize;
	_Ser >> SpriteName;

	std::vector<std::vector<Tile>> LoadTiles;
	_Ser >> LoadTiles;

	Create(SpriteName, TileCount, TileSize);

	for (int y = 0; y < LoadTiles.size(); y++)
	{
		for (int x = 0; x < LoadTiles[y].size(); x++)
		{
			SetTileIndex({ x, y }, LoadTiles[y][x].Pivot, LoadTiles[y][x].Scale, LoadTiles[y][x].SpriteIndex);
		}
	}

}

std::vector<FIntPoint> ATileMap::FindSpriteIndex(int _TileType)
{
	std::vector<FIntPoint> positions;

	for (int y = 0; y < TileCount.Y; ++y)
	{
		for (int x = 0; x < TileCount.X; ++x)
		{
			if (AllTiles[y][x].SpriteIndex == _TileType)
			{
				positions.push_back({x, y});
			}
		}
	}
	return positions;
}

void ATileMap::RemoveTile(FVector2D _Pos)
{
	FIntPoint TargetIndex = LocationToIndex(_Pos);
	if (AllTiles[TargetIndex.Y][TargetIndex.X].SpriteIndex == 1)
	{
		AllTiles[TargetIndex.Y][TargetIndex.X].SpriteRenderer->Destroy();
		AllTiles[TargetIndex.Y][TargetIndex.X].SpriteRenderer = nullptr;
		AllTiles[TargetIndex.Y][TargetIndex.X].Pivot = FVector2D::ZERO;
		AllTiles[TargetIndex.Y][TargetIndex.X].Scale = FVector2D::ZERO;
		AllTiles[TargetIndex.Y][TargetIndex.X].SpriteIndex = -1;

		Mode->PlusScore(SpriteIndex_Score);
	}
}

FIntPoint ATileMap::LocationToMatrixIdx(const FVector2D& _loc)
{
	FIntPoint idx = LocationToIndex(_loc - GetActorLocation());
	return idx;
}
