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

PieceType CourierChessPiece::FromStringCode(const std::string& code)
{
    static const std::unordered_map<std::string, PieceType> codeToPieceType = {
        {"E", Bishop},
        {"B", Courier},
        {"W", Schleich},
        {"M", Sage},
        {"F", Queen}
    };

    const auto it = codeToPieceType.find(code);
    return it != codeToPieceType.end() ? it->second : ShatranjPiece::FromStringCode(code);
}
