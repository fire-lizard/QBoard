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
		return "J";
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
		return "Z";
	case Knight:
		return "Y";
	default:
		return ChuShogiPiece::StringCode();
	}
}

PieceType DaiShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"J", Iron},
		{"U", Stone},
		{"A'", AngryBoar},
		{"V'", ViolentOx},
		{"F'", FlyingDragon},
		{"W", EvilWolf},
		{"Z", CatSword},
		{"Y", Knight}
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
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	case Knight:
		return "Knight" + colour + ".png";
	case ViolentOx:
		return "ViolentOx" + colour + ".png";
	case FlyingDragon:
		return "FlyingDragon" + colour + ".png";
	case AngryBoar:
		return "AngryBoar" + colour + ".png";
	case CatSword:
		return "Cat" + colour + ".png";
	case EvilWolf:
		return "Wolf" + colour + ".png";
	case Iron:
		return "Iron" + colour + ".png";
	case Stone:
		return "Stone" + colour + ".png";
	default:
		return ChuShogiPiece::GetKanjiImageFileName();
	}
}

std::string DaiShogiPiece::GetKanjiImageFileName2()
{
	std::string colour = _pieceColour == White ? "_piece_B_" : "_piece_W_";
	colour += _isPromoted ? "prom" : "norm";
	switch (_pieceType)
	{
	case Knight:
		return "Kon" + colour + ".png";
	case ViolentOx:
		return "Silnyj_byk" + colour + ".png";
	case FlyingDragon:
		return "Letajushij_drakon" + colour + ".png";
	case AngryBoar:
		return "Dikij_kaban" + colour + ".png";
	case CatSword:
		return "Koshachij_mech" + colour + ".png";
	case EvilWolf:
		return "Zloj_Volk" + colour + ".png";
	case Iron:
		return "ZHeleznyj_general" + colour + ".png";
	case Stone:
		return "Kamennyj_general" + colour + ".png";
	default:
		return ChuShogiPiece::GetKanjiImageFileName2();
	}
}