#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;


UEngineAPICore::UEngineAPICore()
{
	// 언리얼에서 GEngine
	MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst)
{
	UEngineWindow::EngineWindowInit(_Inst);

	// 객체 안만들면 객체지향이 아닌거 같아서 객체로 하자.
	UEngineAPICore Core;
	Core.EngineMainWindow.Open();

	EngineDelegate NewDel;
	NewDel = EngineLoop;
	return UEngineWindow::WindowMessageLoop(NewDel);
}

void UEngineAPICore::EngineLoop()
{
	MainCore->Tick();
	MainCore->Render();
}

void UEngineAPICore::Tick()
{

}

void UEngineAPICore::Render()
{

}