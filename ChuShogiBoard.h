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
	bool Move(int x1, int y1, int x2, int y2, int x3, int y3);
	bool IsMovePossible(int oldX, int oldY, int newX, int newY);

protected:

private:

	PieceType _initialSetup[12][12] = {
	{Lance, FerociousLeopard, Copper, Silver, Gold, Elephant, King, Gold, Silver, Copper, FerociousLeopard, Lance},
	{Cannon, None, Bishop, None, BlindTiger, Kylin, Phoenix, BlindTiger, None, Bishop, None, Cannon},
	{SideMover, VerticalMover, Rook, DragonHorse, DragonKing, Queen, Lion, DragonKing, DragonHorse, Rook, VerticalMover, SideMover},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, Cobra, None, None, None, None, Cobra, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, Cobra, None, None, None, None, Cobra, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{SideMover, VerticalMover, Rook, DragonHorse, DragonKing, Lion, Queen, DragonKing, DragonHorse, Rook, VerticalMover, SideMover},
	{Cannon, None, Bishop, None, BlindTiger, Phoenix, Kylin, BlindTiger, None, Bishop, None, Cannon},
	{Lance, FerociousLeopard, Copper, Silver, Gold, King, Elephant, Gold, Silver, Copper, FerociousLeopard, Lance}
	};
};
