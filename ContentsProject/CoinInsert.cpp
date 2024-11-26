#include "PreCompile.h"
#include "CoinInsert.h"

#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "TitleGameMode.h"

UCoinInsert::UCoinInsert()
{
	MAINRENDERER = CreateDefaultSubObject<USpriteRenderer>();
	MAINRENDERER->SetSprite("TITLE_04_COIN_INSERT_002.png");
	MAINRENDERER->SetOrder(ERenderOrder::BACKGROUND0);
	FVector2D MapScale = MAINRENDERER->SetSpriteScale(1.0f);
	MAINRENDERER->SetComponentLocation(MapScale.Half());

	COIN_INSERT = CreateDefaultSubObject<USpriteRenderer>();
	COIN_INSERT->SetSprite("TITLE_04_COIN_INSERT_000.png");
	COIN_INSERT->SetOrder(ERenderOrder::BACKGROUND0);
	COIN_INSERT->SetComponentScale({ 262, 28 });
	COIN_INSERT->SetComponentLocation(MapScale.Half());
	COIN_INSERT->CreateAnimation("COIN_INSERT", "04_COIN_INSERT", 0, 1, 0.3f, true);
	COIN_INSERT->ChangeAnimation("COIN_INSERT");
	COIN_INSERT->SetActive(true);
	
	COMPANY = CreateDefaultSubObject<USpriteRenderer>();
	COMPANY->SetSprite("Company_logo.png");
	COMPANY->SetOrder(ERenderOrder::BACKGROUND1);
	COMPANY->SetSpriteScale(1.0f);
	COMPANY->SetPivotType(PivotType::Top);
	COMPANY->SetComponentLocation({ 296, 384 });
	COMPANY->SetActive(true);

	TM = CreateDefaultSubObject<USpriteRenderer>();
	TM->SetSprite("TM.png");
	TM->SetOrder(ERenderOrder::BACKGROUND1);
	TM->SetSpriteScale(1.0f);
	TM->SetPivotType(PivotType::Top);
	TM->SetComponentLocation({ 512, 96 });
	TM->SetActive(true);
	
};

UCoinInsert::~UCoinInsert()
{

};

void UCoinInsert::BeginPlay()
{
	Super::BeginPlay();
}

void UCoinInsert::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (MODE == nullptr)
	{
		MODE = GetWorld()->GetGameMode<ATitleGameMode>();
	}

	int CURCOIN = MODE->GetCOIN_NUMBER();
	if (CURCOIN > 0)
	{
		COIN_INSERT->SetActive(false);
	}
}

