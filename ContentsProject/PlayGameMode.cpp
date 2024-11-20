#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include "PlayMap.h"
#include "TileMapGameMode.h"
#include "ATileMap.h"
#include "Player.h"
#include "Bomb.h"
#include "Monster.h"
#include "Mushroom.h"
#include "Portal.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::PlayerInit()
{
	// 플레이어 세팅
	std::vector<FIntPoint> PlayerStartPOS = WallTileMap->FindSpriteIndex(ATiles::Player_Spawn);

	UEngineRandom StartRandom;
	FIntPoint Point = PlayerStartPOS[StartRandom.RandomInt(0, static_cast<int>(PlayerStartPOS.size()) - 1)];

	FVector2D TileLocation = WallTileMap->IndexToTileLocation(Point) + WallTileMap->GetActorLocation();
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();
	FVector2D LocalLocation = TileLocation + HalfTiles;
	GetWorld()->GetPawn()->SetActorLocation(LocalLocation);

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetWallTileMap(WallTileMap);
}

void APlayGameMode::PlayTileMapInit()
{
	// 맵 세팅
	WallTileMap = GetWorld()->SpawnActor<ATileMap>();
	WallTileMap->SetActorLocation(WallTileMapLocation);

	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	Dir.Append("Data");

	std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
	UEngineFile NewFile = SaveFilePath;
	NewFile.FileOpen("rb");

	UEngineSerializer Ser;
	NewFile.Read(Ser);

	WallTileMap->DeSerialize(Ser);

}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayMap* BG = GetWorld()->SpawnActor<APlayMap>();

	PlayTileMapInit();
	PlayerInit();

	// 몬스터 세팅
	{
		AMonster* Mushroom = GetWorld()->SpawnActor<AMushroom>();
		Mushroom->SetWallTileMap(WallTileMap);
		FVector2D TileMapLoc = WallTileMap->GetActorLocation();
		FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
		FIntPoint Index = { 0, 0 };
		FVector2D Mush_Location = WallTileMap->IndexToTileLocation(Index);
		FVector2D LocalLoc = Mush_Location + TileMapLoc + TileHalfSize;
		Mushroom->SetActorLocation(LocalLoc);
	}

	// 포탈 세팅
	Portal = GetWorld()->SpawnActor<APortal>();
	std::vector<FIntPoint> PortalPOS = WallTileMap->FindSpriteIndex(ATiles::Object_Portal);
	FVector2D Location = WallTileMap->IndexToTileLocation(PortalPOS[0]);
	FVector2D TileLocation = Location + WallTileMap->GetActorLocation();
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();
	FVector2D LocalLocation = TileLocation + HalfTiles;
	Portal->SetActorLocation(LocalLocation);
	Portal->SetWallTileMap(WallTileMap);

	int a = 0;


}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	IsMonsterAllDead();
	PortalON();

	if (true == UEngineInput::GetInst().IsDown('L'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Tile");
	}

}

bool APlayGameMode::IsMonsterAllDead()
{
	std::list<AMonster*> AllMonsters;
	AllMonsters = GetWorld()->GetActorsFromClass<AMonster>();
	int AAA = AllMonsters.size();

	if (AllMonsters.size() <= 0)
	{
		return true;
	}

	return false;
}

void APlayGameMode::PortalON()
{
	IsMonsterAllDead();
	if (IsMonsterAllDead() == true)
	{
		Portal->PORTAL_SWITCH(true);
	}
}

