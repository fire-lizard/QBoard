#pragma once
#include "unordered_map"
#include "Piece.h"

class WhaleShogiPiece : public Piece
{
public:
    WhaleShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~WhaleShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
    std::string StringCode() override;
};
