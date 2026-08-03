#pragma once
#include "ChessBoard.h"
class KnightmateChessBoard : public ChessBoard
{
public:
	KnightmateChessBoard();
	~KnightmateChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
	std::string GetStringCode(int x, int y) const override;

private:

	PieceType _initialSetup[8][8] = {
		{ Rook, Silver, Bishop, Queen, King, Bishop, Silver, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, Silver, Bishop, Queen, King, Bishop, Silver, Rook }
	};
};
