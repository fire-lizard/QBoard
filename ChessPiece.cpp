#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType pieceType, PieceColour pieceColour) : ShatranjPiece(pieceType, pieceColour)
{
	_hasMoved = false;
}

ChessPiece::~ChessPiece()
{
}

void ChessPiece::Move()
{
	_hasMoved = true;
}

bool ChessPiece::HasMoved() const
{
	return _hasMoved;
}
