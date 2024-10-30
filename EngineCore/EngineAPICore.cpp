#include "PreCompile.h"
#include "EngineAPICore.h"
#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>



// 엔진을 통틀어서 1번 만들어지기 때문에.
// 1번 세팅되고 절대로 바뀌지 않을거다.
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

#include <Windows.h>
// 1 저는 초당 버튼을 1번 눌러요
//QueryPerformanceCounter

// 3 현재까지 3번 눌렀어요 
//QueryPerformanceFrequency

// #include <chrono>

UEngineAPICore::UEngineAPICore()
{

}

UEngineAPICore::~UEngineAPICore()
{
	std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Levels.clear();
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);

	// 객체 안만들면 객체지향이 아닌거 같아서 객체로 하자.
	// 엔진의 기능이 집약되어 있다. CreateLevel;
	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();
	MainCore = &Core;

	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));;
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}

void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

// 이 함수가 1초에 몇번 실행되냐가 프레임입니다.
void UEngineAPICore::EngineTick()
{
	//AXVidio NewVidio;
	//NewVidio.Play("AAAA.avi");

	// 시간재기
	// 이벤트
	// 랜더링
	// 충돌


	// 지금 전혀 용도를 찾지 못해서 사용하지 않는 함수입니다.
	UserCore->Tick();

	// MainCore->TimeCheck();
	MainCore->Tick();
	// MainCore->Render();
	// MainCore->Collision();
}

void UEngineAPICore::Tick()
{
	// 시간을 잴겁니다. 현재시간 
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();

	// 키체크
	UEngineInput::GetInst().KeyCheck(DeltaTime);

	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진 코어에 현재 레벨이 지정되지 않았습니다");
		return;
	}

	UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Tick(DeltaTime);
	//  UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Render();

}


void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();

	//if (true == Levels.contains(ChangeName))
	//{
	//	MSGASSERT(ChangeName + "라는 이름의 레벨은 존재하지 않습니다.");
	//	return;
	//}

	//// 최신 방식
	// 주의할 점이 하나가 있다.
	// 없으면 노드를 insert까지 해버린다.
	// 내부에서 없으면 만든다까지 겸하고 있다.
	// CurLevel = Levels[ChangeName];

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(ChangeName + "라는 이름의 레벨은 존재하지 않습니다.");
		return;
	}

	// 최신 방식
	CurLevel = FindIter->second;
}