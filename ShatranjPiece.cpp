#include "ShatranjPiece.h"

ShatranjPiece::ShatranjPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

ShatranjPiece::~ShatranjPiece()
{
}

void ShatranjPiece::Promote(PieceType pieceType)
{
	IsPromoted = true;
	_pieceType = Queen;
}
