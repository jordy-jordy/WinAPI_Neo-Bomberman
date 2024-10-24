#pragma once
// 여러분들이 여기에다가 이렇게 특정 헤더를 넣으면
// F5를 누를때마다. #include <Windows.h>가 재빌드 된다.
// 미리컴파일된 헤더를 사용하면
// 미리컴파일된 헤더에 넣어진 헤더는 빌드를하면 .pch파일에 빌드결과가 남고
// 그후에는 빌드되지 않는다.
// 컴파일 시간이 
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")


// 함수포인터
// 가상함수

class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

// 설명 :
class UEngineAPICore
{
public:
	// constrcuter destructer
	UEngineAPICore();
	~UEngineAPICore();

	// delete Function
	UEngineAPICore(const UEngineAPICore& _Other) = delete;
	UEngineAPICore(UEngineAPICore&& _Other) noexcept = delete;
	UEngineAPICore& operator=(const UEngineAPICore& _Other) = delete;
	UEngineAPICore& operator=(UEngineAPICore&& _Other) noexcept = delete;

	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);

	class UEngineAPICore* GetCore()
	{
		return MainCore;
	}

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;
	static UContentsCore* UserCore;

	UEngineWindow EngineMainWindow; // 엔진 메인 윈도우

	void Tick();

};
