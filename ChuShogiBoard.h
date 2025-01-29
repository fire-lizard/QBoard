#pragma once
#include "Board.h"
#include "ChuShogiPiece.h"

class ChuShogiBoard : public Board
{
public:
	ChuShogiBoard();
	~ChuShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece *piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	bool LionMove(int x1, int y1, int x2, int y2, int x3, int y3);
	bool IsMovePossible(int x, int y);

protected:
	void CheckNullMove(int x, int y);

private:
	bool _wasLionCapturedByNonLion = false;

	PieceType _initialSetup[12][12] = {
	{Lance, Leopard, Copper, Silver, Gold, Elephant, King, Gold, Silver, Copper, Leopard, Lance},
	{Cannon, None, Bishop, None, Tiger, Phoenix, Kylin, Tiger, None, Bishop, None, Cannon},
	{SideMover, VerticalMover, Rook, DragonHorse, DragonKing, Queen, Lion, DragonKing, DragonHorse, Rook, VerticalMover, SideMover},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, GoBetween, None, None, None, None, GoBetween, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, GoBetween, None, None, None, None, GoBetween, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{SideMover, VerticalMover, Rook, DragonHorse, DragonKing, Lion, Queen, DragonKing, DragonHorse, Rook, VerticalMover, SideMover},
	{Cannon, None, Bishop, None, Tiger, Kylin, Phoenix, Tiger, None, Bishop, None, Cannon},
	{Lance, Leopard, Copper, Silver, Gold, King, Elephant, Gold, Silver, Copper, Leopard, Lance}
	};
};
