#pragma once
#include "ChessPiece.h"

class GothicChessPiece : public ChessPiece
{
public:
    GothicChessPiece(PieceType pieceType, PieceColour pieceColour);
    ~GothicChessPiece() override;
};
