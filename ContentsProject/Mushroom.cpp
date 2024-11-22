#include "PreCompile.h"
#include "Mushroom.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineBase/EngineRandom.h>

#include "ATileMap.h"
#include "PlayGameMode.h"


AMushroom::AMushroom()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 38, 42 });
	SpriteRenderer->SetPivot({ 0, -8 });

	SpriteRenderer->CreateAnimation("Mushroom_Idle", "01_Mushroom_00_Idle", 0, 1, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Left", "01_Mushroom_01_Left", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Right", "01_Mushroom_02_Right", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Up", "01_Mushroom_03_Up", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("Mushroom_Down", "01_Mushroom_04_Down", 0, 5, 0.2f, true);
	SpriteRenderer->CreateAnimation("None", "None.png", 0, 0, 0.2f, true);
	SpriteRenderer->ChangeAnimation("Mushroom_Idle");

	UniqueRenderer = CreateDefaultSubObject<USpriteRenderer>();
	UniqueRenderer->SetSprite("Mushroom.png");
	UniqueRenderer->SetComponentScale({ 64, 64 });
	UniqueRenderer->SetPivot({ 0, -8 });
	UniqueRenderer->CreateAnimation("Mushroom_Idle", "01_Mushroom_00_Idle", 0, 1, 0.2f, true);
	UniqueRenderer->CreateAnimation("Mushroom_Uniq", "Mushroom.png", 44, 54, 0.2f, false);
	UniqueRenderer->CreateAnimation("Mushroom_Dead", "Mushroom.png", {0, 7}, {0.02f, 0.02f}, true);
	UniqueRenderer->SetActive(false);

	// 고유 랜덤 시드 설정
	RandomEngine.SetSeed(static_cast<__int64>(time(nullptr)) + reinterpret_cast<__int64>(this));
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

	if (ISDEAD == true)
	{
		DeadANiM += _DeltaTime;

		SpriteRenderer->SetActive(false);
		UniqueRenderer->SetActive(true);
		UniqueRenderer->ChangeAnimation("Mushroom_Dead");

		if (DeadANiM >= 3.0f)
		{
			Dead();

			ISDEAD = false;
			SpriteRenderer->SetActive(true);
			UniqueRenderer->SetActive(false);
			UniqueRenderer->ChangeAnimation("Mushroom_Idle");
			return;
		}
		return;
	}

	elapsedTime += _DeltaTime;
	if (elapsedTime >= MAX_TIME)
	{
		if (getRandomValue(MAXDELAY, RandomEngine) == 0)
		{
			UNIQ_SKILL();
		}
		elapsedTime = 0.0f;
	}

	if (UNIQUE_ON == true)
	{
		SpriteRenderer->SetActive(false);
		UniqueRenderer->SetActive(true);

		MoveTO = FVector2D::ZERO;
		if (UniqueRenderer->IsCurAnimationEnd() == true)
		{
			UNIQUE_ON = false;
			SpriteRenderer->SetActive(true);
			UniqueRenderer->SetActive(false);
			UniqueRenderer->ChangeAnimation("Mushroom_Idle");

			GET_RANDOM_DIR();
			MoveTO = RANDOM_DIR;
		}
	}

	DIR_ANIM(MoveTO);
	Mush_Move(_DeltaTime);
}

void AMushroom::Mush_Order()
{
	SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
	UniqueRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
}

std::string AMushroom::NAME_CHECK()
{
	return UniqueRenderer->GetCurSpriteName();
}

void AMushroom::UNIQ_SKILL()
{
	UNIQUE_ON = true;
	UniqueRenderer->ChangeAnimation("Mushroom_Uniq");
}

FVector2D AMushroom::GET_RANDOM_DIR()
{
	UEngineRandom Random;
	int RandomIndex = Random.RandomInt(0, 3);
	FVector2D PossibleDirections[4] = { FVector2D::LEFT, FVector2D::RIGHT, FVector2D::UP, FVector2D::DOWN };
	RANDOM_DIR = PossibleDirections[RandomIndex];
	return RANDOM_DIR;
}

FVector2D AMushroom::InvertLOC(FVector2D _Loc)
{
	if (_Loc == FVector2D::ZERO)
	{
		return CUSTOM_VECTOR_ZERO;
	}

	if (_Loc == FVector2D::LEFT)
	{
		return CUSTOM_VECTOR_LEFT;
	}

	if (_Loc == FVector2D::RIGHT)
	{
		return CUSTOM_VECTOR_RIGHT;
	}

	if (_Loc == FVector2D::UP)
	{
		return CUSTOM_VECTOR_UP;
	}

	if (_Loc == FVector2D::DOWN)
	{
		return CUSTOM_VECTOR_DOWN;
	}

	return FVector2D::ZERO;
}

void AMushroom::DIR_ANIM(FVector2D _Dir)
{
	if (MoveTO == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Mushroom_Up");
	}
	if (MoveTO == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Mushroom_Down");
	}
	if (MoveTO == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Mushroom_Left");
	}
	if (MoveTO == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Mushroom_Right");
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
		_NEXTTILE->SpriteIndex != 3 &&
		BOMBBOMB(_NEXTPOS) == false)
	{
		return true;
	}
	return false;
}

bool AMushroom::BOMBBOMB(FVector2D _NEXTPOS)
{
	FIntPoint PosToIndex = { _NEXTPOS.iX(), _NEXTPOS.iY() };
	BOMBCHECK = WallTileMap->IsBomb(PosToIndex);
	return BOMBCHECK;
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

	if (ISDEAD == true)
	{
		return;
	}

	// 현재 방향으로 이동 가능한 경우
	if (ISMOVE(Index_Target, GetTileNext))
	{
		AddActorLocation(MoveTO * _DeltaTime * Speed);
		return;
	}

	// 이동 불가능한 경우, 랜덤하게 새로운 방향 선택
	UEngineRandom Random;
	int RandomIndex = Random.RandomInt(0, 3);
	FVector2D PossibleDirections[4] = { FVector2D::LEFT, FVector2D::RIGHT, FVector2D::UP, FVector2D::DOWN };

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

int AMushroom::getRandomValue(int _MaxDelay, UEngineRandom& _randomEngine)
{
	// _randomEngine을 사용해 0부터 _MaxDelay - 1 사이의 값을 반환
	return _randomEngine.RandomInt(0, _MaxDelay - 1);
}

void AMushroom::Dead()
{
	Mode->PlusScore(MushroomScore);
	Destroy();
}
