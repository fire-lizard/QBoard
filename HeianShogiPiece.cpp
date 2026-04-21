#include "HeianShogiPiece.h"

HeianShogiPiece::HeianShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

HeianShogiPiece::~HeianShogiPiece()
{
}

void HeianShogiPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    _pieceType = Gold;
}
