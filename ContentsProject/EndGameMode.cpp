#include "PreCompile.h"
#include "EndGameMode.h"

#include "Ending.h"


AEndGameMode::AEndGameMode()
{
};

AEndGameMode::~AEndGameMode()
{

};

void AEndGameMode::BeginPlay()
{
	Super::BeginPlay();

	EndingCut = GetWorld()->SpawnActor<AEnding>();


}

void AEndGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

