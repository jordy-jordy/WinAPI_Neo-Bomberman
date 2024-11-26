#pragma once

enum class ERenderOrder
{
	BACKGROUND0 = -2000,
	BACKGROUND1 = -1000,
	BACKGROUND3 = -900,
	BACKGROUND2 = -800,
	BOMB = -600,
	OBJECTS = -500,
	PORTAL = -400,
	PLAYER = 0,
	UI = 10000,
	TEXT_UI = 12000,
	FADE = 20000,
	UI_OVERFADE = 21000
};

enum class AStageTiles
{
	NONE0 = 0,
	Object_Broken = 1,
	Object_Unbroken = 2,
	Object_Portal = 3,
	Player_Spawn = 4,
	Max,
	Background = 6,
	Object_Bomb = 7
};

enum class ABossTiles
{
	NONE0 = 0,
	NONE1 = 1,
	Wall = 2,
	NONE2 = 3,
	Player_Spawn = 4,
	Max,
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
};

enum class Direction
{
	NONE = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4,
	MAX
};
