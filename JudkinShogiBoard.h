#pragma once
#include "ShogiVariantBoard.h"

class JudkinShogiBoard : public ShogiVariantBoard
{
public:
	JudkinShogiBoard();
	~JudkinShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;

protected:

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

