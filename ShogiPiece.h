#pragma once
#include "ChuShogiPiece.h"

class ShogiPiece : public ChuShogiPiece
{
public:
	ShogiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	virtual ~ShogiPiece();
};

