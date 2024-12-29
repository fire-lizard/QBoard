#pragma once
#include <map>
#include "ShogiVariantBoard.h"
#include "ShogiPiece.h"

class ShogiBoard : public ShogiVariantBoard
{
public:
	ShogiBoard();
	~ShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
    void GetMoves(Piece *piece, int x, int y) override;
	void SetDrops(bool hasDrops);

protected:

private:
	bool _hasDrops;

	const std::map<PieceType, std::string> _pieceToPSN = {
		{Pawn, "P"},
		{Rook, "R"},
		{WhiteHorse, "N"},
		{Bishop, "B"},
		{Queen, "Q"},
		{King, "K"},
		{Lance, "L"},
		{Gold, "G"},
		{Silver, "S"},
		{DragonKing, "+R"},
		{DragonHorse, "+B"}
	};

	const std::map<PieceType, std::string> _pieceToCSA = {
		{Pawn, "FU"},
		{Rook, "HI"},
		{WhiteHorse, "KE"},
		{Bishop, "KA"},
		{King, "OU"},
		{Lance, "KY"},
		{Gold, "KI"},
		{Silver, "GI"},
		{DragonKing, "RY"},
		{DragonHorse, "UM"}
	};

	const std::map<PieceType, std::string> _pieceToKIF = {
		{Pawn, "歩"},
		{Rook, "飛"},
		{WhiteHorse, "桂"},
		{Bishop, "角"},
		{King, "王"},
		{Lance, "香"},
		{Gold, "金"},
		{Silver, "銀"},
		{DragonKing, "竜"},
		{DragonHorse, "馬"}
	};

	PieceType _initialSetup[9][9] = {
		{ Lance, WhiteHorse, Silver, Gold, King, Gold, Silver, WhiteHorse, Lance },
		{ None, Rook, None, None, None, None, None, Bishop, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, Bishop, None, None, None, None, None, Rook, None },
		{ Lance, WhiteHorse, Silver, Gold, King, Gold, Silver, WhiteHorse, Lance }
	};
};

