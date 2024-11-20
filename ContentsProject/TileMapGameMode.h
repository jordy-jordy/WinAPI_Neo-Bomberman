#pragma once
#include <EngineCore/GameMode.h>

#include "ATileMap.h"
#include "ContentsEnum.h"

// Ό³Έν :
class ATileMapGameMode : public AGameMode
{
public:

	// constrcuter destructer
	ATileMapGameMode();
	~ATileMapGameMode();

	// delete Function
	ATileMapGameMode(const ATileMapGameMode& _Other) = delete;
	ATileMapGameMode(ATileMapGameMode&& _Other) noexcept = delete;
	ATileMapGameMode& operator=(const ATileMapGameMode& _Other) = delete;
	ATileMapGameMode& operator=(ATileMapGameMode&& _Other) noexcept = delete;

	ATiles CurrentTileType = ATiles::Object_Broken;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	ATileMap* WallTileMap = nullptr;
	ATileMap* GroundTileMap = nullptr;
	

};

