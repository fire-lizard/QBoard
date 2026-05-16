#pragma once
#include <unordered_map>
#include "Common.h"
#include "Piece.h"

class WaShogiPiece : public Piece
{
public:
	WaShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~WaShogiPiece() override;
	static std::string ToStringCode(PieceType piece);
};

