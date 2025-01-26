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
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	void WriteMove(const std::string& moveStr);
	std::string GetCastling();
	std::string GetEnPassant();
	int HalfMoveCount();
	void SetCastling(std::string val);
	void SetEnPassant(std::string val);

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
	int _halfMoveCount;
	std::string _ep = "-";
};
