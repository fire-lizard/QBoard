#pragma once
#include <unordered_map>
#include "KanjiPiece.h"

class ToriShogiPiece : public KanjiPiece
{
public:
    ToriShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~ToriShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
};
