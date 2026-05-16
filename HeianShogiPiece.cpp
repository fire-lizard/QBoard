#include "HeianShogiPiece.h"

HeianShogiPiece::HeianShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

HeianShogiPiece::~HeianShogiPiece()
{
}

void HeianShogiPiece::Promote(PieceType pieceType)
{
    IsPromoted = true;
    _pieceType = Gold;
}
