﻿#include "DaiDaiShogiPiece.h"

DaiDaiShogiPiece::DaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : MakaDaiDaiShogiPiece(pieceType, pieceColour)
{
}

DaiDaiShogiPiece::~DaiDaiShogiPiece()
{
}

void DaiDaiShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case OldKite:
		_pieceType = Tengu;
		break;
	case PoisonousSnake:
		_pieceType = HookMover;
		break;
	case Lion:
		_pieceType = FuriousFiend;
		break;
	case LionDog:
		_pieceType = GreatElephant;
		break;
	case EasternBarbarian:
		_pieceType = Lion;
		break;
	case WesternBarbarian:
		_pieceType = LionDog;
		break;
	case NorthernBarbarian:
		_pieceType = FragrantElephant;
		break;
	case SouthernBarbarian:
		_pieceType = WhiteElephant;
		break;
	case WaterBuffalo:
		_pieceType = FreeDreamEater;
		break;
	case RushingBird:
		_pieceType = FreeDemon;
		break;
	case FlyingHorse:
		_pieceType = Queen;
		break;
	case NeighboringKing:
		_pieceType = StandardBearer;
		break;
	case BlindMonkey:
		_pieceType = MountainWitch;
		break;
	case OldRat:
		_pieceType = WizardStork;
		break;
	case EnchantedBadger:
		_pieceType = Dove;
		break;
	case EnchantedFox:
		_pieceType = Yaksha;
		break;
	case CatSword:
		_pieceType = DragonHorse;
		break;
	case FlyingDragon:
		_pieceType = DragonKing;
		break;
	case PrancingStag:
		_pieceType = SquareMover;
		break;
	case Phoenix:
		_pieceType = GoldenBird;
		break;
	case Kylin:
		_pieceType = GreatDragon;
		break;
	case LeftChariot:
	case RightChariot:
	case WhiteTiger:
	case BlueDragon:
	case SideMover:
	case VerticalMover:
	case HowlingDog:
	case ReverseChariot:
	case ViolentOx:
	case ViolentBear:
	case AngryBoar:
	case Lance:
	case LeftGeneral:
	case RightGeneral:
	case Leopard:
	case EvilWolf:
	case SavageTiger:
	case Bishop:
	case Rook:
	case RacingChariot:
	case Yaksha:
	case HookMover:
	case King:
	case Gold:
	case Silver:
	case Copper:
	case Iron:
	case Stone:
	case Wood:
	case Pawn:
		_isPromoted = false;
		break;
	default:
		MakaDaiDaiShogiPiece::Promote(pieceType);
		break;
	}
}

std::string DaiDaiShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	default:
		return MakaDaiDaiShogiPiece::StringCode();
	}
}

PieceType DaiDaiShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : MakaDaiDaiShogiPiece::FromStringCode(code);
}

std::string DaiDaiShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	default:
		return MakaDaiDaiShogiPiece::KanjiStringCode();
	}
}

std::string DaiDaiShogiPiece::GetKanjiImageFileName()
{
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	case Tengu:
		return "LongNosedGoblin" + colour + ".png";
	case RacingChariot:
		return "SideChariot" + colour + ".png";
	case NeighboringKing:
		return "NeighborKing" + colour + ".png";
	case Wood:
		return "WoodGeneral" + colour + ".png";
	default:
		return MakaDaiDaiShogiPiece::GetKanjiImageFileName();
	}
}