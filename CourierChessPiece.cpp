#include "CourierChessPiece.h"

CourierChessPiece::CourierChessPiece(PieceType pieceType, PieceColour pieceColour) : ShatranjPiece(pieceType, pieceColour)
{
}

CourierChessPiece::~CourierChessPiece()
{
}

std::string CourierChessPiece::StringCode()
{
    switch (_pieceType)
    {
    case Bishop:
        return "E";
    case Courier:
        return "B";
    case Schleich:
        return "W";
    case Sage:
        return "M";
    case Queen:
        return "F";
    default:
        return ShatranjPiece::StringCode();
    }
}
