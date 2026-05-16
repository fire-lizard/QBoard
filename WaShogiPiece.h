#pragma once
#include <unordered_map>
#include "Common.h"
#include "KanjiPiece.h"

class WaShogiPiece : public KanjiPiece
{
public:
	WaShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~WaShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
	static std::string ToStringCode(PieceType piece);
};

