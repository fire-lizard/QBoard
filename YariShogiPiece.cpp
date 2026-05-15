#include "YariShogiPiece.h"

YariShogiPiece::YariShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
}

YariShogiPiece::~YariShogiPiece()
{
}

void YariShogiPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    switch (_pieceType)
    {
    case YariKnight:
        _pieceType = YariGold;
        break;
    case YariRook:
        _pieceType = Rook;
        break;
    case YariBishop:
        _pieceType = YariGold;
        break;
    case Pawn:
        _pieceType = YariSilver;
        break;
    default:
        break;
    }
}

std::string YariShogiPiece::StringCode()
{
    switch (_pieceType)
    {
    case YariKnight:
        return "N";
    case YariRook:
        return "Y";
    case YariBishop:
        return "B";
    case YariGold:
        return "G";
    case YariSilver:
        return "S";
    default:
        return ShogiPiece::StringCode();
    }
}

