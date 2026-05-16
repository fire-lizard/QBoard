#include "GrandeAcedrexPiece.h"

GrandeAcedrexPiece::GrandeAcedrexPiece(PieceType pieceType, PieceColour pieceColour) : ChessPiece(pieceType, pieceColour)
{
}

GrandeAcedrexPiece::~GrandeAcedrexPiece()
{
}

void GrandeAcedrexPiece::Promote(PieceType pieceType)
{
    IsPromoted = true;
    _pieceType = pieceType;
}
