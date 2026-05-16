#pragma once
#include "ChessPiece.h"

class GrandeAcedrexPiece : public ChessPiece
{
public:
    GrandeAcedrexPiece(PieceType pieceType, PieceColour pieceColour);
    ~GrandeAcedrexPiece() override;
    void Promote(PieceType pieceType = None) override;
};
