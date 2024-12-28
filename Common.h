#pragma once

enum EngineProtocol
{
	XBoard, UCI, UCCI, Qianhong, USI
};

enum GameFormat
{
	PGN, WXF, PSN, CSA, KIF
};

enum GameVariant
{
	Chess, Xiangqi, Shogi, ShoShogi, ChuShogi, MiniShogi
};

enum PieceColour
{
	White, Black
};

enum PieceStyle
{
	European, Asian
};

enum EngineOutput
{
	Concise, Verbose
};

enum PieceType
{
	None = 0, King = 1, Lion = 2, Queen = 3, DragonKing = 4, DragonHorse = 5, Rook = 6, Bishop = 7,
	VerticalMover = 8, SideMover = 9, Cannon = 10, Lance = 11, Kylin = 12, Phoenix = 13, Elephant = 14,
	BlindTiger = 15, Gold = 16, Silver = 17, Copper = 18, FerociousLeopard = 19, Cobra = 20, Pawn = 21,
	Eagle = 22, Unicorn = 23, NarrowQueen = 24, SleepingQueen = 25, FlyingStag = 26, WhiteHorse = 27, Whale = 28,
	ViolentOxen = 29, FlyingDragon = 30, AngryBoar = 31, CatSword = 32, EvilWolf = 33, Iron = 34, Stone = 35
};

enum Direction
{
	NorthWest, North, NorthEast, East, SouthEast, South, SouthWest, West
};
