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
	Chess, Xiangqi, Shogi, ShoShogi, ChuShogi, MiniShogi, JudkinShogi
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
	None = 0, King = 1, Lion = 2, Queen = 3, DragonKing = 4, DragonHorse = 5, Rook = 6, Bishop = 7, Knight = 8,
	VerticalMover = 9, SideMover = 10, Cannon = 11, Lance = 12, Kylin = 13, Phoenix = 14, Elephant = 15,
	BlindTiger = 16, Gold = 17, Silver = 18, Copper = 19, FerociousLeopard = 20, Cobra = 21, Pawn = 22,
	Eagle = 23, Unicorn = 24, NarrowQueen = 25, SleepingQueen = 26, FlyingStag = 27, WhiteHorse = 28, Whale = 29,
	// Promoted Shogi pieces
	PromotedLance = 30, PromotedKnight = 31, PromotedSilver = 32, Tokin = 33,
	// Dai Shogi pieces
	ViolentOxen = 34, FlyingDragon = 35, AngryBoar = 36, CatSword = 37, EvilWolf = 38, Iron = 39, Stone = 40
};

enum Direction
{
	NorthWest, North, NorthEast, East, SouthEast, South, SouthWest, West
};
