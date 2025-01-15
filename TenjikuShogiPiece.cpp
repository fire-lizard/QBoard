#include "TenjikuShogiPiece.h"

TenjikuShogiPiece::TenjikuShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

TenjikuShogiPiece::~TenjikuShogiPiece()
{
}

void TenjikuShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case BishopGeneral:
		_pieceType = ViceGeneral;
		break;
	case RookGeneral:
		_pieceType = GreatGeneral;
		break;
	case Dog:
		_pieceType = MultiGeneral;
		break;
	case SideSoldier:
		_pieceType = WaterBuffalo;
		break;
	case VerticalSoldier:
		_pieceType = ChariotSoldier;
		break;
	case ChariotSoldier:
		_pieceType = HeavenlyTetrarch;
		break;
	case WaterBuffalo:
		_pieceType = FireDemon;
		break;
	case Queen:
		_pieceType = FreeEagle;
		break;
	case Iron:
		_pieceType = VerticalSoldier;
		break;
	case Knight:
		_pieceType = SideSoldier;
		break;
	case Lion:
		_pieceType = LionHawk;
		break;
	case Unicorn:
		_pieceType = BishopGeneral;
		break;
	case Eagle:
		_pieceType = RookGeneral;
		break;
	default:
		DaiShogiPiece::Promote(pieceType);
		break;
	}
}

std::string TenjikuShogiPiece::StringCode()
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
		return DaiShogiPiece::StringCode();
	}
}

std::string TenjikuShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case ViceGeneral:
		return "副";
	case GreatGeneral:
		return "大";
	case BishopGeneral:
		return "用";
	case RookGeneral:
		return "升";
	case MultiGeneral:
		return "雜";
	case Dog:
		return "犬";
	case FreeEagle:
		return "就";
	case LionHawk:
		return "師";
	case SideSoldier:
		return "黄";
	case VerticalSoldier:
		return "立";
	case ChariotSoldier:
		return "車";
	case WaterBuffalo:
		return "水";
	case HeavenlyTetrarch:
		return "天";
	case FireDemon:
		return "火";
	default:
		return DaiShogiPiece::KanjiStringCode();
	}
}

std::string TenjikuShogiPiece::GetImageFileName() const
{
	const std::string colour = _pieceColour == White ? "_B" : "_W";
	const std::string promo = _isPromoted ? "P" : "";
	switch (_pieceType)
	{
	case ViceGeneral:
		return "ViceGeneral" + colour + ".png";
	case GreatGeneral:
		return "GreatGeneral" + colour + ".png";
	case BishopGeneral:
		return promo + "BishopGeneral" + colour + ".png";
	case RookGeneral:
		return promo + "RookGeneral" + colour + ".png";
	case MultiGeneral:
		return "Multi-General" + colour + "2.png";
	case Dog:
		return promo + "Dog" + colour + ".png";
	case FreeEagle:
		return "FreeEagle" + colour + ".png";
	case LionHawk:
		return "Lion-Hawk" + colour + ".png";
	case SideSoldier:
		return promo + "SideSoldier" + colour + ".png";
	case VerticalSoldier:
		return promo + "VerticalSoldier" + colour + ".png";
	case ChariotSoldier:
		return promo + "ChariotSoldier" + colour + ".png";
	case Phoenix:
		return "Phoenix" + colour + ".png";
	case Elephant:
		return promo + "Elephant" + colour + ".png";
	case Tiger:
		return "Tiger" + colour + ".png";
	case Leopard:
		return "Leopard" + colour + ".png";
	case WaterBuffalo:
		return promo + "WaterBuffalo" + colour + ".png";
	case HeavenlyTetrarch:
		return "Heaven" + colour + ".png";
	case FireDemon:
		return "FireDemon" + colour + ".png";
	case Queen:
		return promo + "Queen" + colour + ".png";
	case Knight:
		return "Knight" + colour + ".png";
	case Iron:
		return "Iron" + colour + ".png";
	case Tokin:
		return promo + "Gold" + colour + ".png";
	case FreeBoar:
		return "FBoar" + colour + ".png";
	case FlyingOx:
		return "pOx" + colour + ".png";
	default:
		return GetMnemonicImageFileName();
	}
}