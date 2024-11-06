#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

#include "PlayMap.h"
#include "TileMapGameMode.h"
#include "ATileMap.h"

APlayGameMode::APlayGameMode()
{

}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();
	WallTileMap = GetWorld()->SpawnActor<ATileMap>();
	WallTileMap->SetActorLocation({ 96, 64 });

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


	std::vector<FIntPoint> PlayerStartposS = WallTileMap->FindSpriteIndex(ATiles::Player_Spawn);

	GetWorld()->GetPawn()


}

void APlayGameMode::Tick(float _DeltaTime)
{
	if (true == UEngineInput::GetInst().IsDown('L'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Tile");
	}

}