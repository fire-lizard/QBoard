#pragma once
#include "ChessBoard.h"
class CylinderChessBoard : public ChessBoard
{
public:
	CylinderChessBoard();
	~CylinderChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
	void GetMoves(const std::optional<Piece>& piece, int x, int y) override;

protected:
	bool EnemyPawnsAround(int x, int y) const override;

private:
	int Wrap(int x) const;
	void CheckWrappedMove(const std::optional<Piece>& piece, int x, int y);
	void CheckWrappedDirection(const std::optional<Piece>& piece, int x, int y, Direction direction);

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
