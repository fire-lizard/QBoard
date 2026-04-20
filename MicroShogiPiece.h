#pragma once
#include "KyotoShogiPiece.h"

class MicroShogiPiece : public KyotoShogiPiece
{
public:
    MicroShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~MicroShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
};
