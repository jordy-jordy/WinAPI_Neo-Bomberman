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
	UniqueRenderer->SetActive(false);

	TimeEventer.PushEvent(GET_RANDOM_TIME(), std::bind(&AMushroom::UNIQ_SKILL, this), false, true);
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

	if (UNIQUE_ON == true)
	{
		SpriteRenderer->SetActive(false);

		MoveTO = FVector2D::ZERO;
		if (UniqueRenderer->IsCurAnimationEnd() == true)
		{
			UNIQUE_ON = false;
			//UniqueRenderer->Destroy();
			//UniqueRenderer = nullptr;
			UniqueRenderer->SetActive(false);
			SpriteRenderer->SetActive(true);
			UniqueRenderer->ChangeAnimation("Mushroom_Idle");

			GET_RANDOM_DIR();
			MoveTO = RANDOM_DIR;
		}
	}

	Mush_Order();
	DIR_ANIM(MoveTO);
	Mush_Move(_DeltaTime);
}

void AMushroom::Mush_Order()
{
	SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);
}

std::string AMushroom::NAME_CHECK()
{
	return UniqueRenderer->GetCurSpriteName();
}

void AMushroom::UNIQ_SKILL()
{
	UNIQUE_ON = true;
	UniqueRenderer->SetActive(true);
	UniqueRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);;
	UniqueRenderer->ChangeAnimation("Mushroom_Uniq");
}

float AMushroom::GET_RANDOM_TIME()
{
	UEngineRandom Random;
	RandomTime = Random.Randomfloat(MIN_TIME, MAX_TIME);
	return RandomTime;
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
		return TEMP_ZERO;
	}

	if (_Loc == FVector2D::LEFT)
	{
		return TEMP_LEFT;
	}

	if (_Loc == FVector2D::RIGHT)
	{
		return TEMP_RIGHT;
	}

	if (_Loc == FVector2D::UP)
	{
		return TEMP_UP;
	}

	if (_Loc == FVector2D::DOWN)
	{
		return TEMP_DOWN;
	}
}

void AMushroom::DIR_ANIM(FVector2D _Dir)
{
	//if (MoveTO == FVector2D::ZERO)
	//{
	//	SpriteRenderer->ChangeAnimation("Mushroom_Uniq");
	//}
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

void AMushroom::RemoveMushroom()
{
	this->Destroy();
}

