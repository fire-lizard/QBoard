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
		return "X'";
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
		return "L!";
	default:
		return ChuShogiPiece::StringCode();
	}
}

PieceType DaiShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"I", Iron},
		{"U", Stone},
		{"A'", AngryBoar},
		{"X'", ViolentOx},
		{"F'", FlyingDragon},
		{"W", EvilWolf},
		{"C'", CatSword},
		{"N", Knight},
		{"P'", GoBetween},
		{"L!", Lion}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : ChuShogiPiece::FromStringCode(code);
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

std::string DaiShogiPiece::GetKanjiImageFileName()
{
	std::string imageFileName = ChuShogiPiece::GetKanjiImageFileName();
	const std::string colour = _pieceColour == White ? "White" : "Black";
	if (_isPromoted)
	{
		if (_pieceType == Gold)
		{
			return colour + "PromoGold.png";
		}
		else if (_pieceType == WhiteHorse)
		{
			return colour + "WhiteHorse.png";
		}
		else if (_pieceType == Prince)
		{
			return colour + "PromoKing.png";
		}
	}
	else if (_pieceType == Stone)
	{
		return colour + "Stone.png";
	}
	else if (_pieceType == CatSword)
	{
		return colour + "CatSword.png";
	}
	else if (_pieceType == AngryBoar)
	{
		return colour + "AngryBoar.png";
	}
	return imageFileName;
}