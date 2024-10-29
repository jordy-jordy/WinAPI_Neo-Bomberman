#pragma once
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

class BombmanCore : public UContentsCore
{
public:
	BombmanCore();
	~BombmanCore();

	BombmanCore(const BombmanCore& _Other) = delete;
	BombmanCore(BombmanCore&& _Other) noexcept = delete;
	BombmanCore& operator=(const BombmanCore& _Other) = delete;
	BombmanCore& operator=(BombmanCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel;
};

