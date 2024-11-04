#pragma once
#include <EngineCore/GameMode.h>

#include "ATileMap.h"

// Ό³Έν :
class ATileMapGameMode : public AGameMode
{
public:
	enum class ATiles
	{
		Background = 0,
		Object_Broken = 1,
		Object_Unbroken = 2,
		Max
	};

	// constrcuter destructer
	ATileMapGameMode();
	~ATileMapGameMode();

	// delete Function
	ATileMapGameMode(const ATileMapGameMode& _Other) = delete;
	ATileMapGameMode(ATileMapGameMode&& _Other) noexcept = delete;
	ATileMapGameMode& operator=(const ATileMapGameMode& _Other) = delete;
	ATileMapGameMode& operator=(ATileMapGameMode&& _Other) noexcept = delete;

	ATiles CurrentTileType = ATiles::Background;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	ATileMap* WallTileMap = nullptr;
	ATileMap* GroundTileMap = nullptr;

};

