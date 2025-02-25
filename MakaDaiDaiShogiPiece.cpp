﻿#include "MakaDaiDaiShogiPiece.h"

MakaDaiDaiShogiPiece::MakaDaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

MakaDaiDaiShogiPiece::~MakaDaiDaiShogiPiece()
{
}

void MakaDaiDaiShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	if (pieceType != None)
	{
		_pieceType = pieceType;
		return;
	}
	switch (_pieceType)
	{
	case King:
		_pieceType = Emperor;
		break;
	case Deva:
		_pieceType = TeachingKing;
		break;
	case DarkSpirit:
		_pieceType = BuddhistSpirit;
		break;
	case Gold:
		_pieceType = FreeGold;
		break;
	case Silver:
		_pieceType = FreeSilver;
		break;
	case Copper:
		_pieceType = FreeCopper;
		break;
	case Iron:
		_pieceType = FreeIron;
		break;
	case Tile:
		_pieceType = FreeTile;
		break;
	case Stone:
		_pieceType = FreeStone;
		break;
	case GoBetween:
		_pieceType = FreeGo;
		break;
	case Earth:
		_pieceType = FreeEarth;
		break;
	case Tiger:
		_pieceType = FreeTiger;
		break;
	case Leopard:
		_pieceType = FreeLeopard;
		break;
	case CoiledSerpent:
		_pieceType = FreeSerpent;
		break;
	case RecliningDragon:
		_pieceType = FreeDragon;
		break;
	case OldMonkey:
		_pieceType = MountainWitch;
		break;
	case ChineseCock:
		_pieceType = WizardStork;
		break;
	case CatSword:
		_pieceType = FreeCat;
		break;
	case Lion:
		_pieceType = FuriousFiend;
		break;
	case Phoenix:
		_pieceType = GoldenBird;
		break;
	case Kylin:
		_pieceType = GreatDragon;
		break;
	case EvilWolf:
		_pieceType = FreeWolf;
		break;
	case BlindBear:
		_pieceType = FreeBear;
		break;
	case AngryBoar:
		_pieceType = FreeBoar;
		break;
	case OldRat:
		_pieceType = Bat;
		break;
	case Lance:
	case ReverseChariot:
	case LionDog:
	case Wrestler:
	case Guardian:
	case BuddhistDevil:
	case Yaksha:
	case FlyingDragon:
	case ViolentOx:
	case Knight:
	case Donkey:
	case Capricorn:
	case HookMover:
	case Bishop:
	case Rook:
	case VerticalMover:
	case SideMover:
	case LeftChariot:
	case RightChariot:
	case SideFlier:
	case Pawn:
		_pieceType = Gold;
		break;
	default:
		DaiShogiPiece::Promote(pieceType);
		break;
	}
}

std::string MakaDaiDaiShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	default:
		return DaiShogiPiece::StringCode();
	}
}

PieceType MakaDaiDaiShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : DaiShogiPiece::FromStringCode(code);
}

std::string MakaDaiDaiShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case Emperor:
		return "自在天王";
	case Deva:
		return "提婆";
	case DarkSpirit:
		return "無明";
	case TeachingKing:
		return "教王";
	case BuddhistSpirit:
		return "法性";
	case FreeGold:
		return "奔金";
	case FreeSilver:
		return "奔銀";
	case FreeCopper:
		return "奔銅";
	case FreeIron:
		return "奔鉄";
	case FreeTile:
		return "奔瓦";
	case FreeStone:
		return "奔石";
	case FreeEarth:
		return "奔土";
	case FreeGo:
		return "奔人";
	case FreeTiger:
		return "奔虎";
	case FreeLeopard:
		return "奔豹";
	case CoiledSerpent:
		return "蟠蛇";
	case RecliningDragon:
		return "臥龍";
	case FreeSerpent:
		return "奔蛇";
	case FreeDragon:
		return "奔龍";
	case OldMonkey:
		return "古猿";
	case MountainWitch:
		return "山母";
	case ChineseCock:
		return "淮鶏";
	case WizardStork:
		return "仙鶴";
	case FreeCat:
		return "奔猫";
	case FuriousFiend:
		return "奮迅";
	case GoldenBird:
		return "金翅";
	case GreatDragon:
		return "大龍";
	case FreeWolf:
		return "奔狼";
	case FreeBear:
		return "奔熊";
	case OldRat:
		return "老鼠";
	case Bat:
		return "蝙蝠";
	case LionDog:
		return "狛犬";
	case Wrestler:
		return "力士";
	case Guardian:
		return "金剛";
	case BuddhistDevil:
		return "羅刹";
	case Yaksha:
		return "夜叉";
	case Donkey:
		return "驢馬";
	case Capricorn:
		return "摩𩹄";
	case HookMover:
		return "鉤行";
	case LeftChariot:
		return "左車";
	case RightChariot:
		return "右車";
	case SideFlier:
		return "横飛";
	case Tile:
		return "瓦";
	case Earth:
		return "土";
	default:
		return DaiShogiPiece::KanjiStringCode();
	}
}

std::string MakaDaiDaiShogiPiece::GetKanjiImageFileName()
{
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	case Gold:
	case Silver:
	case Copper:
	case Iron:
	case Tile:
	case Stone:
	case Earth:
		return PieceType2Description(_pieceType) + "General" + colour + ".png";
	case Leopard:
		return "FerociousLeopard" + colour + ".png";
	case Tiger:
		return "BlindTiger" + colour + ".png";
	case Elephant:
		return "DrunkElephant" + colour + ".png";
	case Kylin:
		return "Kirin" + colour + ".png";
	case Guardian:
		return "GuardianGod" + colour + ".png";
	case Yaksha:
		return "SheDevil" + colour + ".png";
	case FreeSerpent:
		return "FreeSnake" + colour + ".png";
	case FreeGo:
		return "FreeGoBetween" + colour + ".png";
	default:
		std::string desc = PieceType2Description(_pieceType);
		replaceSubstring(desc, " ", "");
		return desc + colour + ".png";
	}
}