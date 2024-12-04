#pragma once
#include "ShogiVariantBoard.h"
#include "ShogiPiece.h"

class MiniShogiBoard : public ShogiVariantBoard
{
public:
	MiniShogiBoard();
	~MiniShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false) override;
    void GetMoves(Piece *piece, int x, int y) override;

protected:

private:

	PieceType _initialSetup[5][5] = {
		{ Rook, Bishop, Silver, Gold, King },
		{ None, None, None, None, Pawn },
		{ None, None, None, None, None },
		{ Pawn, None, None, None, None },
		{ King, Gold, Silver, Bishop, Rook }
	};
};
