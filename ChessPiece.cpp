#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted) : Piece(pieceType, pieceColour, isPromoted)
{
	//ctor
}

ChessPiece::~ChessPiece()
{
	//dtor
}

void ChessPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	_pieceType = pieceType;
}

string ChessPiece::StringCode()
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

string ChessPiece::AsianStringCode()
{
	return "";
}
