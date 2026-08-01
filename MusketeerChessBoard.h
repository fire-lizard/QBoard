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

	int WhitePiecesToPlace = 2;
	int BlackPiecesToPlace = 2;
	// The Musketeer piece the last Move let onto the board, None if it let none. The engine has to
	// be told about it in the same move, so the caller reads it straight after moving.
	PieceType GatedPiece = None;

protected:
	bool EnemyPawnsAround(int x, int y) const override;

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
