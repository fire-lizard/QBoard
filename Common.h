#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

enum PieceColour
{
	White, Black
};

enum PieceType
{
	None = 0, King = 1, Lion = 2, Queen = 3, DragonKing = 4, DragonHorse = 5, Rook = 6, Bishop = 7,
	VerticalMover = 8, SideMover = 9, Cannon = 10, Lance = 11, Kylin = 12, Phoenix = 13, Elephant = 14,
	BlindTiger = 15, Gold = 16, Silver = 17, Copper = 18, FerociousLeopard = 19, Cobra = 20, Pawn = 21,
	Eagle = 22, Unicorn = 23, NarrowQueen = 24, SleepingQueen = 25, FlyingStag = 26, WhiteHorse = 27, Whale = 28
};

enum Direction
{
	NorthWest, North, NorthEast, East, SouthEast, South, SouthWest, West
};

#endif // COMMON_H_INCLUDED
