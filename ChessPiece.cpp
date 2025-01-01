#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
	_hasMoved = false;
}

ChessPiece::~ChessPiece()
{
}

void ChessPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	_pieceType = pieceType;
}

std::string ChessPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case Queen:
		return "Q";
	case Rook:
		return "R";
	case Bishop:
		return "B";
	case WhiteHorse:
		return "N";
	case Pawn:
		return "P";
	default:
		return "";
	}
}

void ChessPiece::Move()
{
	_hasMoved = true;
}

bool ChessPiece::HasMoved() const
{
	return _hasMoved;
}
