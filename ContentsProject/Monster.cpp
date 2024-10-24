#include "PreCompile.h"
#include "Monster.h"
#include <EngineCore/EngineAPICore.h>

AMonster::AMonster()
{
	SetActorLoaction({ 100, 100 });
	SetActorScale({ 100, 100 });
};

AMonster::~AMonster()
{

};

void AMonster::BeginPlay()
{
}

void AMonster::Tick()
{
	AddActorLoaction(FVector2D::DOWN * 0.0001f);
}