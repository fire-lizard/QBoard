#pragma once
#include "Board.h"
#include "ChessPiece.h"

class ChessBoard : public Board
{
public:
	ChessBoard();
	virtual ~ChessBoard();
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false) override;
	void GetMoves(Piece *piece, int x, int y) override;

protected:

	PieceType _initialSetup[8][8] = {
		{ Rook, WhiteHorse, Bishop, King, Queen, Bishop, WhiteHorse, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, WhiteHorse, Bishop, King, Queen, Bishop, WhiteHorse, Rook }
	};

private:
};
