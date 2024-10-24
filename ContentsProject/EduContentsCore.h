#pragma once
#include <EngineCore/EngineAPICore.h>

class EduContentsCore : public UContentsCore
{
public:
	EduContentsCore();
	~EduContentsCore();

	EduContentsCore(const EduContentsCore& _Other) = delete;
	EduContentsCore(EduContentsCore&& _Other) noexcept = delete;
	EduContentsCore& operator=(const EduContentsCore& _Other) = delete;
	EduContentsCore& operator=(EduContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel;
};

