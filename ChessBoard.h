#pragma once
#include <map>
#include "ShatranjBoard.h"

class ChessBoard : public ShatranjBoard
{
public:
	ChessBoard();
	~ChessBoard() override;
	void Initialize() override;
	Board* Clone() override;
    void Promote(int x, int y, PieceType pt = None) override;
    void GetMoves(const std::optional<Piece>& piece, int x, int y) override;
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	std::string GetStringCode(int x, int y) const override;
	void WriteCastling(const std::string& moveStr);
	std::string GetCastling() const;
	std::string GetEnPassant();
	int HalfMoveCount() const;
	void SetHalfMoveCount(int halfMoveCount);
	void SetCastling(const std::string& val);
	void SetEnPassant(std::string val);

protected:

    bool _wkc = true;
	bool _wqc = true;
	bool _bkc = true;
	bool _bqc = true;
	int _halfMoveCount;
	std::string _ep = "-";

    virtual bool EnemyPawnsAround(int x, int y) const;

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
