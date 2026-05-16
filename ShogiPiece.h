#pragma once
#include <unordered_map>
#include "Piece.h"

class ShogiPiece : public Piece
{
public:
	ShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
    static std::string ToStringCode(PieceType piece);
};

