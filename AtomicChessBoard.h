#pragma once
#include "ChessBoard.h"
class AtomicChessBoard : public ChessBoard
{
public:
	AtomicChessBoard();
	~AtomicChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;

private:
	void Explode(int x, int y);

	PieceType _initialSetup[8][8] = {
		{ Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook }
	};
};
