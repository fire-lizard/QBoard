#include "OmegaChessPiece.h"

OmegaChessPiece::OmegaChessPiece(PieceType pieceType, PieceColour pieceColour) : ChessPiece(pieceType, pieceColour)
{
    _hasMoved = false;
}

OmegaChessPiece::~OmegaChessPiece()
{
}

std::string OmegaChessPiece::StringCode()
{
    switch (_pieceType)
    {
    case Champion:
        return "C";
    case Wizard:
        return "W";
    default:
        return ChessPiece::StringCode();
    }
}

PieceType OmegaChessPiece::FromStringCode(const std::string& code)
{
    static const std::unordered_map<std::string, PieceType> codeToPieceType = {
        {"C", Champion},
        {"W", Wizard}
    };

    const auto it = codeToPieceType.find(code);
    return it != codeToPieceType.end() ? it->second : ChessPiece::FromStringCode(code);
}

std::string OmegaChessPiece::PieceType2Description(PieceType pieceType)
{
    switch (pieceType)
    {
    case Champion: return "Champion";
    case Wizard: return "Wizard";
    default: return Piece::PieceType2Description(pieceType);
    }
}

PieceType OmegaChessPiece::Description2PieceType(const std::string& description)
{
    if (description == "Champion")  return Champion;
    if (description == "Wizard")    return Wizard;
    return Piece::Description2PieceType(description);
}
