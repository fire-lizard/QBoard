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
