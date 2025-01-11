#pragma once
#include "Common.h"
#include "KanjiPiece.h"

class WaShogiPiece : public KanjiPiece
{
public:
	WaShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~WaShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string KanjiStringCode() override;
	std::string GetImageFileName() const override;
	std::string GetKanjiImageFileName() override;
	std::string LongStringCode() const;
	static PieceType LongStringCode2PieceType(const std::string& longStringCode);

protected:

private:
};

