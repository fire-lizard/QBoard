#pragma once
#include "ChessPiece.h"

class GrandeAcedrexPiece : public ChessPiece
{
public:
    GrandeAcedrexPiece(PieceType pieceType, PieceColour pieceColour);
    ~GrandeAcedrexPiece() override;
    void Promote(PieceType pieceType = None) override;
    std::string StringCode() override;
    static PieceType FromStringCode(const std::string& code);
};
