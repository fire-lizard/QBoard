#pragma once
#include "Piece.h"

class XiangqiPiece : public Piece
{
public:
	XiangqiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	virtual ~XiangqiPiece();
};

