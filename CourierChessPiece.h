#pragma once
#include "ShatranjPiece.h"

class CourierChessPiece : public ShatranjPiece
{
public:
    CourierChessPiece(PieceType pieceType, PieceColour pieceColour);
    ~CourierChessPiece() override;
    std::string StringCode() override;
    std::string GetImageFileName() const override;
    static PieceType FromStringCode(const std::string& code);
    static std::string PieceType2Description(PieceType pieceType);
    static PieceType Description2PieceType(const std::string& description);
};
