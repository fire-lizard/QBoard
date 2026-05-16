#include "OmegaChessPiece.h"

OmegaChessPiece::OmegaChessPiece(PieceType pieceType, PieceColour pieceColour) : ChessPiece(pieceType, pieceColour)
{
    _hasMoved = false;
}

OmegaChessPiece::~OmegaChessPiece()
{
}
