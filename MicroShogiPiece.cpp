#include "MicroShogiPiece.h"

MicroShogiPiece::MicroShogiPiece(PieceType pieceType, PieceColour pieceColour) : KyotoShogiPiece(pieceType, pieceColour)
{
}

MicroShogiPiece::~MicroShogiPiece()
{
}

void MicroShogiPiece::Promote(PieceType pieceType)
{
    switch (_pieceType)
    {
    case Rook:
        _pieceType = Gold;
        break;
    case Bishop:
        _pieceType = Tokin;
        break;
    case Tokin:
        _pieceType = Bishop;
        break;
    case Lance:
        _pieceType = Silver;
        break;
    case Silver:
        _pieceType = Lance;
        break;
    case Knight:
        _pieceType = Pawn;
        break;
    case Gold:
        _pieceType = Rook;
        break;
    case Pawn:
        _pieceType = Knight;
        break;
    default:
        break;
    }
}
