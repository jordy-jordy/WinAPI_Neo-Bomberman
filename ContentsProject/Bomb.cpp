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
	// 몇 초후에 폭탄이 사라지는 것을 구현하기 위해선 DeathTime 같은 변수 선언이 필요하다.
}