#include "WhaleShogiPiece.h"

WhaleShogiPiece::WhaleShogiPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

WhaleShogiPiece::~WhaleShogiPiece()
{
}

void WhaleShogiPiece::Promote(PieceType pieceType)
{
}

std::string WhaleShogiPiece::StringCode()
{
    switch (_pieceType)
    {
    case King:
        return "W";
    case GreyWhale:
        return "G";
    case Porpoise:
        return "P";
    case DragonKing:
        return "K";
    case Narwhal:
        return "N";
    case Humpback:
        return "H";
    case BlueWhale:
        return "B";
    case Pawn:
        return "D";
    default:
        return "";
    }
}
