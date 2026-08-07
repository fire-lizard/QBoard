#pragma once
#include "CapablancaChessBoard.h"

class FalconChessBoard : public CapablancaChessBoard
{
public:
	FalconChessBoard();
	~FalconChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
	std::string GetStringCode(int x, int y) const override;

private:
	void CheckFalconMove(const std::optional<Piece>& piece, int x, int y, int dx, int dy);

	PieceType _initialSetup[8][10] = {
		{ Rook, Knight, Bishop, Falcon, Queen, King, Falcon, Bishop, Knight, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, Knight, Bishop, Falcon, Queen, King, Falcon, Bishop, Knight, Rook }
	};
};
