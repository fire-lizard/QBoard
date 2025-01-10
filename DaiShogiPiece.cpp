#include "DaiShogiPiece.h"

DaiShogiPiece::DaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : ChuShogiPiece(pieceType, pieceColour)
{
}

DaiShogiPiece::~DaiShogiPiece()
{
}

void DaiShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case Iron:
	case Stone:
	case AngryBoar:
	case ViolentOx:
	case FlyingDragon:
	case EvilWolf:
	case CatSword:
	case Knight:
		_pieceType = Gold;
		break;
	default:
		ChuShogiPiece::Promote(pieceType);
		break;
	}
}

std::string DaiShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case Iron:
		return "I";
	case Stone:
		return "U";
	case AngryBoar:
		return "A'";
	case ViolentOx:
		return "V'";
	case FlyingDragon:
		return "F'";
	case EvilWolf:
		return "W";
	case CatSword:
		return "C'";
	case Knight:
		return "N";
	case GoBetween:
		return "P'";
	case Lion:
		return "L!'";
	default:
		return ChuShogiPiece::StringCode();
	}
}

std::string DaiShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case Iron:
		return "鉄";
	case Stone:
		return "石";
	case AngryBoar:
		return "猪";
	case ViolentOx:
		return "牛";
	case FlyingDragon:
		return "龍";
	case EvilWolf:
		return "狼";
	case CatSword:
		return "猫";
	case Knight:
		return "桂";
	default:
		return ChuShogiPiece::KanjiStringCode();
	}
}
