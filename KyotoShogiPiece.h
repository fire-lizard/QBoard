#pragma once
#include "ShogiPiece.h"

class KyotoShogiPiece : public ShogiPiece
{
public:
    KyotoShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~KyotoShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
    std::string GetImageFileName() const override;
    std::string GetKanjiImageFileName() override;
    std::string GetKanjiImageFileName2() override;
};
