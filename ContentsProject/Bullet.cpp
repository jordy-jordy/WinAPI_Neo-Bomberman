#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
	SetActorScale({ 20, 20 });
}

ABullet::~ABullet()
{
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(FVector2D::RIGHT * _DeltaTime * 500.0f);
}