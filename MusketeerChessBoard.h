#pragma once
#include "PieceStorage.h"
#include "CapablancaChessBoard.h"

class MusketeerChessBoard : public CapablancaChessBoard, public PieceStorage
{
public:
	MusketeerChessBoard();
	~MusketeerChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	std::string GetStringCode(int x, int y) const override;

private:

	PieceType _initialSetup[10][8] = {
		{ None, None, None, None, None, None, None, None },
		{ Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook },
		{ None, None, None, None, None, None, None, None }
	};
};
