#pragma once
#include <unordered_map>
#include "Common.h"
#include "ChuShogiPiece.h"

class DaiShogiPiece : public ChuShogiPiece
{
public:
	DaiShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~DaiShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetKanjiImageFileName() override;
	static PieceType FromStringCode(const std::string& code);
};

