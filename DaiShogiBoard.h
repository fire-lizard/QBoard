#pragma once
#include "Common.h"
#include "ChuShogiBoard.h"
#include "DaiShogiPiece.h"

class DaiShogiBoard : public ChuShogiBoard
{
public:
	DaiShogiBoard();
	~DaiShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;

protected:

private:

	PieceType _initialSetup[15][15] = {
	{Lance, Knight, Stone, Iron, Copper, Silver, Gold, King, Gold, Silver, Copper, Iron, Stone, Knight, Lance},
	{Cannon, None, CatSword, None, FerociousLeopard, None, BlindTiger, Elephant, BlindTiger, None, FerociousLeopard, None, CatSword, None, Cannon},
	{None, ViolentOx, None, AngryBoar, None, EvilWolf, Kylin, Lion, Kylin, EvilWolf, None, AngryBoar, None, ViolentOx, None},
	{Rook, FlyingDragon, SideMover, VerticalMover, Bishop, DragonHorse, DragonKing, Queen, DragonKing, DragonHorse, Bishop, VerticalMover, SideMover, FlyingDragon, Rook},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, None, Cobra, None, None, None, None, None, Cobra, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, Cobra, None, None, None, None, None, Cobra, None, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{Rook, FlyingDragon, SideMover, VerticalMover, Bishop, DragonHorse, DragonKing, Queen, DragonKing, DragonHorse, Bishop, VerticalMover, SideMover, FlyingDragon, Rook},
	{None, ViolentOx, None, AngryBoar, None, EvilWolf, Kylin, Lion, Kylin, EvilWolf, None, AngryBoar, None, ViolentOx, None},
	{Cannon, None, CatSword, None, FerociousLeopard, None, BlindTiger, Elephant, BlindTiger, None, FerociousLeopard, None, CatSword, None, Cannon},
	{Lance, Knight, Stone, Iron, Copper, Silver, Gold, King, Gold, Silver, Copper, Iron, Stone, Knight, Lance}
	};
};

