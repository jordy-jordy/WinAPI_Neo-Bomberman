#pragma once

enum class ERenderOrder
{
	BACKGROUND0 = -2000,
	BACKGROUND1 = -1000,
	COLMAP = -999,
	OBJECTS = -500,
	PLAYER = 0,
	UI = 10000,
};

enum class ATiles
{
	Background = 0,
	Object_Broken = 1,
	Object_Unbroken = 2,
	Object_Portal = 3,
	Player_Spawn = 4,
	Max
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
};

