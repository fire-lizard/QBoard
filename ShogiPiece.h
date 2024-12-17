#pragma once
#include "ChuShogiPiece.h"

class ShogiPiece : public ChuShogiPiece
{
public:
	ShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string AsianStringCode() override;
	std::string GetJapaneseImageFileName() override;

protected:

private:
};

