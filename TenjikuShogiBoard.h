#pragma once
#include <queue>
#include <set>
#include "Common.h"
#include "DaiShogiBoard.h"
#include "TenjikuShogiPiece.h"

// A small helper struct for BFS states.
struct State
{
	int r, c, steps;
};

class TenjikuShogiBoard : public DaiShogiBoard
{
public:
	TenjikuShogiBoard();
	~TenjikuShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;

private:
	void CheckJump(const Piece* piece, int x, int y, Direction direction);
	void CheckIgui(const Piece* piece, int x, int y);
	void GetPossibleMoves(int x, int y);

	PieceType _jumpingPieces[4] = { GreatGeneral, ViceGeneral, BishopGeneral, RookGeneral };

	PieceType _initialSetup[16][16] = {
	{Lance, Knight, Leopard, Iron, Copper, Silver, Gold, Elephant, King, Gold, Silver, Copper, Iron, Leopard, Knight, Lance},
	{ReverseChariot, None, ChariotSoldier, ChariotSoldier, None, Tiger, Phoenix, Queen, Lion, Kylin, Tiger, None, ChariotSoldier, ChariotSoldier, None, ReverseChariot},
	{SideSoldier, VerticalSoldier, Bishop, DragonHorse, DragonKing, WaterBuffalo, FireDemon, FreeEagle, LionHawk, FireDemon, WaterBuffalo, DragonKing, DragonHorse, Bishop, VerticalSoldier, SideSoldier},
	{SideMover, VerticalMover, Rook, Unicorn, Eagle, BishopGeneral, RookGeneral, ViceGeneral, GreatGeneral, RookGeneral, BishopGeneral, Eagle, Unicorn, Rook, VerticalMover, SideMover},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, None, Dog, None, None, None, None, None, None, Dog, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, Dog, None, None, None, None, None, None, Dog, None, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{SideMover, VerticalMover, Rook, Unicorn, Eagle, BishopGeneral, RookGeneral, GreatGeneral, ViceGeneral, RookGeneral, BishopGeneral, Eagle, Unicorn, Rook, VerticalMover, SideMover},
	{SideSoldier, VerticalSoldier, Bishop, DragonHorse, DragonKing, WaterBuffalo, FireDemon, LionHawk, FreeEagle, FireDemon, WaterBuffalo, DragonKing, DragonHorse, Bishop, VerticalSoldier, SideSoldier},
	{ReverseChariot, None, ChariotSoldier, ChariotSoldier, None, Tiger, Kylin, Lion, Queen, Phoenix, Tiger, None, ChariotSoldier, ChariotSoldier, None, ReverseChariot},
	{Lance, Knight, Leopard, Iron, Copper, Silver, Gold, King, Elephant, Gold, Silver, Copper, Iron, Leopard, Knight, Lance}
	};
};

