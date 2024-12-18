#pragma once
#include "Board.h"
#include "ChessPiece.h"

class ChessBoard : public Board
{
public:
	ChessBoard();
	~ChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece *piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY) override;

protected:

	PieceType _initialSetup[8][8] = {
		{ Rook, WhiteHorse, Bishop, Queen, King, Bishop, WhiteHorse, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, WhiteHorse, Bishop, Queen, King, Bishop, WhiteHorse, Rook }
	};

private:
};
