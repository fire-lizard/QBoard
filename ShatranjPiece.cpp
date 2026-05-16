#include "ShatranjPiece.h"

ShatranjPiece::ShatranjPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

ShatranjPiece::~ShatranjPiece()
{
}

void ShatranjPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	_pieceType = Queen;
}
