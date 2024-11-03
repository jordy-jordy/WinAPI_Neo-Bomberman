#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UTitleLogo : public AActor
{
public:
	// constrcuter destructer
	UTitleLogo();
	~UTitleLogo();

	// delete Function
	UTitleLogo(const UTitleLogo& _Other) = delete;
	UTitleLogo(UTitleLogo&& _Other) noexcept = delete;
	UTitleLogo& operator=(const UTitleLogo& _Other) = delete;
	UTitleLogo& operator=(UTitleLogo&& _Other) noexcept = delete;

protected:

private:

};

