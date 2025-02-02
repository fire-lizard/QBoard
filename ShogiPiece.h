#pragma once
#include <unordered_map>
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
	static PieceType FromStringCode(const std::string& code);
	static std::string ToStringCode(PieceType piece);
	static PieceType LongStringCode2PieceType(const std::string& longStringCode);

protected:

private:
};

