#pragma once
#include "Common.h"
#include "Board.h"
#include "ShogiPiece.h"

class ShogiVariantBoard : public Board
{
public:
	void PlacePiece(PieceType pieceType, PieceColour pieceColour, int x, int y);
};

