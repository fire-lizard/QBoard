#pragma once
#include "ShogiPiece.h"

class KyotoShogiPiece : public ShogiPiece
{
public:
    KyotoShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~KyotoShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
};
