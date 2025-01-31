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
	void WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2, char promotion, bool capture) override;

protected:

	PieceType _initialSetup[8][8] = {
		{ Rook, Knight, Silver, Queen, King, Silver, Knight, Rook },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ Rook, Knight, Silver, King, Queen, Silver, Knight, Rook }
	};

private:
	const std::map<PieceType, char> _pieceToPGN = {
		{Pawn, 'P'},
		{Rook, 'R'},
		{Knight, 'N'},
		{Silver, 'S'},
		{Queen, 'M'},
		{King, 'K'}
	};
};

