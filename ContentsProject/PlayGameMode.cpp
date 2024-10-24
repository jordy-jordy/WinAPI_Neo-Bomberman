#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

// 언리얼에서는 MainPawn 주인공 무조건 지정하게 해요.
void APlayGameMode::BeginPlay()
{
	// 플레이어가 만들어져 있다면. BeginPlay();
	// 감안하고 짜셔야 합니다.


	// GetWorld()->SpawnActor<BackGround>();

	// GetWorld()->SpawnActor<Monster>();

	// 플레이어를 만들필요가 없게 되었다.
	// MainPawn을 지정하는 방식으로 가기로 했으므로.
	// GetWorld()->SpawnActor<Player>();

	// 우린 GUI에디터도 없고 저장했다가
	// 그걸 읽어서 
	// 다 코드로 쳐야한다.
	// 주인공 

	int a = 0;
}
