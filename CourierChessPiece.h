#pragma once
#include "ShatranjPiece.h"

class CourierChessPiece : public ShatranjPiece
{
public:
    CourierChessPiece(PieceType pieceType, PieceColour pieceColour);
    ~CourierChessPiece() override;
    std::string StringCode() override;
    static PieceType FromStringCode(const std::string& code);
};
