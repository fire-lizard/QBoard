#pragma once
#include <map>
#include "Common.h"
#include "ShatranjBoard.h"
#include "MakrukPiece.h"

class MakrukBoard : public ShatranjBoard
{
public:
	MakrukBoard();
	~MakrukBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;

protected:

	PieceType _initialSetup[8][8] = {
		{ Rook, Knight, Silver, Queen, King, Silver, Knight, Rook },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ Rook, Knight, Silver, Queen, King, Silver, Knight, Rook }
	};

private:
};

