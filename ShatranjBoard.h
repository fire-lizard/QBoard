#pragma once
#include <map>
#include "Common.h"
#include "Board.h"
#include "ShatranjPiece.h"

class ShatranjBoard : public Board
{
public:
	ShatranjBoard();
	~ShatranjBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;
	virtual void WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2, char promotion, bool capture);
	std::string GetPGN();

protected:
	std::string _pgn;

	PieceType _initialSetup[8][8] = {
		{ Rook, Knight, Bishop, King, Queen, Bishop, Knight, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, Knight, Bishop, King, Queen, Bishop, Knight, Rook }
	};

private:
	const std::map<PieceType, char> _pieceToPGN = {
		{Pawn, 'P'},
		{Rook, 'R'},
		{Knight, 'N'},
		{Bishop, 'B'},
		{Queen, 'Q'},
		{King, 'K'}
	};
};

