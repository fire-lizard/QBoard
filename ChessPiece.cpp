#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType pieceType, PieceColour pieceColour) : ShatranjPiece(pieceType, pieceColour)
{
	_hasMoved = false;
}

ChessPiece::~ChessPiece()
{
}

void ChessPiece::Promote(PieceType pieceType)
{
    IsPromoted = true;
	_pieceType = pieceType;
}

void ChessPiece::Move()
{
	_hasMoved = true;
}

bool ChessPiece::HasMoved() const
{
	return _hasMoved;
}
