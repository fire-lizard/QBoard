#pragma once
#include "ChessPiece.h"

class OmegaChessPiece : public ChessPiece
{
public:
    OmegaChessPiece(PieceType pieceType, PieceColour pieceColour);
    ~OmegaChessPiece() override;
    std::string StringCode() override;
    static PieceType FromStringCode(const std::string& code);
};
