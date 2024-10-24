#include "PreCompile.h"
#include "EduContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "EndGameMode.h"
#include "Player.h"
#include "Monster.h"

EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

void EduContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, APlayer>("Title");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, AMonster>("Play");
	UEngineAPICore::GetCore()->CreateLevel<AEndGameMode, APlayer>("End");

	UEngineAPICore::GetCore()->OpenLevel("Title");
	UEngineAPICore::GetCore()->OpenLevel("Play");
	UEngineAPICore::GetCore()->OpenLevel("End");
}

void EduContentsCore::Tick()
{
}