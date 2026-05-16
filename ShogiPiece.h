#pragma once
#include <unordered_map>
#include "KanjiPiece.h"

class ShogiPiece : public KanjiPiece
{
public:
	ShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
    static std::string ToStringCode(PieceType piece);
};

