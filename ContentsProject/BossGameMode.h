#pragma once

#include <EngineCore/GameMode.h>


// Ό³Έν :
class ABossGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ABossGameMode();
	~ABossGameMode();

	// delete Function
	ABossGameMode(const ABossGameMode& _Other) = delete;
	ABossGameMode(ABossGameMode&& _Other) noexcept = delete;
	ABossGameMode& operator=(const ABossGameMode& _Other) = delete;
	ABossGameMode& operator=(ABossGameMode&& _Other) noexcept = delete;

	void BeginPlay();


protected:
	void Tick(float _DeltaTime) override;


private:

};
