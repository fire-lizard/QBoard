#pragma once
#include <unordered_map>
#include "Piece.h"

class ToriShogiPiece : public Piece
{
public:
    ToriShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~ToriShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
};
