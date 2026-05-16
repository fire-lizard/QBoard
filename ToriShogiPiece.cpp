#include "ToriShogiPiece.h"

ToriShogiPiece::ToriShogiPiece(PieceType pieceType, PieceColour pieceColour) : KanjiPiece(pieceType, pieceColour)
{
}

ToriShogiPiece::~ToriShogiPiece()
{
}

void ToriShogiPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
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
