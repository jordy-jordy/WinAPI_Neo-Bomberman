#include "PreCompile.h"
#include "Portal.h"
#include "ATileMap.h"

#include <EngineCore/SpriteRenderer.h>

APortal::APortal()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 32, 32 });
	SpriteRenderer->SetPivot({ 0, 0 });

	SpriteRenderer->CreateAnimation("Portal_OFF", "OFF", 0, 1, 0.2f, true);
	SpriteRenderer->CreateAnimation("Portal_ON_0", "ON_00", 0, 5, 0.2f, false);
	SpriteRenderer->CreateAnimation("Portal_ON_1", "ON_01", 0, 2, 0.2f, true);

	SpriteRenderer->SetOrder(ERenderOrder::PORTAL);


};

APortal::~APortal()
{

};

void APortal::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//SpriteRenderer->SetOrder(GetActorLocation().Y - WallTileMap->GetActorLocation().Y);

	switch (CurPortalState)
	{
	case PortalState::OFF:
		PORTAL_OFF();
		break;
	case PortalState::ON0:
		PORTAL_ON_0();
		break;
	case PortalState::ON1:
		PORTAL_ON_1();
		break;
	default:
		break;
	}

}

bool APortal::PORTAL_SWITCH(bool _OnOff)
{
	ISPORTAL_ON = _OnOff;
	return ISPORTAL_ON;
}

void APortal::ChangeState(PortalState _CurPortalState)
{
	switch (_CurPortalState)
	{
	case PortalState::OFF:
		break;
	case PortalState::ON0:
		break;
	case PortalState::ON1:
		break;
	default:
		break;
	}
	CurPortalState = _CurPortalState;
}

void APortal::PORTAL_OFF()
{
	SpriteRenderer->ChangeAnimation("Portal_OFF");

	if (ISPORTAL_ON == true)
	{
		ChangeState(PortalState::ON0);
	}
}

void APortal::PORTAL_ON_0()
{
	SpriteRenderer->ChangeAnimation("Portal_ON_0");

	if (SpriteRenderer->IsCurAnimationEnd() == true)
	{
		ChangeState(PortalState::ON1);
	}
}

void APortal::PORTAL_ON_1()
{
	SpriteRenderer->ChangeAnimation("Portal_ON_1");

	if (SpriteRenderer->IsCurAnimationEnd() == true)
	{
		ISCANMOVE = true;
	}
}

