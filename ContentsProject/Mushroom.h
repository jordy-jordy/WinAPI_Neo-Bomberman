#pragma once
#include "Monster.h"

// Ό³Έν :
class AMushroom : public AMonster
{
public:
	// constrcuter destructer
	AMushroom();
	~AMushroom();

	// delete Function
	AMushroom(const AMushroom& _Other) = delete;
	AMushroom(AMushroom&& _Other) noexcept = delete;
	AMushroom& operator=(const AMushroom& _Other) = delete;
	AMushroom& operator=(AMushroom&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Mush_Order();

	void SetWallTileMap(class ATileMap* _TileMap) override
	{
		WallTileMap = _TileMap;
	}

	bool CheckCantMove(FVector2D _Pos);

	int CheckNextPos(FVector2D _CurPos);

	void Mush_Move(float _DeltaTime);

	template<typename EnumType>
	std::vector<FVector2D> FindDirectionPos(EnumType _Direction)
	{
		return FindDirectionPos(static_cast<int>(_Direction));
	}
	std::vector<FVector2D> FindDirectionPos(int _Direction);



protected:
	class USpriteRenderer* SpriteRenderer = nullptr;


private:
	class ATileMap* WallTileMap = nullptr;
	float Speed = 500.0f;

	FVector2D MoveTO = FVector2D::LEFT;

	std::vector<FVector2D> MoveDir;
	FVector2D UP = { 0, -1 };
	FVector2D DOWN = { 0, 1 };
	FVector2D LEFT = { -1, 0 };
	FVector2D RIGHT = { 1, 0 };


};
