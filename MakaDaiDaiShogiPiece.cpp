#include "MakaDaiDaiShogiPiece.h"

MakaDaiDaiShogiPiece::MakaDaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

MakaDaiDaiShogiPiece::~MakaDaiDaiShogiPiece()
{
}

void MakaDaiDaiShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case King:
		_pieceType = Emperor;
		break;
	case Deva:
		_pieceType = TeachingKing;
		break;
	case DarkSpirit:
		_pieceType = BuddhistDevil;
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
	case Queen:
	case DragonKing:
	case DragonHorse:
		_isPromoted = false;
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
	default:
		return DaiShogiPiece::GetKanjiImageFileName();
	}
}