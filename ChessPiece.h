#pragma once
#include "ShatranjPiece.h"

class ChessPiece : public ShatranjPiece
{
public:
	ChessPiece(PieceType pieceType, PieceColour pieceColour);
	~ChessPiece() override;
};
