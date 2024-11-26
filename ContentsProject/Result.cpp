#include "PreCompile.h"
#include "Result.h"

#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"


AResult::AResult()
{
	STAGECLEAR = CreateDefaultSubObject<USpriteRenderer>();
	STAGECLEAR->SetSprite("01_StageClear");
	STAGECLEAR->SetOrder(ERenderOrder::UI_OVERFADE);
	STAGECLEAR->SetSpriteScale(1.0f);
	STAGECLEAR->SetPivotType(PivotType::Top);
	STAGECLEAR->SetComponentLocation({303, 67});
	STAGECLEAR->CreateAnimation("StageClear", "01_StageClear", 0, 5, 0.15f, true);
	STAGECLEAR->ChangeAnimation("StageClear");

	RESULTINFO = CreateDefaultSubObject<USpriteRenderer>();
	RESULTINFO->SetSprite("STAGECLEAR_INFO.png");
	RESULTINFO->SetOrder(ERenderOrder::UI_OVERFADE);
	RESULTINFO->SetSpriteScale(1.0f);
	RESULTINFO->SetPivotType(PivotType::Center);
	RESULTINFO->SetComponentLocation(RESULTINFO->GetComponentScale().Half());

};


AResult::~AResult()
{

};

void AResult::BeginPlay()
{
	Super::BeginPlay();
}


void AResult::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
