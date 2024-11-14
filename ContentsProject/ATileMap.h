#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

#include "ContentsEnum.h"


class Tile : public ISerializObject
{
public:
	class USpriteRenderer* SpriteRenderer;

	bool IsMove = true;
	int TileType = -1;
	FVector2D Scale;
	FVector2D Pivot;
	int SpriteIndex;

	// 폭탄
	class ABomb* Bomb = nullptr;

	// 삭제 오브젝트
	class ATile_Destroy* Object = nullptr;

	void Serialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		if (nullptr != SpriteRenderer)
		{
			SpriteName = SpriteRenderer->GetCurSpriteName();
		}
		_Ser << SpriteName;
		_Ser << IsMove;
		_Ser << TileType;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}

	void DeSerialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> TileType;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;
	}
};


class ATileMap : public AActor, public ISerializObject
{
public:
	ATileMap();
	~ATileMap();

	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

	void Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize);

	void SetTileLocation(FVector2D _Location, int _SpriteIndex);

	void SetTileIndex(FIntPoint _Index, int _SpriteIndex);
	void SetTileIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector2D _Location);

	FVector2D IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index);
	bool IsIndexOverFVector(FVector2D _Pos);

	void Serialize(UEngineSerializer& _Ser);
	void DeSerialize(UEngineSerializer& _Ser);

	template<typename EnumType>
	std::vector<FIntPoint> FindSpriteIndex(EnumType _TileType)
	{
		return FindSpriteIndex(static_cast<int>(_TileType));
	}

	std::vector<FIntPoint> FindSpriteIndex(int _TileType);


	FVector2D GetTileHalfSize()
	{
		return FVector2D( TileSize.X * 0.5f, TileSize.Y * 0.5f);
	}

	FVector2D GetTileSize()
	{
		return TileSize;
	}

	// 폭탄 관련 함수
	bool IsBomb(FIntPoint _Index); // 해당 위치에 폭탄이 있는지 체크하는 함수
	void SetBomb(FIntPoint _Index, class ABomb* _Bomb); // 해당 위치에 폭탄을 세팅하는 함수
	
	// 타일 제거 함수
	void RemoveTile(FVector2D _Pos);

	// 제거되는 오브젝트 애니메이션 스폰용
	void SetDestroyObject(FIntPoint _Index, class ATile_Destroy* _Object);



protected:

private:
	FIntPoint TileCount;
	std::string SpriteName;
	FVector2D TileSize;
	std::vector<std::vector<Tile>> AllTiles;
};


