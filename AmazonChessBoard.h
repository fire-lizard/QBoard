#pragma once
#include "ChessBoard.h"
class AmazonChessBoard : public ChessBoard
{
public:
	AmazonChessBoard();
	~AmazonChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;

private:

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
};
