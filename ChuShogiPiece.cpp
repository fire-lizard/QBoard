#include "ChuShogiPiece.h"

ChuShogiPiece::ChuShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
}

ChuShogiPiece::~ChuShogiPiece()
{
}

void ChuShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case DragonKing:
		_pieceType = Eagle;
		break;
	case DragonHorse:
		_pieceType = Unicorn;
		break;
	case Rook:
		_pieceType = DragonKing;
		break;
	case Bishop:
		_pieceType = DragonHorse;
		break;
	case VerticalMover:
		_pieceType = FlyingOx;
		break;
	case SideMover:
		_pieceType = FreeBoar;
		break;
	case ReverseChariot:
		_pieceType = Whale;
		break;
	case Lance:
		_pieceType = WhiteHorse;
		break;
	case Kylin:
		_pieceType = Lion;
		break;
	case Phoenix:
		_pieceType = Queen;
		break;
	case Elephant:
		_pieceType = Prince;
		break;
	case Tiger:
		_pieceType = FlyingStag;
		break;
	case Gold:
		_pieceType = Rook;
		break;
	case Silver:
		_pieceType = VerticalMover;
		break;
	case Copper:
		_pieceType = SideMover;
		break;
	case Leopard:
		_pieceType = Bishop;
		break;
	case GoBetween:
		_pieceType = Elephant;
		break;
	case Pawn:
		_pieceType = Tokin;
		break;
	default:
		break;
	}
}

std::string ChuShogiPiece::StringCode()
{
	switch (_pieceType)
	{
    case King:
		return "K";
	case Prince:
		return "+E";
	case Lion:
        if (_basePieceType == Kylin) return "+O"; else if (_basePieceType == EasternBarbarian) return "+C'"; else return "N";
    case Queen:
        if (_basePieceType == Phoenix) return "+X"; else if (_basePieceType == FlyingHorse) return "+A~"; else return "Q";
	case DragonKing:
        if (_basePieceType == Rook) return "+R"; else if (_basePieceType == FlyingDragon) return "+F'"; else return "D";
	case DragonHorse:
        if (_basePieceType == Bishop) return "+B"; else if (_basePieceType == CatSword) return "+Z'"; else return "H";
    case Rook:
		return _basePieceType == Gold ? "+G": "R";
	case Bishop:
		return _basePieceType == Leopard ? "+F" : "B";
	case VerticalMover:
		return _basePieceType == Silver ? "+S" : "V";
	case SideMover:
		return _basePieceType == Copper ? "+C" : "M";
	case ReverseChariot:
		return "A";
	case Lance:
		return "L";
	case Kylin:
		return "O";
	case Phoenix:
		return "X";
	case Elephant:
		return _basePieceType == GoBetween ? "+I" : "E";
	case Tiger:
		return "T";
	case Silver:
		return "S";
	case Copper:
		return "C";
	case Leopard:
		return "F";
	case GoBetween:
		return "I";
	case Pawn:
		return "P";
	case Tokin:
		return "+P";
	case Eagle:
        return _basePieceType == DragonKing ? "+D": "E!";
	case Unicorn:
        return _basePieceType == DragonHorse ? "+H": "F!";
    case FlyingOx:
		return "+V";
	case FreeBoar:
        if (_basePieceType == AngryBoar) return "+A"; else return "+M";
	case FlyingStag:
		return "+T";
	case WhiteHorse:
		return "+L";
	case Whale:
		return "+A";
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
    case WaterBuffalo:
        return _basePieceType == SideSoldier ? "+S'" : "W!";
    case Emperor:
        return "+K";
    case Deva:
        return "A!";
    case DarkSpirit:
        return "G!";
    case TeachingKing:
        return "+A!";
    case BuddhistSpirit:
        return "+G!";
    case FreeGold:
        return "+G";
    case FreeSilver:
        return "+S";
    case FreeCopper:
        return "+C";
    case FreeIron:
        return "+J";
    case FreeTile:
        return "+T'";
    case FreeStone:
        return "+U";
    case FreeEarth:
        return "+E'";
    case FreeGo:
        return "+I";
    case FreeTiger:
        return "+T";
    case FreeLeopard:
        return "+F";
    case CoiledSerpent:
        return "I!";
    case RecliningDragon:
        return "J!";
    case FreeSerpent:
        return "+I!";
    case FreeDragon:
        return "+J!";
    case OldMonkey:
        return "M!";
    case MountainWitch:
        return "+M!";
    case ChineseCock:
        return "K!";
    case WizardStork:
        return "+K!";
    case FreeCat:
        return "+Z";
    case FuriousFiend:
        return "+N";
    case FreeWolf:
        return "+W";
    case BlindBear:
        return "L!";
    case FreeBear:
        return "+L!";
    case OldRat:
        return "O!";
    case Bat:
        return "+O!";
    case Wrestler:
        return "P!";
    case Guardian:
        return "R!";
    case BuddhistDevil:
        return "S!";
    case Donkey:
        return "U!";
    case Capricorn:
        return "X!";
    case LeftChariot:
        return "L'";
    case RightChariot:
        return "R'";
    case SideFlier:
        return "Z!";
    case Tile:
        return "T'";
    case Earth:
        return "E'";
    case Tengu:
        return _basePieceType == OldKite ? "+K'" : "J'";
    case Yaksha:
        return _basePieceType == EnchantedFox ? "+F~" : "T!";
    case HookMover:
        return _basePieceType == PoisonousSnake ? "+M'" : "Y!";
    case OldKite:
        return "K'";
    case PoisonousSnake:
        return "M'";
    case GreatElephant:
        return "+N!";
    case LionDog:
        return _basePieceType == WesternBarbarian ? "+B'" : "N!'";
    case WesternBarbarian:
        return "B'";
    case EasternBarbarian:
        return "C'";
    case SouthernBarbarian:
        return "G'";
    case NorthernBarbarian:
        return "H'";
    case FragrantElephant:
        return _basePieceType == NorthernBarbarian ? "+H'" : "N'";
    case WhiteElephant:
        return _basePieceType == SouthernBarbarian ? "+G'" : "O'";
    case FreeDreamEater:
        return _basePieceType == WaterBuffalo ? "+W!": "P'";
    case FreeDemon:
        return _basePieceType == RushingBird ? "+X'" : "U'";
    case RushingBird:
        return "X'";
    case StandardBearer:
        return _basePieceType == NeighboringKing ? "+B~" : "Y'";
    case FlyingHorse:
        return "A~";
    case NeighboringKing:
        return "B~";
    case BlindMonkey:
        return "C~";
    case Dove:
        return _basePieceType == EnchantedBadger ? "+E~" : "D~";
    case EnchantedBadger:
        return "E~";
    case EnchantedFox:
        return "F~";
    case RacingChariot:
        return "G~";
    case SquareMover:
        return _basePieceType == PrancingStag ? "+I~" : "H~";
    case PrancingStag:
        return "I~";
    case WhiteTiger:
        return "J~";
    case BlueDragon:
        return "K~";
    case HowlingDog:
        return "M~";
    case ViolentBear:
        return "N~";
    case LeftGeneral:
        return "L~";
    case RightGeneral:
        return "R~";
    case SavageTiger:
        return "O~";
    case Wood:
        return "W'";
    case GoldenBird:
        return _basePieceType == Phoenix ? "+X" : "P~";
    case GreatDragon:
        return _basePieceType == Kylin ? "+O" : "Q~";
    case PromotedLance:
        return "+L";
    case PromotedKnight:
        return "+N";
    case PromotedSilver:
        return "+S";
    case Dog:
        return "D'";
    case MultiGeneral:
        return "+D'";
    case ViceGeneral:
        return _basePieceType == BishopGeneral ? "+B!" : "V!";
    case GreatGeneral:
        return _basePieceType == RookGeneral ? "+R!" : "Q!";
    case BishopGeneral:
        return _basePieceType == Unicorn ? "+F!" : "B!";
    case RookGeneral:
        return _basePieceType == Eagle ? "+E!" : "R!";
    case FreeEagle:
        return _basePieceType == Queen ? "+Q" : "Q'";
    case LionHawk:
        return _basePieceType == Lion ? "+N" : "H!";
    case SideSoldier:
        return _basePieceType == Knight ? "+Y" : "S'";
    case VerticalSoldier:
        return _basePieceType == Iron ? "+J" : "V'";
    case ChariotSoldier:
        return _basePieceType == VerticalSoldier ? "+V'" : "C!";
    case HeavenlyTetrarch:
        return "+C!";
    case FireDemon:
        return _basePieceType == WaterBuffalo ? "+W!" : "D!";
    case Gold:
        switch (_basePieceType)
        {
        case Iron:
            return "+J";
        case Stone:
            return "+U";
        case AngryBoar:
            return "+A'";
        case ViolentOx:
            return "+V'";
        case FlyingDragon:
            return "+F'";
        case EvilWolf:
            return "+W";
        case CatSword:
            return "+Z";
        case Knight:
            return "+Y";
        case Lance:
            return "+L";
        case ReverseChariot:
            return "+A";
        case LionDog:
            return "+N!";
        case Wrestler:
            return "+P!";
        case Guardian:
            return "+R!";
        case BuddhistDevil:
            return "+S!";
        case Yaksha:
            return "+T!";
        case Donkey:
            return "+U!";
        case Capricorn:
            return "+X!";
        case HookMover:
            return "+Y!";
        case Bishop:
            return "+B";
        case Rook:
            return "+R";
        case VerticalMover:
            return "+V";
        case SideMover:
            return "+M";
        case LeftChariot:
            return "+L'";
        case RightChariot:
            return "+R'";
        case SideFlier:
            return "+Z!";
        case Pawn:
            return "+P";
        default:
            return "G";
        }
    default:
		return "";
	}
}
