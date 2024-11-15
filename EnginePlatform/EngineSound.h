#pragma once
#include <EngineBase/EngineResources.h>
#include <map>

#include "ThirdParty/FMOD/inc/fmod.hpp"

// 사운드 플레이어
// 재생하는 사운드에 대한 볼륨및 
class USoundPlayer
{
public:
	friend class UEngineSound;

	void On()
	{
		Control->setPaused(false);
	}

	void Off()
	{
		Control->setPaused(true);
	}

	void OnOffSwtich()
	{
		bool Check = false;
		Control->getPaused(&Check);

		if (true == Check)
		{
			Control->setPaused(false);
		}
		else
		{
			Control->setPaused(true);
		}
	}


	void Loop(int Count = -1)
	{
		Control->setLoopCount(Count);
	}

private:
	// 채널이 곧 사운드 재생방식에 대한 권한을 가집니다.
	FMOD::Channel* Control = nullptr;
};

// 설명 : 관리 선생님의 본스타일로 짜겠습니다.
class UEngineSound : public UEngineResources
{
public:
	// constrcuter destructer
	UEngineSound();
	~UEngineSound();

	// delete Function
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	// 동시재생 사운드기능을 제대로 이용하려면
	// FMOD도 system업데이트 해줘야 합니다.
	// 우리가 실제 돌려주는것과 같이.

	static void Load(std::string_view _Path);
	static void Load(std::string_view _Name, std::string_view _Path);
	static USoundPlayer Play(std::string_view _Name);
	static UEngineSound* Find(std::string_view _Name);
	static void Release();

	static void Update();

protected:

private:
	static std::map<std::string, UEngineSound*> Sounds;

	FMOD::Sound* SoundHandle;

	bool ResLoad(std::string_view _Path);
};

