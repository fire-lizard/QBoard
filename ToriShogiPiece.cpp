#include "ToriShogiPiece.h"

ToriShogiPiece::ToriShogiPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

ToriShogiPiece::~ToriShogiPiece()
{
}

void ToriShogiPiece::Promote(PieceType pieceType)
{
    IsPromoted = true;
    switch (_pieceType)
    {
    case Falcon:
        _pieceType = Eagle;
        break;
    case Pawn:
        _pieceType = Goose;
        break;
    default:
        break;
    }
}
