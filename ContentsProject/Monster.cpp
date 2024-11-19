#include "PreCompile.h"
#include "Monster.h"
#include "ATileMap.h"


AMonster::AMonster()
{

};

AMonster::~AMonster()
{

};

FIntPoint AMonster::GetMonsterPos_INDEX(FVector2D _CurPos)
{
	FVector2D POS_MONSTER = _CurPos - WallTileMap->GetActorLocation();
	FIntPoint Index = WallTileMap->LocationToIndex(POS_MONSTER);
	return Index;
}

FIntPoint AMonster::GetNextIndex(FIntPoint _CurIndex, MonsterDir _TagetDir)
{
	MonsterDir Dir = _TagetDir;
	switch (Dir)
	{
	case MonsterDir::ZERO:
		_CurIndex + INDEX_ZERO;
		break;
	case MonsterDir::UP:
		_CurIndex + INDEX_UP;
		break;
	case MonsterDir::DOWN:
		_CurIndex + INDEX_DOWN;
		break;
	case MonsterDir::LEFT:
		_CurIndex + INDEX_LEFT;
		break;
	case MonsterDir::RIGHT:
		_CurIndex + INDEX_RIGHT;
		break;
	default:
		break;
	}
}

FVector2D AMonster::GetNextVector(FVector2D _CurPos, MonsterDir _TagetDir)
{
	MonsterDir Dir = _TagetDir;
	switch (Dir)
	{
	case MonsterDir::ZERO:
		_CurPos + VECTOR_ZERO;
		break;
	case MonsterDir::UP:
		_CurPos + VECTOR_UP;
		break;
	case MonsterDir::DOWN:
		_CurPos + VECTOR_DOWN;
		break;
	case MonsterDir::LEFT:
		_CurPos + VECTOR_LEFT;
		break;
	case MonsterDir::RIGHT:
		_CurPos + VECTOR_RIGHT;
		break;
	default:
		break;
	}
}
