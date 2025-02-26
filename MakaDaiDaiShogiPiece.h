#pragma once
#include <unordered_map>
#include "Common.h"
#include "DaiShogiPiece.h"

class MakaDaiDaiShogiPiece : public DaiShogiPiece
{
public:
	MakaDaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~MakaDaiDaiShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetKanjiImageFileName() override;
	std::string GetKanjiImageFileName2() override;
	static PieceType FromStringCode(const std::string& code);
};

