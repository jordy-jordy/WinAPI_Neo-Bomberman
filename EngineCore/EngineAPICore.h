#pragma once
#include <string>
// 여러분들이 여기에다가 이렇게 특정 헤더를 넣으면
// F5를 누를때마다. #include <Windows.h>가 재빌드 된다.
// 미리컴파일된 헤더를 사용하면
// 미리컴파일된 헤더에 넣어진 헤더는 빌드를하면 .pch파일에 빌드결과가 남고
// 그후에는 빌드되지 않는다.
// 컴파일 시간이 
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineTimer.h>
#include <EngineBase/EngineString.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

// 함수포인터
// 가상함수

class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

// UEngineAPICore => 언리얼로 보면 world라고 볼수 있다.

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

	static class UEngineAPICore* GetCore()
	{
		return MainCore;
	}

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

	float GetDeltaTime()
	{
		return DeltaTimer.GetDeltaTime();
	}

	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(std::string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);

		if (false != Levels.contains(UpperName))
		{
			MSGASSERT("존재하는 이름의 레벨을 또 만들수 없습니다" + UpperName);
			return nullptr;
		}


		ULevel* NewLevel = new ULevel();

		// 게임 모드가 레벨의 특성을 설정하는 중요한 객체
		NewLevel->CreateGameMode<GameModeType, MainPawnType>();
		NewLevel->SetName(UpperName);


		// 레벨을 string으로 저장하고 string으로 호출한다.
		Levels.insert({ UpperName, NewLevel });

		return NewLevel;
	}


	template<typename GameModeType, typename MainPawnType>
	void ResetLevel(std::string_view _LevelName)
	{
		// DestroyLevelName = _LevelName;
		std::string UpperName = UEngineString::ToUpper(_LevelName);

		// 지금 당장 이녀석을 지우면 안된다.
		if (CurLevel->GetName() != UpperName)
		{
			DestroyLevel(_LevelName);
			CreateLevel<GameModeType, MainPawnType>(UpperName);
			return;
		}

		// CurLevel은 삭제되어야 한다.
		// 나의 포인터는 살아있다. CurLevel
		std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(UpperName);
		Levels.erase(FindIter);
		NextLevel = CreateLevel<GameModeType, MainPawnType>(UpperName);
		IsCurLevelReset = true;
	}

	void DestroyLevel(std::string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);

		if (false == Levels.contains(UpperName))
		{
			// MSGASSERT("존재하지 않는 레벨을 리셋할수 없습니다." + UpperName);
			return;
		}

		std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(UpperName);

		if (nullptr != FindIter->second)
		{
			delete FindIter->second;
			FindIter->second = nullptr;
		}

		Levels.erase(FindIter);
	}


	void OpenLevel(std::string_view _LevelName);

	void SetGlobalTimeScale(float _Scale)
	{
		GlobalTimeScale = _Scale;
	}


protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;
	static UContentsCore* UserCore;

	UEngineTimer DeltaTimer = UEngineTimer();
	UEngineWindow EngineMainWindow = UEngineWindow(); // 엔진 메인 윈도우

	// 누가 레벨의 소유자라고 개념을 잡는게 좋냐?

	// 만들어진 모든 레벨
	std::map<std::string, class ULevel*> Levels;

	// 현재 내가 눈으로 보고 있어야하는 레벨
	// 돌아가고 있는 레벨
	// 포인터 체인지 방식
	class ULevel* CurLevel = nullptr;
	class ULevel* NextLevel = nullptr;
	bool IsCurLevelReset = false;

	float GlobalTimeScale = 1.0f;

	void Tick();

};