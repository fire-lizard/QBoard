#pragma once
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
};

