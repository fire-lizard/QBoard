#pragma once
#include "ShatranjBoard.h"
class SittuyinBoard : public ShatranjBoard
{
public:
	SittuyinBoard();
	~SittuyinBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
private:

	PieceType _initialSetup[8][8] = {
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, Pawn, Pawn, Pawn, Pawn },
		{ Pawn, Pawn, Pawn, Pawn, None, None, None, None },
		{ None, None, None, None, Pawn, Pawn, Pawn, Pawn },
		{ Pawn, Pawn, Pawn, Pawn, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None }
	};
};
