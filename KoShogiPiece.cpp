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

void KoShogiPiece::Demote()
{
	if (_isPromoted)
	{
		_isPromoted = false;
		_pieceType = _basePieceType;
	}
}
