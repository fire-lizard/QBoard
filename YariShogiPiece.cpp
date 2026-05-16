#include "YariShogiPiece.h"

YariShogiPiece::YariShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
}

YariShogiPiece::~YariShogiPiece()
{
}

void YariShogiPiece::Promote(PieceType pieceType)
{
    IsPromoted = true;
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
