#include "PreCompile.h"
#include "Bomb.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "ATileMap.h"


ABomb::ABomb()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("01_Bomb_00_Idle");
	SpriteRenderer->SetComponentScale({ 32, 32 });

	SpriteRenderer->CreateAnimation("Bomb_Idle", "01_Bomb_00_Idle", { 0, 1, 2, 1 }, { 0.2f, 0.2f ,0.2f ,0.2f });
	SpriteRenderer->ChangeAnimation("Bomb_Idle");

	SpriteRenderer->SetOrder(ERenderOrder::BOMB);

	TimeEventer.PushEvent(2.0f, std::bind(&ABomb::Bomb_ExPlode, this), false, false);
}

ABomb::~ABomb()
{
	ClearBombTile(); // 소멸자에서 타일맵 업데이트
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Bomb_Destroy();
}

void ABomb::SetWallTileMap(ATileMap* _TileMap, FIntPoint _Index)
{
	WallTileMap = _TileMap;
	BombTileIndex = _Index;
}

void ABomb::Bomb_Destroy()
{
	if (nullptr != Explode_Center)
	{
		if (true == Explode_Center->IsCurAnimationEnd())
		{
			// 폭탄 제거
			Destroy();
		}
	}
}

void ABomb::ClearBombTile()
{
	if (WallTileMap != nullptr)
	{
		WallTileMap->SetBomb(BombTileIndex, nullptr); // 폭탄 포인터를 nullptr로 설정
	}
}


void ABomb::Bomb_ExPlode()
{
	int _Power = CurBombPower;

	Explode_Center = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Center->SetSprite("01_Bomb_01_Center");
	Explode_Center->CreateAnimation("Bomb_Center", "01_Bomb_01_Center", 0, 11, 0.15f, false);
	Explode_Center->ChangeAnimation("Bomb_Center");
	Explode_Center->SetComponentScale({ 32, 32 });
	Explode_Center->SetComponentLocation({ 0, 0 });

	FVector2D TileSize = WallTileMap->GetTileHalfSize();

	FVector2D Pos = GetActorLocation() - WallTileMap->GetActorLocation(); // X, Y에 TILE HALF SIZE (16)을 더한 값
	// 이대로 사용하면 float가 int로 변환되는 과정에 값 왜곡이 일어남

	FVector2D Pos_Minus_TileHalfSize = Pos - WallTileMap->GetTileHalfSize(); // X, Y에 TILE HALF SIZE (16)을 뺀 값
	// 정확한 값을 얻기 위해 사용


	// 왼쪽 확산 처리
	int LeftCount = 0;
	for (int i = 1; i <= _Power - 1; i++)
	{
		Tile* TileDataLeft = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ -32, 0 } *static_cast<float>(i));

		if (TileDataLeft == nullptr || TileDataLeft->SpriteIndex == 2)
		{
			break; // 왼쪽 확산 중단
		}

		USpriteRenderer* Explode_LeftMid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_LeftMid->SetSprite("01_Bomb_07_LeftMid");
		Explode_LeftMid->CreateAnimation("Bomb_LeftMid", "01_Bomb_07_LeftMid", 0, 19, 0.15f, false);
		Explode_LeftMid->ChangeAnimation("Bomb_LeftMid");
		Explode_LeftMid->SetComponentScale({ 32, 32 });
		Explode_LeftMid->SetOrder((Pos + FVector2D{ -32, 0 } *static_cast<float>(i)).Y);
		Explode_LeftMid->SetComponentLocation(FVector2D{ -32, 0 } *static_cast<float>(i));

		if (TileDataLeft->SpriteIndex == 1)
		{
			FVector2D TilePos_Location = Explode_LeftMid->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
			break;
		}

		LeftCount = i;
	}
	Tile* TileDataLeft = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ -32, 0 } *(static_cast<float>(LeftCount + 1)));
	if (TileDataLeft != nullptr)
	{
		if (TileDataLeft->SpriteIndex != 2)
		{
			USpriteRenderer* Explode_Left = CreateDefaultSubObject<USpriteRenderer>();
			Explode_Left->SetSprite("01_Bomb_06_Left");
			Explode_Left->CreateAnimation("Bomb_Left", "01_Bomb_06_Left", 0, 19, 0.15f, false);
			Explode_Left->ChangeAnimation("Bomb_Left");
			Explode_Left->SetComponentScale({ 32, 32 });
			Explode_Left->SetOrder((Pos + FVector2D{ -32, 0 }).Y);
			Explode_Left->SetComponentLocation(FVector2D{ -32, 0 } *(static_cast<float>(LeftCount + 1)));
			
			FVector2D TilePos_Location = Explode_Left->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
		}
	}

	// 위 확산 처리
	int UpCount = 0;
	for (int i = 1; i <= _Power - 1; i++)
	{
		Tile* TileDataUp = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 0, -32 } *static_cast<float>(i));

		if (TileDataUp == nullptr || TileDataUp->SpriteIndex == 2)
		{
			break; // 위 확산 중단
		}

		USpriteRenderer* Explode_UpMid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_UpMid->SetSprite("01_Bomb_03_UpMid");
		Explode_UpMid->CreateAnimation("Bomb_UpMid", "01_Bomb_03_UpMid", 0, 19, 0.15f, false);
		Explode_UpMid->ChangeAnimation("Bomb_UpMid");
		Explode_UpMid->SetComponentScale({ 32, 32 });
		Explode_UpMid->SetOrder((Pos + FVector2D{ 0, -32 } *static_cast<float>(i)).Y);
		Explode_UpMid->SetComponentLocation(FVector2D{ 0, -32 } *static_cast<float>(i));

		if (TileDataUp->SpriteIndex == 1)
		{
			FVector2D TilePos_Location = Explode_UpMid->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
			break;
		}
		UpCount = i;
	}
	Tile* TileDataUp = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 0, -32 } *(static_cast<float>(UpCount + 1)));
	if (TileDataUp != nullptr)
	{
		if (TileDataUp->SpriteIndex != 2)
		{
			USpriteRenderer* Explode_Up = CreateDefaultSubObject<USpriteRenderer>();
			Explode_Up->SetSprite("01_Bomb_02_Up");
			Explode_Up->CreateAnimation("Bomb_Up", "01_Bomb_02_Up", 0, 19, 0.15f, false);
			Explode_Up->ChangeAnimation("Bomb_Up");
			Explode_Up->SetComponentScale({ 32, 32 });
			Explode_Up->SetOrder((Pos + FVector2D{ 0, -32 }).Y);
			Explode_Up->SetComponentLocation(FVector2D{ 0, -32 } *(static_cast<float>(UpCount + 1)));

			FVector2D TilePos_Location = Explode_Up->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
		}
	}

	// 오른쪽 확산 처리
	int RightCount = 0;
	for (int i = 1; i <= _Power - 1; i++)
	{
		Tile* TileDataRight = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 32, 0 } *static_cast<float>(i));

		if (TileDataRight == nullptr || TileDataRight->SpriteIndex == 2)
		{
			break; // 오른쪽 확산 중단
		}

		USpriteRenderer* Explode_RightMid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_RightMid->SetSprite("01_Bomb_09_RightMid");
		Explode_RightMid->CreateAnimation("Bomb_RightMid", "01_Bomb_09_RightMid", 0, 19, 0.15f, false);
		Explode_RightMid->ChangeAnimation("Bomb_RightMid");
		Explode_RightMid->SetComponentScale({ 32, 32 });
		Explode_RightMid->SetOrder((Pos + FVector2D{ 32, 0 } *static_cast<float>(i)).Y);
		Explode_RightMid->SetComponentLocation(FVector2D{ 32, 0 } *static_cast<float>(i));

		if (TileDataRight->SpriteIndex == 1)
		{
			FVector2D TilePos_Location = Explode_RightMid->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
			break;
		}
		RightCount = i;
	}
	Tile* TileDataRight = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 32, 0 } *(static_cast<float>(RightCount + 1)));
	if (TileDataRight != nullptr)
	{
		if (TileDataRight->SpriteIndex != 2)
		{
			USpriteRenderer* Explode_Right = CreateDefaultSubObject<USpriteRenderer>();
			Explode_Right->SetSprite("01_Bomb_08_Right");
			Explode_Right->CreateAnimation("Bomb_Right", "01_Bomb_08_Right", 0, 19, 0.15f, false);
			Explode_Right->ChangeAnimation("Bomb_Right");
			Explode_Right->SetComponentScale({ 32, 32 });
			Explode_Right->SetOrder((Pos + FVector2D{ 32, 0 }).Y);
			Explode_Right->SetComponentLocation(FVector2D{ 32, 0 } *(static_cast<float>(RightCount + 1)));

			FVector2D TilePos_Location = Explode_Right->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
		}
	}

	// 아래 확산 처리
	int DownCount = 0;
	for (int i = 1; i <= _Power - 1; i++)
	{
		Tile* TileDataDown = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 0, 32 } *static_cast<float>(i));

		if (TileDataDown == nullptr || TileDataDown->SpriteIndex == 2)
		{
			break; // 오른쪽 확산 중단
		}

		USpriteRenderer* Explode_DownMid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_DownMid->SetSprite("01_Bomb_05_DownMid");
		Explode_DownMid->CreateAnimation("Bomb_DownMid", "01_Bomb_05_DownMid", 0, 19, 0.15f, false);
		Explode_DownMid->ChangeAnimation("Bomb_DownMid");
		Explode_DownMid->SetComponentScale({ 32, 32 });
		Explode_DownMid->SetOrder((Pos + FVector2D{ 0, 32 } *static_cast<float>(i)).Y);
		Explode_DownMid->SetComponentLocation(FVector2D{ 0, 32 } *static_cast<float>(i));

		if (TileDataDown->SpriteIndex == 1)
		{
			FVector2D TilePos_Location = Explode_DownMid->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
			break;
		}
		DownCount = i;
	}
	Tile* TileDataDown = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 0, 32 } *(static_cast<float>(DownCount + 1)));
	if (TileDataDown != nullptr)
	{
		if (TileDataDown->SpriteIndex != 2)
		{
			USpriteRenderer* Explode_Down = CreateDefaultSubObject<USpriteRenderer>();
			Explode_Down->SetSprite("01_Bomb_04_Down");
			Explode_Down->CreateAnimation("Bomb_Down", "01_Bomb_04_Down", 0, 19, 0.15f, false);
			Explode_Down->ChangeAnimation("Bomb_Down");
			Explode_Down->SetComponentScale({ 32, 32 });
			Explode_Down->SetOrder((Pos + FVector2D{ 0, 32 }).Y);
			Explode_Down->SetComponentLocation(FVector2D{ 0, 32 } *(static_cast<float>(DownCount + 1)));

			FVector2D TilePos_Location = Explode_Down->GetComponentLocation();
			FVector2D BombPos_Location = GetActorLocation() - WallTileMap->GetActorLocation();
			FVector2D TargetPos = BombPos_Location + TilePos_Location;
			WallTileMap->RemoveTile(TargetPos);
		}
	}

}