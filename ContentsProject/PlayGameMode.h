#pragma once

#include <EngineCore/GameMode.h>


// Ό³Έν :
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void BeginPlay();

	FVector2D WindowSize = { 608, 448 };
	FVector2D WallTileMapLocation = { 96, 64 };

	bool IsMonsterAllDead();

	void PlusScore(int _Score)
	{
		PlayerScore += _Score;
	}

	int GetScore()
	{
		return PlayerScore;
	}


protected:
	void Tick(float _DeltaTime) override;
	void PlayerInit();
	void PlayTileMapInit();
	void MonsterInit();
	void PortalInit();
	void PortalON();
	void MOVETO_BOSS();

private:
	class ATileMap* WallTileMap = nullptr;
	class APortal* Portal = nullptr;

	USpriteRenderer* SpriteRendererSTAGE = nullptr;

	USpriteRenderer* SpriteRendererSPAWN = nullptr;
	USpriteRenderer* SpriteRendererPORTAL = nullptr;
	
	class AScore* Minute = nullptr;
	class AScore* Second = nullptr;
	class AScore* Zero = nullptr;
	class AScore* Score = nullptr;

	float Time = 181.0f;

	int PlayerScore = 0;
};

