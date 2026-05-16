#include "GrandeAcedrexPiece.h"

GrandeAcedrexPiece::GrandeAcedrexPiece(PieceType pieceType, PieceColour pieceColour) : ChessPiece(pieceType, pieceColour)
{
}

GrandeAcedrexPiece::~GrandeAcedrexPiece()
{
}

void GrandeAcedrexPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    _pieceType = pieceType;
}
