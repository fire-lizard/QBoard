#pragma once
#include <unordered_map>
#include "Common.h"
#include "DaiShogiPiece.h"

class TenjikuShogiPiece : public DaiShogiPiece
{
public:
	TenjikuShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~TenjikuShogiPiece() override;
	std::string GetImageFileName() const override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetKanjiImageFileName() override;
	static PieceType FromStringCode(const std::string& code);
};

