#pragma once
#include "KanjiPiece.h"

class ShogiPiece : public KanjiPiece
{
public:
	ShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetKanjiImageFileName() override;
	std::string LongStringCode() const;
	static PieceType LongStringCode2PieceType(const std::string& longStringCode);

protected:

private:
};

