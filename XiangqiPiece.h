#pragma once
#include <unordered_map>
#include "Piece.h"

class XiangqiPiece : public Piece
{
public:
	XiangqiPiece(PieceType pieceType, PieceColour pieceColour);
	~XiangqiPiece() override;
};

