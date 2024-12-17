#pragma once
#include "Piece.h"
#include "Common.h"

class ChuShogiPiece : public Piece
{
public:
	ChuShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ChuShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	std::string StringCode() override;
	std::string AsianStringCode() override;
	virtual std::string GetJapaneseImageFileName();

protected:
	static void replaceSubstring(std::string& str, const std::string& from, const std::string& to);

private:
};
