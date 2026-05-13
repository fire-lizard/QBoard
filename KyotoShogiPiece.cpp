#include "KyotoShogiPiece.h"

KyotoShogiPiece::KyotoShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
}

KyotoShogiPiece::~KyotoShogiPiece()
{
}

void KyotoShogiPiece::Promote(PieceType pieceType)
{
    switch (_pieceType)
    {
    case Rook:
        _pieceType = Pawn;
        break;
    case Bishop:
        _pieceType = Silver;
        break;
    case Tokin:
        _pieceType = Lance;
        break;
    case Lance:
        _pieceType = Tokin;
        break;
    case Silver:
        _pieceType = Bishop;
        break;
    case Knight:
        _pieceType = Gold;
        break;
    case Gold:
        _pieceType = Knight;
        break;
    case Pawn:
        _pieceType = Rook;
        break;
    default:
        break;
    }
}
