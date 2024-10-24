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

// 엔진이 실행되고 단 1번 실행된다.
void EduContentsCore::BeginPlay()
{
	// 아무 쓸모 없는 코드.
	// 애는 님들이 지워줘야한다.
	// TitleLevel = new ULevel();

	// 객체를 생성하는 함수를 제공해주는데 무시하면 안된다는것.
	// 이걸 통해서 안만든 애들 => 다 아무런 쓸모가 없을 가능성이 없다.

	//UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");

}

void EduContentsCore::Tick()
{
}