#include "GothicChessPiece.h"

GothicChessPiece::GothicChessPiece(PieceType pieceType, PieceColour pieceColour) : ChessPiece(pieceType, pieceColour)
{
    _hasMoved = false;
}

GothicChessPiece::~GothicChessPiece()
{
}
