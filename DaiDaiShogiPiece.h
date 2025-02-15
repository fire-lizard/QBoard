#pragma once
#include "Common.h"
#include "MakaDaiDaiShogiPiece.h"

class DaiDaiShogiPiece : public MakaDaiDaiShogiPiece
{
public:
	DaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~DaiDaiShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetKanjiImageFileName() override;
	static PieceType FromStringCode(const std::string& code);
};

