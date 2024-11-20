#pragma once
#include <EngineCore/Actor.h>


enum class PortalState
{
	OFF,
	ON0,
	ON1
};

// Ό³Έν :
class APortal : public AActor
{
public:
	// constrcuter destructer
	APortal();
	~APortal();

	// delete Function
	APortal(const APortal& _Other) = delete;
	APortal(APortal&& _Other) noexcept = delete;
	APortal& operator=(const APortal& _Other) = delete;
	APortal& operator=(APortal&& _Other) noexcept = delete;

	bool PORTAL_SWITCH(bool _OnOff);
	void SetWallTileMap(class ATileMap* _TileMap)
	{
		WallTileMap = _TileMap;
	}

	bool GET_ISCANMOVE()
	{
		return ISCANMOVE;
	}


protected:
	void Tick(float _DeltaTime) override;

private:
	ATileMap* WallTileMap = nullptr;
	class USpriteRenderer* SpriteRenderer;

	PortalState CurPortalState = PortalState::OFF;
	void ChangeState(PortalState _CurPortalState);

	bool ISPORTAL_ON = false;
	bool ISCANMOVE = false;

	void PORTAL_OFF();
	void PORTAL_ON_0();
	void PORTAL_ON_1();


};
