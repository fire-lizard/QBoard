#pragma once
#include "ShogiBoard.h"

class JudkinShogiBoard : public ShogiBoard
{
public:
	JudkinShogiBoard();
	~JudkinShogiBoard() override;
	void Initialize() override;

private:

	PieceType _initialSetup[6][6] = {
		{ Rook, Bishop, Knight, Silver, Gold, King },
		{ None, None, None, None, None, Pawn },
		{ None, None, None, None, None, None },
		{ None, None, None, None, None, None },
		{ Pawn, None, None, None, None, None },
		{ King, Gold, Silver, Knight, Bishop, Rook }
	};
};

