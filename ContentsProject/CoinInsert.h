#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class UCoinInsert : public AActor
{
public:
	// constrcuter destructer
	UCoinInsert();
	~UCoinInsert();

	// delete Function
	UCoinInsert(const UCoinInsert& _Other) = delete;
	UCoinInsert(UCoinInsert&& _Other) noexcept = delete;
	UCoinInsert& operator=(const UCoinInsert& _Other) = delete;
	UCoinInsert& operator=(UCoinInsert&& _Other) noexcept = delete;

	void SetScore_Coin(class AScore* _data)
	{
		COINs = _data;
	}

	class USpriteRenderer* MAINRENDERER = nullptr;
	class USpriteRenderer* COIN_INSERT = nullptr;
	class USpriteRenderer* LEVEL4 = nullptr;
	class USpriteRenderer* CREDIT = nullptr;
	class USpriteRenderer* COMPANY = nullptr;
	class USpriteRenderer* TM = nullptr;


protected:
	void BeginPlay();
	void Tick(float _DeltaTime);

private:
	class AScore* COINs = nullptr;

	class ATitleGameMode* MODE = nullptr;

	int COIN_NUMBER = 0;

};
