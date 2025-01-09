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

std::string ShatranjPiece::StringCode()
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
	case Knight:
		return "N";
	case Pawn:
		return "P";
	default:
		return "";
	}
}
