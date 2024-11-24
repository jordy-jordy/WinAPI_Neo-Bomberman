#include "PreCompile.h"
#include "ChooseStage.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


UChooseStage::UChooseStage()
{
	Background = CreateDefaultSubObject<USpriteRenderer>();
	Background->SetSprite("00_BASIC.png");
	Background->SetSpriteScale(1.0f);
	Background->SetComponentLocation(BG_SIZE.Half());
	Background->SetOrder(ERenderOrder::BACKGROUND0);

	Basic_UI00 = CreateDefaultSubObject<USpriteRenderer>();
	Basic_UI00->SetSprite("01_BASIC.png");
	Basic_UI00->SetSpriteScale(1.0f);
	Basic_UI00->SetComponentLocation(BG_SIZE.Half());
	Basic_UI00->SetOrder(ERenderOrder::BACKGROUND1);

	Basic_UI01 = CreateDefaultSubObject<USpriteRenderer>();
	Basic_UI01->SetSprite("02_BASIC.png");
	Basic_UI01->SetSpriteScale(1.0f);
	Basic_UI01->SetComponentLocation(BG_SIZE.Half());
	Basic_UI01->SetOrder(ERenderOrder::BACKGROUND2);

	CHOOSE_00 = CreateDefaultSubObject<USpriteRenderer>();
	CHOOSE_00->SetSprite("INFO_STAGE_01_02.png");
	CHOOSE_00->SetSpriteScale(1.0f);
	CHOOSE_00->SetPivotType(PivotType::Top);
	CHOOSE_00->SetComponentLocation({352, 176});
	CHOOSE_00->SetOrder(ERenderOrder::BACKGROUND3);
	CHOOSE_00->SetActive(true);

	CHOOSE_01 = CreateDefaultSubObject<USpriteRenderer>();
	CHOOSE_01->SetSprite("INFO_STAGE_02_02.png");
	CHOOSE_01->SetSpriteScale(1.0f);
	CHOOSE_01->SetPivotType(PivotType::Top);
	CHOOSE_01->SetComponentLocation({ 352, 336 });
	CHOOSE_01->SetOrder(ERenderOrder::BACKGROUND3);
	CHOOSE_01->SetActive(false);

	BLACKMAN = CreateDefaultSubObject<USpriteRenderer>();
	BLACKMAN->SetSprite("05_CHOOSE_STAGE_01_CHA_BLK");
	BLACKMAN->SetSpriteScale(1.0f);
	BLACKMAN->SetPivotType(PivotType::Top);
	BLACKMAN->SetComponentLocation({ 379, 16 });
	BLACKMAN->SetOrder(ERenderOrder::OBJECTS);
	BLACKMAN->CreateAnimation("BLKMAN", "05_CHOOSE_STAGE_01_CHA_BLK", 0, 5, 0.15f, true);
	BLACKMAN->ChangeAnimation("BLKMAN");

	BOMB_MAN = CreateDefaultSubObject<USpriteRenderer>();
	BOMB_MAN->SetSprite("03_BASIC.png");
	BOMB_MAN->SetSpriteScale(1.0f);
	BOMB_MAN->SetPivotType(PivotType::Top);
	BOMB_MAN->SetComponentLocation({ 65, 194 });
	BOMB_MAN->SetOrder(ERenderOrder::OBJECTS);

	BOMB_MAN->CreateAnimation("MOVE", "05_CHOOSE_STAGE_03_CHA_MOVE", 0, 3, 0.2f, true);
	BOMB_MAN->CreateAnimation("DRAW", "05_CHOOSE_STAGE_02_CHA_DRAW", 0, 9, 0.1f, false);
	BOMB_MAN->CreateAnimation("BACK", "05_CHOOSE_STAGE_03_CHA_MOVE", 4, 4, 0.1f, false);
	BOMB_MAN->ChangeAnimation("MOVE");

};

UChooseStage::~UChooseStage()
{

};