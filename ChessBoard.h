#pragma once
#include <map>
#include "ShatranjBoard.h"
#include "ChessPiece.h"

class ChessBoard : public ShatranjBoard
{
public:
	ChessBoard();
	~ChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece *piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY) override;
	void WriteMove(const std::string& moveStr);
	std::string Castling();
	std::string EnPassant();

protected:

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

private:
	bool _wkc = true;
	bool _wqc = true;
	bool _bkc = true;
	bool _bqc = true;
	std::string _ep = "-";
};
