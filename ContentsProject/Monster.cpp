#include "PreCompile.h"
#include "Monster.h"
#include "ATileMap.h"


AMonster::AMonster()
{

};

AMonster::~AMonster()
{

};

FIntPoint AMonster::GetMonsterPos_INDEX(FVector2D _CurPos, ATileMap* _Map)
{
	FVector2D POS_MONSTER = _CurPos - _Map->GetActorLocation();
	FIntPoint Index = _Map->LocationToIndex(POS_MONSTER);
	return Index;
}

FVector2D AMonster::GetMonsterPos_VECTOR(FVector2D _CurPos, ATileMap* _Map)
{
	FVector2D POS_MONSTER = _CurPos - _Map->GetActorLocation();
	return POS_MONSTER;
}

FIntPoint AMonster::GetNextIndex(FIntPoint _CurIndex, MonsterDir _TagetDir)
{
	MonsterDir Dir = _TagetDir;
	FIntPoint RESULT;

	switch (Dir)
	{
	case MonsterDir::ZERO:
		RESULT = _CurIndex + INDEX_ZERO;
		break;
	case MonsterDir::UP:
		RESULT = _CurIndex + INDEX_UP;
		break;
	case MonsterDir::DOWN:
		RESULT = _CurIndex + INDEX_DOWN;
		break;
	case MonsterDir::LEFT:
		RESULT = _CurIndex + INDEX_LEFT;
		break;
	case MonsterDir::RIGHT:
		RESULT = _CurIndex + INDEX_RIGHT;
		break;
	default:
		break;
	}
	return RESULT;
}

FVector2D AMonster::GetNextVector(FVector2D _CurPos, MonsterDir _TagetDir)
{
	MonsterDir Dir = _TagetDir;
	FVector2D RESULT;

	switch (Dir)
	{
	case MonsterDir::ZERO:
		RESULT = _CurPos + VECTOR_ZERO;
		break;
	case MonsterDir::UP:
		RESULT = _CurPos + VECTOR_UP;
		break;
	case MonsterDir::DOWN:
		RESULT = _CurPos + VECTOR_DOWN;
		break;
	case MonsterDir::LEFT:
		RESULT = _CurPos + VECTOR_LEFT;
		break;
	case MonsterDir::RIGHT:
		RESULT = _CurPos + VECTOR_RIGHT;
		break;
	default:
		break;
	}
	return RESULT;
}
