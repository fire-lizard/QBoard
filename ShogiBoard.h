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
	virtual void SetDrops(bool hasDrops);
	void WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2, char promotion, bool capture);
	std::string GetPSN();
	std::string GetCSA();
	std::string GetKIF();
	std::string GetKI2();

protected:
	bool _hasDrops;

private:
	std::string _psn;
	std::string _csa;
	std::string _kif;
	std::string _ki2;
	int _oldX2 = -1;
	int _oldY2 = -1;
	const std::string _promotionStr = "成";
	const std::string _dropStr = "打";
	const std::string _sameCoordStr = "同";
	const std::string _senteStr = "▲";
	const std::string _goteStr = "△";

	const std::map<PieceType, std::string> _pieceToPSN = {
		{Pawn, "P"},
		{Rook, "R"},
		{Knight, "N"},
		{Bishop, "B"},
		{Queen, "Q"},
		{King, "K"},
		{Lance, "L"},
		{Gold, "G"},
		{Silver, "S"},
		{Elephant, "E"},
		{Prince, "+E"},
		{DragonKing, "+R"},
		{DragonHorse, "+B"},
		{Tokin, "+P"},
		{PromotedLance, "+L"},
		{PromotedKnight, "+N"},
		{PromotedSilver, "+S"}
	};

	const std::map<PieceType, std::string> _pieceToCSA = {
		{Pawn, "FU"},
		{Rook, "HI"},
		{Knight, "KE"},
		{Bishop, "KA"},
		{King, "OU"},
		{Lance, "KY"},
		{Gold, "KI"},
		{Silver, "GI"},
		{Elephant, "SZ"},
		{Prince, "TS"},
		{DragonKing, "RY"},
		{DragonHorse, "UM"},
		{Tokin, "TO"},
		{PromotedLance, "NY"},
		{PromotedKnight, "NK"},
		{PromotedSilver, "NG"}
	};

	const std::map<PieceType, std::string> _pieceToKIF = {
		{Pawn, "歩"},
		{Rook, "飛"},
		{Knight, "桂"},
		{Bishop, "角"},
		{King, "玉"},
		{Lance, "香"},
		{Gold, "金"},
		{Silver, "銀"},
		{Elephant, "酔"},
		{Prince, "太"},
		{DragonKing, "龍"},
		{DragonHorse, "馬"},
		{Tokin, "と"},
		{PromotedLance, "杏"},
		{PromotedKnight, "圭"},
		{PromotedSilver, "全"}
	};

	const std::map<int, std::string> _numberToKanji = {
		{1, "一"},
		{2, "二"},
		{3, "三"},
		{4, "四"},
		{5, "五"},
		{6, "六"},
		{7, "七"},
		{8, "八"},
		{9, "九"}
	};

	PieceType _initialSetup[9][9] = {
		{ Lance, Knight, Silver, Gold, King, Gold, Silver, Knight, Lance },
		{ None, Rook, None, None, None, None, None, Bishop, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, Bishop, None, None, None, None, None, Rook, None },
		{ Lance, Knight, Silver, Gold, King, Gold, Silver, Knight, Lance }
	};
};
