#pragma once
#include "Common.h"
#include "ShogiBoard.h"
#include "WaShogiPiece.h"

class WaShogiBoard : public ShogiBoard
{
public:
	WaShogiBoard();
	~WaShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;
	void SetDrops(bool hasDrops) override;

protected:

private:

	PieceType _initialSetup[11][11] = {
		{ LiberatedHorse, ClimbingMonkey, SwoopingOwl, FlyingCock, Silver, King, Gold, FlyingGoose, StruttingCrow, BlindDog, Lance },
		{ None, CloudEagle, None, None, None, SideMover, None, None, None, FlyingFalcon, None },
		{ Pawn, Pawn, Pawn, RunningRabbit, Pawn, Pawn, Pawn, TreacherousFox, Pawn, Pawn, Pawn },
		{ None, None, None, Pawn, None, None, None, Pawn, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, Pawn, None, None, None, Pawn, None, None, None },
		{ Pawn, Pawn, Pawn, TreacherousFox, Pawn, Pawn, Pawn, RunningRabbit, Pawn, Pawn, Pawn },
		{ None, FlyingFalcon, None, None, None, SideMover, None, None, None, CloudEagle, None },
		{ Lance, BlindDog, StruttingCrow, FlyingGoose, Gold, King, Silver, FlyingCock, SwoopingOwl, ClimbingMonkey, LiberatedHorse }
	};
};

