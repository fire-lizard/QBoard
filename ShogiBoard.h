#pragma once
#include "Board.h"
#include "ShogiPiece.h"

class ShogiBoard : public Board
{
public:
	ShogiBoard();
	virtual ~ShogiBoard();
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false) override;
	void GetMoves(Piece *piece, int x, int y) override;
	void SetDrops(bool hasDrops);
	void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y);

protected:

private:
	bool _hasDrops;

	PieceType _initialSetup[9][9] = {
		{ Lance, WhiteHorse, Silver, Gold, King, Gold, Silver, WhiteHorse, Lance },
		{ None, Rook, None, None, None, None, None, Bishop, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, Bishop, None, None, None, None, None, Rook, None },
		{ Lance, WhiteHorse, Silver, Gold, King, Gold, Silver, WhiteHorse, Lance }
	};
};

