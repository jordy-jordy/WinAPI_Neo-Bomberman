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

	SpriteRenderer->CreateAnimation("Bomb_Center", "01_Bomb_01_Center", 0, 19, 0.15f);


	SpriteRenderer->SetOrder(ERenderOrder::BOMB);

}

ABomb::~ABomb()
{
	ClearBombTile(); // 소멸자에서 타일맵 업데이트
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Bomb_Explode(_DeltaTime);
}

void ABomb::SetWallTileMap(ATileMap* _TileMap, FIntPoint _Index)
{
	WallTileMap = _TileMap;
	BombTileIndex = _Index;
}


void ABomb::StartExplodeTimer()
{
	ExplodeTimer_On = true;
}


void ABomb::StartDestroyTimer()
{
	DestroyTimer_On = true;
}


void ABomb::Bomb_Explode(float _DeltaTime)
{
	if (true != ExplodeTimer_On)
	{
		return;
	}

	Explodecheck_Start_Timer += _DeltaTime;
	if (Explodecheck_Start_Timer >= Explode_Start_Time)
	{
		//SpriteRenderer->ChangeAnimation("Bomb_Center"); // 폭발 애니메이션으로 변경
		//Explode_Up->ChangeAnimation("Bomb_Up");
		//Explode_Left->ChangeAnimation("Bomb_Left");
		//Explode_Down->ChangeAnimation("Bomb_Down");
		//Explode_Right->ChangeAnimation("Bomb_Right");

		// StartDestroyTimer(); // 폭탄 제거 타이머 ON
		// Bomb_Destroy(_DeltaTime); // 폭탄 제거 함수 실행
	}
}

void ABomb::Bomb_Destroy(float _DeltaTime)
{
	if (true != DestroyTimer_On)
	{
		return;
	}

	Bomb_DestroyTimer += _DeltaTime;

	if (Bomb_DestroyTimer >= Bomb_DestroyTime)
	{
		ClearBombTile(); // 폭탄 제거 전 타일맵 업데이트
		Destroy(); // 폭탄 제거
	}
}

void ABomb::ClearBombTile()
{
	if (WallTileMap != nullptr)
	{
		WallTileMap->SetBomb(BombTileIndex, nullptr); // 폭탄 포인터를 nullptr로 설정
	}
}


void ABomb::SetPower(int _Power)
{
	CurBombPower = _Power;

	USpriteRenderer* Explode_Center = CreateDefaultSubObject<USpriteRenderer>();
	Explode_Center->SetSprite("01_Bomb_01_Center");
	Explode_Center->CreateAnimation("Bomb_Center", "01_Bomb_01_Center", 0, 19, 0.15f);
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
	for (int i = 1; i <= _Power -1; i++)
	{
		Tile* TileDataLeft = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ -32, 0 } * i );

		if (TileDataLeft == nullptr || TileDataLeft->SpriteIndex == 1 || TileDataLeft->SpriteIndex == 2)
		{
			break; // 왼쪽 확산 중단
		}

		USpriteRenderer* Explode_LeftMid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_LeftMid->SetSprite("01_Bomb_07_LeftMid");
		Explode_LeftMid->CreateAnimation("Bomb_LeftMid", "01_Bomb_07_LeftMid", 0, 19, 0.15f);
		Explode_LeftMid->ChangeAnimation("Bomb_LeftMid");
		Explode_LeftMid->SetComponentScale({ 32, 32 });
		Explode_LeftMid->SetOrder((Pos + FVector2D{ -32, 0 } *i).Y);
		Explode_LeftMid->SetComponentLocation(FVector2D{ -32, 0 } *i);
		
		LeftCount = i;
	}
	Tile* TileDataLeft = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ -32, 0 } *(LeftCount + 1));
	if (TileDataLeft != nullptr)
	{
		if (TileDataLeft->SpriteIndex != 2)
		{
			USpriteRenderer* Explode_Left = CreateDefaultSubObject<USpriteRenderer>();
			Explode_Left->SetSprite("01_Bomb_06_Left");
			Explode_Left->CreateAnimation("Bomb_Left", "01_Bomb_06_Left", 0, 19, 0.15f);
			Explode_Left->ChangeAnimation("Bomb_Left");
			Explode_Left->SetComponentScale({ 32, 32 });
			Explode_Left->SetOrder((Pos + FVector2D{ -32, 0 }).Y);
			Explode_Left->SetComponentLocation(FVector2D{ -32, 0 } *(LeftCount + 1));
		}
	}


	// 오른쪽 확산 처리
	int RightCount = 0;
	for (int i = 1; i <= _Power -1; i++)
	{
		Tile* TileDataRight = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 32, 0 } *i);

		if (TileDataRight == nullptr || TileDataRight->SpriteIndex == 1 || TileDataRight->SpriteIndex == 2)
		{
			break; // 오른쪽 확산 중단
		}

		USpriteRenderer* Explode_RightMid = CreateDefaultSubObject<USpriteRenderer>();
		Explode_RightMid->SetSprite("01_Bomb_09_RightMid");
		Explode_RightMid->CreateAnimation("Bomb_RightMid", "01_Bomb_09_RightMid", 0, 19, 0.15f);
		Explode_RightMid->ChangeAnimation("Bomb_RightMid");
		Explode_RightMid->SetComponentScale({ 32, 32 });
		Explode_RightMid->SetOrder((Pos + FVector2D{ 32, 0 } * i ).Y);
		Explode_RightMid->SetComponentLocation(FVector2D{ 32, 0 } * i );

		RightCount = i;
	}
	Tile* TileDataRight = WallTileMap->GetTileRef(Pos_Minus_TileHalfSize + FVector2D{ 32, 0 } *(RightCount + 1));
	if (TileDataRight != nullptr)
	{
		if (TileDataRight->SpriteIndex != 2)
		{
			USpriteRenderer* Explode_Right = CreateDefaultSubObject<USpriteRenderer>();
			Explode_Right->SetSprite("01_Bomb_08_Right");
			Explode_Right->CreateAnimation("Bomb_Right", "01_Bomb_08_Right", 0, 19, 0.15f);
			Explode_Right->ChangeAnimation("Bomb_Right");
			Explode_Right->SetComponentScale({ 32, 32 });
			Explode_Right->SetOrder((Pos + FVector2D{ 32, 0 }).Y);
			Explode_Right->SetComponentLocation(FVector2D{ 32, 0 } *(RightCount + 1));
		}
	}



	//Explode_Down = CreateDefaultSubObject<USpriteRenderer>();
	//Explode_Down->SetSprite("01_Bomb_04_Down");
	//Explode_Down->CreateAnimation("Bomb_Down", "01_Bomb_04_Down", 0, 19, 0.15f);
	//Explode_Down->SetComponentScale({ 32, 32 });
	//Explode_Down->SetComponentLocation({ 0, 32 });

	//Explode_Right = CreateDefaultSubObject<USpriteRenderer>();
	//Explode_Right->SetSprite("01_Bomb_08_Right");
	//Explode_Right->CreateAnimation("Bomb_Right", "01_Bomb_08_Right", 0, 19, 0.15f);
	//Explode_Right->SetComponentScale({ 32, 32 });
	//Explode_Right->SetComponentLocation({ 32, 0 });


	//Explode_Up_Mid->CreateAnimation("Bomb_UpMid", "01_Bomb_03_UpMid", 0, 19, 0.2f);
	//Explode_Left_Mid->CreateAnimation("Bomb_LeftMid", "01_Bomb_07_LeftMid", 0, 19, 0.2f);
	//Explode_Down_Mid->CreateAnimation("Bomb_DownMid", "01_Bomb_05_DownMid", 0, 19, 0.2f);
	//Explode_Right_Mid->CreateAnimation("Bomb_RightMid", "01_Bomb_09_RightMid", 0, 19, 0.2f);
}