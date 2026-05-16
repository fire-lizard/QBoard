#include "Piece.h"

Piece::Piece(PieceType pieceType, PieceColour pieceColour)
{
	_basePieceType = pieceType;
	_pieceType = pieceType;
	_pieceColour = pieceColour;
    IsPromoted = false;
}

Piece::~Piece()
{
}

PieceType Piece::GetBaseType() const
{
	return _basePieceType;
}

PieceType Piece::GetType() const
{
	return _pieceType;
}

void Piece::SetType(PieceType pieceType)
{
    _pieceType = pieceType;
}

PieceColour Piece::GetColour() const
{
	return _pieceColour;
}
