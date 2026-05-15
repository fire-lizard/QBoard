#include "KoShogiPiece.h"

KoShogiPiece::KoShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

KoShogiPiece::~KoShogiPiece()
{
}

void KoShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case Kylin:
		_pieceType = DoubleKylin;
		break;
	case Phoenix:
		_pieceType = DoublePhoenix;
		break;
	case Elephant:
		_pieceType = DragonKing;
		break;
	case Gold:
		_pieceType = FlyingStag;
		break;
	case Silver:
		_pieceType = CompanyCommander;
		break;
	case Leopard:
		_pieceType = ViceCommissioner;
		break;
	case Copper:
		_pieceType = PoisonFlame;
		break;
	case TaoistPriest:
		_pieceType = ExtensiveFog;
		break;
	case SpiritualMonk:
		_pieceType = HolyLight;
		break;
	case AdvanceGuard:
		_pieceType = SkywardNet;
		break;
	case MiddleTroop:
		_pieceType = Prince;
		break;
	case Drum:
		_pieceType = Thunderclap;
		break;
	case Flag:
		_pieceType = RoamingAssault;
		break;
	case Tiger:
		_pieceType = DragonHorse;
		break;
	case Queen:
		_pieceType = RisingDragon;
		break;
	case DragonKing:
		_pieceType = WingedTiger;
		break;
	case DragonHorse:
		_pieceType = FlyingHawk;
		break;
	case RearGuard:
		_pieceType = EarthwardNet;
		break;
	case FrankishCannon:
		_pieceType = DivineCarriage;
		break;
	case Longbow:
		_pieceType = LongbowKnight;
		break;
	case Crossbow:
		_pieceType = CrossbowKnight;
		break;
	case Cannon:
		_pieceType = CannonCarriage;
		break;
	case Knight:
		_pieceType = KnightCaptain;
		break;
	case KnightCaptain:
		_pieceType = WingedHorse;
		break;
	case Pawn:
		_pieceType = VerticalMover;
		break;
	case CatSword:
		_pieceType = ShieldCaptain;
		break;
	case ShieldCaptain:
		_pieceType = FreeBoar;
		break;
	case Chariot:
		_pieceType = Rook;
		break;
	case Rook:
		_pieceType = Queen;
		break;
	case VerticalMover:
	case Vanguard:
		_pieceType = FlyingOx;
		break;
	default:
		break;
	}
}

std::string KoShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case MiddleTroop:
		return "M";
	case Prince:
		return "+M";
	case Drum:
		return "U";
	case Thunderclap:
		return "+U";
	case Flag:
		return "L";
	case RoamingAssault:
		return "+L";
	case Tiger:
		return "T";
	case DragonHorse:
		return _basePieceType == Tiger ? "+T" : "H";
	case Elephant:
		return "E";
	case DragonKing:
		return _basePieceType == Elephant ? "+E" : "D";
	case Gold:
		return "G";
	case FlyingStag:
		return "+G";
	case Silver:
		return "S";
	case CompanyCommander:
		return "+S";
	case Leopard:
		return "F";
	case ViceCommissioner:
		return "+F";
	case Copper:
		return "C";
	case PoisonFlame:
		return "+C";
	case Lion:
		return "N";
	case Kylin:
		return "O";
	case DoubleKylin:
		return "+O";
	case Phoenix:
		return "X";
	case DoublePhoenix:
		return "+X";
	case TaoistPriest:
		return "T'";
	case SpiritualMonk:
		return "S'";
	case ExtensiveFog:
		return "+T'";
	case HolyLight:
		return "+S'";
	case AdvanceGuard:
		return "A'";
	case RearGuard:
		return "R'";
	case SkywardNet:
		return "+A'";
	case EarthwardNet:
		return "+R'";
	case Queen:
		return _basePieceType == Rook ? "+R" : "Q";
	case RisingDragon:
		return "+Q";
	case WingedTiger:
		return "+D";
	case FlyingHawk:
		return "+H";
	case Bishop:
		return "B";
	case Longbow:
		return "L'";
	case LongbowKnight:
		return "+L'";
	case Crossbow:
		return "C'";
	case CrossbowKnight:
		return "+C'";
	case Cannon:
		return "I";
	case CannonCarriage:
		return "+I";
	case FrankishCannon:
		return "J";
	case DivineCarriage:
		return "+J";
	case Knight:
		return "Y";
	case KnightCaptain:
		return _basePieceType == Knight ? "+Y" : "W";
	case WingedHorse:
		return "+W";
	case Pawn:
		return "P";
	case VerticalMover:
		return _basePieceType == Pawn ? "+P" : "V";
	case FlyingOx:
		return "+V";
	case CatSword:
		return "Z";
	case ShieldCaptain:
		return _basePieceType == CatSword ? "+Z": "U'";
	case FreeBoar:
		return "F'";
	case Chariot:
		return "A";
	case Rook:
		return _basePieceType == Chariot ? "+A" : "R";
	case Vanguard:
		return "V'";
	default:
		return "";
	}
}

void KoShogiPiece::Demote()
{
	if (_isPromoted)
	{
		_isPromoted = false;
		_pieceType = _basePieceType;
	}
}
