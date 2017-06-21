#include "ShogiPiece.h"

ShogiPiece::ShogiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted) : ChuShogiPiece(pieceType, pieceColour, isPromoted)
{
}

ShogiPiece::~ShogiPiece()
{
}

void ShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case Rook:
		_pieceType = DragonKing;
		break;
	case Bishop:
		_pieceType = DragonHorse;
		break;
	case Lance:
		_pieceType = Gold;
		break;
	case Silver:
		_pieceType = Gold;
		break;
	case WhiteHorse:
		_pieceType = Gold;
		break;
	case Pawn:
		_pieceType = Gold;
		break;
	default:
		break;
	}
}

string ShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case DragonKing:
		return "D";
	case DragonHorse:
		return "H";
	case Rook:
		return "R";
	case Bishop:
		return "B";
	case Lance:
		return "L";
	case Silver:
		return "S";
	case Gold:
		return "G";
	case WhiteHorse:
		return "N";
	case Pawn:
		return "P";
	default:
		return "";
	}
}
