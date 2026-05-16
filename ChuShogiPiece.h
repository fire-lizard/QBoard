#pragma once
#include <unordered_map>
#include "ShogiPiece.h"
#include "Common.h"

class ChuShogiPiece : public ShogiPiece
{
public:
	ChuShogiPiece(PieceType pieceType, PieceColour pieceColour);
	~ChuShogiPiece() override;
	void Promote(PieceType pieceType = None) override;
};
