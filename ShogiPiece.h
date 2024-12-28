#pragma once
#include "Piece.h"

class ShogiPiece : public Piece
{
public:
	ShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string AsianStringCode() override;
	virtual std::string GetJapaneseImageFileName();
	std::string LongStringCode() const;
	static PieceType LongStringCode2PieceType(const std::string& longStringCode);

protected:

private:
};

