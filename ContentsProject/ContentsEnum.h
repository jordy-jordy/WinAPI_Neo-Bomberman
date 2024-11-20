#pragma once

enum class ERenderOrder
{
	BACKGROUND0 = -2000,
	BACKGROUND1 = -1000,
	COLMAP = -999,
	BOMB = -700,
	OBJECTS = -500,
	PLAYER = 0,
	UI = 10000,
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
