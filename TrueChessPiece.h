#pragma once
#include "ChessPiece.h"

class TrueChessPiece : public ChessPiece
{
public:
	TrueChessPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	virtual ~TrueChessPiece();
};

