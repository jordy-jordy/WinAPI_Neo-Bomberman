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
#include "Score.h"
#include "UIBar.h"
#include "Fade.h"


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::PlayerInit()
{
	std::vector<FIntPoint> PlayerStartPOS = WallTileMap->FindSpriteIndex(AStageTiles::Player_Spawn);

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

void APlayGameMode::MonsterInit()
{
	{
		AMonster* Mushroom = GetWorld()->SpawnActor<AMushroom>();
		Mushroom->SetWallTileMap(WallTileMap);
		FVector2D TileMapLoc = WallTileMap->GetActorLocation();
		FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
		FIntPoint Index = { 0, 0 };
		FVector2D Mush_Location = WallTileMap->IndexToTileLocation(Index);
		FVector2D LocalLoc = Mush_Location + TileMapLoc + TileHalfSize;
		Mushroom->SetActorLocation(LocalLoc);
		Mushroom->SetMode(this);
	}
	{
		AMonster* Mushroom = GetWorld()->SpawnActor<AMushroom>();
		Mushroom->SetWallTileMap(WallTileMap);
		FVector2D TileMapLoc = WallTileMap->GetActorLocation();
		FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
		FIntPoint Index = { 12, 0 };
		FVector2D Mush_Location = WallTileMap->IndexToTileLocation(Index);
		FVector2D LocalLoc = Mush_Location + TileMapLoc + TileHalfSize;
		Mushroom->SetActorLocation(LocalLoc);
		Mushroom->SetMode(this);
	}
	{
		AMonster* Mushroom = GetWorld()->SpawnActor<AMushroom>();
		Mushroom->SetWallTileMap(WallTileMap);
		FVector2D TileMapLoc = WallTileMap->GetActorLocation();
		FVector2D TileHalfSize = WallTileMap->GetTileHalfSize();
		FIntPoint Index = { 0, 11 };
		FVector2D Mush_Location = WallTileMap->IndexToTileLocation(Index);
		FVector2D LocalLoc = Mush_Location + TileMapLoc + TileHalfSize;
		Mushroom->SetActorLocation(LocalLoc);
		Mushroom->SetMode(this);
	}
}

void APlayGameMode::PortalInit()
{
	Portal = GetWorld()->SpawnActor<APortal>();
	std::vector<FIntPoint> PortalPOS = WallTileMap->FindSpriteIndex(AStageTiles::Object_Portal);
	FVector2D Location = WallTileMap->IndexToTileLocation(PortalPOS[0]);
	FVector2D TileLocation = Location + WallTileMap->GetActorLocation();
	FVector2D HalfTiles = WallTileMap->GetTileHalfSize();
	FVector2D LocalLocation = TileLocation + HalfTiles;
	Portal->SetActorLocation(LocalLocation);
	Portal->SetWallTileMap(WallTileMap);
}


void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 백그라운드 세팅
	APlayMap* STAGE1_BG = GetWorld()->SpawnActor<APlayMap>();
	SpriteRendererSTAGE = STAGE1_BG->SpriteRenderer;
	SpriteRendererSTAGE->ChangeAnimation("Stage1_BG");

	// UI바 세팅
	AUIBar* UI_TOP = GetWorld()->SpawnActor<AUIBar>();

	// 스코어(시간) 세팅
	Minute = GetWorld()->SpawnActor<AScore>();
	Minute->SetTextSpriteName("TimeCount.png");
	Minute->SetActorLocation({ 282, 24 });
	Minute->SetTextScale({ 16, 12 });
	Minute->SetAlignment(AScore::Alignment::Left);
	Minute->SetOrder(ERenderOrder::TEXT_UI);

	Second = GetWorld()->SpawnActor<AScore>();
	Second->SetTextSpriteName("TimeCount.png");
	Second->SetActorLocation({ 314, 24 });
	Second->SetTextScale({ 16, 12 });
	Second->SetAlignment(AScore::Alignment::Left);
	Second->SetOrder(ERenderOrder::TEXT_UI);

	Zero = GetWorld()->SpawnActor<AScore>();
	Zero->SetTextSpriteName("TimeCount.png");
	Zero->SetActorLocation({ 314, 24 });
	Zero->SetTextScale({ 16, 12 });
	Zero->SetAlignment(AScore::Alignment::Left);
	Zero->SetOrder(ERenderOrder::TEXT_UI);
	Zero->SetValue(0);
	Zero->SetActive(false);

	// 스코어(점수) 세팅
	Score = GetWorld()->SpawnActor<AScore>();
	Score->SetTextSpriteName("BarScoreNumber.png");
	Score->SetActorLocation({264, 23});
	Score->SetTextScale({ 16, 14 });
	Score->SetAlignment(AScore::Alignment::Right);
	Score->SetOrder(ERenderOrder::TEXT_UI);

	// 타일맵 세팅
	PlayTileMapInit();

	// 플레이어 세팅
	PlayerInit();

	// 몬스터 세팅
	MonsterInit();

	// 포탈 세팅
	PortalInit();

	Actor_Fade = GetWorld()->SpawnActor<AFade>();
	Actor_Fade->SetFadeSpeed(1.5f);
	Actor_Fade->SetActive(false);

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Actor_Fade->SetActive(true);
	Actor_Fade->FadeOut();

	Score->SetValue(PlayerScore);

	IsMonsterAllDead();
	PortalON();
	if (Portal->GET_ISCANMOVE() == true)
	{
		MOVETO_BOSS();
	}

	if (true == UEngineInput::GetInst().IsDown('L'))
	{
		UEngineAPICore::GetCore()->OpenLevel("MAPEDIT");
	}

	Time -= _DeltaTime;

	int M = static_cast<int>(Time) / 60;
	int S = static_cast<int>(Time) % 60;

	if (S < 0 || M < 0)
	{
		return;
	}

	Minute->SetValue(M);

	if (S >= 10)
	{
		Zero->SetActive(false);
		Second->SetActorLocation({ 314, 24 });
		Second->SetValue(S);
	}
	else if (S < 10)
	{
		Zero->SetActive(true);
		Second->SetActorLocation({ 330, 24 });
		Second->SetValue(S);
	}

}

bool APlayGameMode::IsMonsterAllDead()
{
	std::list<AMonster*> AllMonsters;
	AllMonsters = GetWorld()->GetActorsFromClass<AMonster>();

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

void APlayGameMode::MOVETO_BOSS()
{
	FVector2D PLAYER_POS = GetWorld()->GetPawn()->GetActorLocation() - WallTileMapLocation;
	FVector2D PORTAL_POS = Portal->GetActorLocation() - WallTileMapLocation;

	FIntPoint PLAYER_INDEX = WallTileMap->LocationToIndex(PLAYER_POS);
	FIntPoint PORTAL_INDEX = WallTileMap->LocationToIndex(PORTAL_POS);

	if (PLAYER_INDEX == PORTAL_INDEX)
	{
		UEngineAPICore::GetCore()->OpenLevel("BOSS");
	}

}



