#pragma once
#include "DaiShogiPiece.h"

class HeianShogiPiece : public DaiShogiPiece
{
public:
    HeianShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~HeianShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
};
