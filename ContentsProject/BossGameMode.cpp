#include "PreCompile.h"
#include "BossGameMode.h"

#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include "PlayMap.h"
#include "ATileMap.h"
#include "Player.h"
#include "Bomb.h"
#include "Monster.h"
#include "Portal.h"
#include "UI_Timer.h"



ABossGameMode::ABossGameMode()
{
};

ABossGameMode::~ABossGameMode()
{

};

void ABossGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 백그라운드 세팅
	APlayMap* BOSS_BG = GetWorld()->SpawnActor<APlayMap>();
	SpriteRendererBOSS = BOSS_BG->SpriteRenderer;
	SpriteRendererBOSS->ChangeAnimation("Boss_BG");

	// UI 세팅
	AUI_Timer* UI_TOP = GetWorld()->SpawnActor<AUI_Timer>();
	UI_TOP->SetActorLocation({ WindowSize.hX(), 0.0f });

	// 타일맵 세팅
	PlayTileMapInit();

	// 플레이어 세팅
	PlayerInit();

}

void ABossGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ABossGameMode::PlayerInit()
{
	std::vector<FIntPoint> PlayerStartPOS = WallTileMap->FindSpriteIndex(ABossTiles::Player_Spawn);

	UEngineRandom StartRandom;
	FIntPoint Point = PlayerStartPOS[StartRandom.RandomInt(0, static_cast<int>(PlayerStartPOS.size()) - 1)];

	FVector2D TileLocation = WallTileMap->IndexToTileLocation(Point) + WallTileMap->GetActorLocation();
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();
	FVector2D LocalLocation = TileLocation + HalfTiles;
	GetWorld()->GetPawn()->SetActorLocation(LocalLocation);

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetWallTileMap(WallTileMap);
}

void ABossGameMode::PlayTileMapInit()
{
	WallTileMap = GetWorld()->SpawnActor<ATileMap>();
	WallTileMap->SetActorLocation(WallTileMapLocation);

	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	Dir.Append("Data");

	std::string SaveFilePath = Dir.GetPathToString() + "\\BossMapData.Data";
	UEngineFile NewFile = SaveFilePath;
	NewFile.FileOpen("rb");

	UEngineSerializer Ser;
	NewFile.Read(Ser);

	WallTileMap->DeSerialize(Ser);

	std::vector<FIntPoint> IDXs_SPAWN = WallTileMap->FindSpriteIndex(4);
	std::vector<FIntPoint> IDXs_PORTAL = WallTileMap->FindSpriteIndex(3);

	Tile* TILEs_SPAWN = nullptr;
	Tile* TILEs_PORTAL = nullptr;

	for (unsigned __int64 i = 0; i < IDXs_SPAWN.size(); i++)
	{
		TILEs_SPAWN = WallTileMap->GetTileRef(IDXs_SPAWN[i]);
		TILEs_SPAWN->SpriteRenderer->SetActive(false);
	}

	for (unsigned __int64 i = 0; i < IDXs_PORTAL.size(); i++)
	{
		TILEs_PORTAL = WallTileMap->GetTileRef(IDXs_PORTAL[i]);
		TILEs_PORTAL->SpriteRenderer->SetActive(false);
	}

}

