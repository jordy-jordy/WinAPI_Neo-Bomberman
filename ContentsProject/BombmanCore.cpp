#include "PreCompile.h"
#include "BombmanCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
#include "Player.h"


BombmanCore::BombmanCore()
{
}

BombmanCore::~BombmanCore()
{
}

void BombmanCore::BeginPlay()
{
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle(":: LHJ Win API :: Neo-Bomberman ::");

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");

}

void BombmanCore::Tick()
{
}