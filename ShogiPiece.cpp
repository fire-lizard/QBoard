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
	case Elephant:
		return "E";
	default:
		return "";
	}
}

string ShogiPiece::AsianStringCode()
{
	switch (_pieceType)
	{
	case King:
		return _basePieceType == Elephant ? "太" : _pieceColour == Black ? "王" : "玉";
	case DragonKing:
		return "竜";
	case DragonHorse:
		return "馬";
	case Rook:
		return "飛";
	case Bishop:
		return "角";
	case Lance:
		return "香";
	case Silver:
		return "銀";
	case Gold:
		switch (_basePieceType)
		{
		case Lance:
			return "杏";
		case Silver:
			return "全";
		case WhiteHorse:
			return "圭";
		case Pawn:
			return "と";
		default:
			return "金";
		}
	case WhiteHorse:
		return "桂";
	case Pawn:
		return "歩";
	case Elephant:
		return "酔";
	default:
		return "";
	}
}
