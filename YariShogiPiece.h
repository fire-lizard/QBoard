#pragma once
#include "ShogiPiece.h"

class YariShogiPiece : public ShogiPiece
{
public:
    YariShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~YariShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
};
