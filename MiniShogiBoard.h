#pragma once
#include "ShogiBoard.h"
#include "ShogiPiece.h"

class MiniShogiBoard : public ShogiBoard
{
public:
	MiniShogiBoard();
	~MiniShogiBoard() override;
	void Initialize() override;

private:

	PieceType _initialSetup[5][5] = {
		{ Rook, Bishop, Silver, Gold, King },
		{ None, None, None, None, Pawn },
		{ None, None, None, None, None },
		{ Pawn, None, None, None, None },
		{ King, Gold, Silver, Bishop, Rook }
	};
};
