#include "PreCompile.h"
#include "Bomb.h"

ABomb::ABomb()
{
	SetActorScale({ 50, 50 });
}

ABomb::~ABomb()
{
}

void ABomb::Tick(float _DeltaTime)
{
	AddActorLocation(FVector2D::ZERO * _DeltaTime * 500.0f);
}