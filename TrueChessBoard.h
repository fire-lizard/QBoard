#pragma once
#include "ChessBoard.h"

class TrueChessBoard : public ChessBoard
{
public:
	TrueChessBoard();
	virtual ~TrueChessBoard();
	void GetMoves(Piece *piece, int x, int y) override;

protected:

private:
};

