#pragma once
#include "ShatranjPiece.h"

class CourierChessPiece : public ShatranjPiece
{
public:
    CourierChessPiece(PieceType pieceType, PieceColour pieceColour);
    ~CourierChessPiece() override;
};
