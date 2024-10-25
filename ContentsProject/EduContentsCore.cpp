#include "PreCompile.h"
#include "EduContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
#include "Player.h"

EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

void EduContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void EduContentsCore::Tick()
{
}