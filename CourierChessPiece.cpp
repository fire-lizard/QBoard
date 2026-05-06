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

std::string CourierChessPiece::PieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case Sage: return "Sage";
    case Schleich: return "Schleich";
    case Courier: return "Courier";
    default: return Piece::PieceType2Description(pieceType);
    }
}

PieceType CourierChessPiece::Description2PieceType(const std::string& description)
{
    if (description == "Sage")      return Sage;
    if (description == "Schleich")  return Schleich;
    if (description == "Courier")   return Courier;
    return Piece::Description2PieceType(description);
}

std::string CourierChessPiece::GetImageFileName() const
{
    const std::string colour = _pieceColour == White ? "White" : "Black";
    switch (_pieceType)
    {
    case Sage:
        return colour + "Wizard.png";
    case Schleich:
        return colour + "Hat.png";
    case Courier:
        return colour + "Pegasus.png";
    default:
        return ShatranjPiece::GetImageFileName();
    }
}
