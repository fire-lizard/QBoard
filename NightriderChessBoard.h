#pragma once
#include "ChessBoard.h"

class NightriderChessBoard : public ChessBoard
{
public:
	NightriderChessBoard();
	~NightriderChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
	std::string GetStringCode(int x, int y) const override;

private:
	void CheckKnightDirection(const std::optional<Piece>& piece, int x, int y, Direction direction);
	static void CheckKnightDirectionInc(int& x, int& y, Direction direction);

	PieceType _initialSetup[8][8] = {
		{ Rook, Nightrider, Bishop, Queen, King, Bishop, Nightrider, Rook },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ Rook, Nightrider, Bishop, Queen, King, Bishop, Nightrider, Rook }
	};
};
