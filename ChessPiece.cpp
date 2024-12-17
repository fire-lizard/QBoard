#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
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

std::string ChessPiece::AsianStringCode()
{
	return "";
}
