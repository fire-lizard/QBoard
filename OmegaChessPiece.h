#pragma once
#include "ChessPiece.h"

class OmegaChessPiece : public ChessPiece
{
public:
    OmegaChessPiece(PieceType pieceType, PieceColour pieceColour);
    ~OmegaChessPiece() override;
    std::string StringCode() override;
    static PieceType FromStringCode(const std::string& code);
    static std::string PieceType2Description(PieceType pieceType);
    static PieceType Description2PieceType(const std::string& description);
};
