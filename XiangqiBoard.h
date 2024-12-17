#pragma once
#include "Board.h"

class XiangqiBoard : public Board
{
public:
	XiangqiBoard();
	~XiangqiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece *piece, int x, int y) override;

protected:

private:
	void CheckCannonDirection(const Piece *piece, int x, int y, Direction direction);

	PieceType _initialSetup[10][9] = {
		{ Rook, WhiteHorse, Elephant, Silver, King, Silver, Elephant, WhiteHorse, Rook },
		{ None, None, None, None, None, None, None, None, None },
		{ None, Cannon, None, None, None, None, None, Cannon, None },
		{ Pawn, None, Pawn, None, Pawn, None, Pawn, None, Pawn },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ Pawn, None, Pawn, None, Pawn, None, Pawn, None, Pawn },
		{ None, Cannon, None, None, None, None, None, Cannon, None },
		{ None, None, None, None, None, None, None, None, None },
		{ Rook, WhiteHorse, Elephant, Silver, King, Silver, Elephant, WhiteHorse, Rook }
	};
};

