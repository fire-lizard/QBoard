#include "DaiDaiShogiPiece.h"

DaiDaiShogiPiece::DaiDaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : MakaDaiDaiShogiPiece(pieceType, pieceColour)
{
}

DaiDaiShogiPiece::~DaiDaiShogiPiece()
{
}

void DaiDaiShogiPiece::Promote(PieceType pieceType)
{
	if (std::find(std::begin(UnpromotablePieces), std::end(UnpromotablePieces), pieceType) != std::end(UnpromotablePieces))
	{
		return;
	}
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
	default:
		break;
	}
}

std::string DaiDaiShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case Tengu:
		return _basePieceType == OldKite ? "+K'" : "J'";
	case Yaksha:
		return _basePieceType == EnchantedFox ? "+F~" : "T!";
	case Queen:
		return _basePieceType == FlyingHorse ? "+A~" : "Q";
	case DragonKing:
		return _basePieceType == FlyingDragon ? "+F'" : "D";
	case DragonHorse:
		return _basePieceType == CatSword ? "+Z" : "H";
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
	case Lion:
		return _basePieceType == EasternBarbarian ? "+C'" : "N";
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
	default:
		return MakaDaiDaiShogiPiece::StringCode();
	}
}

PieceType DaiDaiShogiPiece::FromStringCode(const std::string& code)
{
	if (code == "J'")  return Tengu;
	if (code == "K'")  return OldKite;
	if (code == "+K'") return OldKite;
	if (code == "M'")  return PoisonousSnake;
	if (code == "+M'") return PoisonousSnake;
	if (code == "+N!") return GreatElephant;
	if (code == "B'")  return WesternBarbarian;
	if (code == "+B'") return WesternBarbarian;
	if (code == "C'")  return EasternBarbarian;
	if (code == "+C'") return EasternBarbarian;
	if (code == "G'")  return SouthernBarbarian;
	if (code == "+G'") return SouthernBarbarian;
	if (code == "H'")  return NorthernBarbarian;
	if (code == "+H'") return NorthernBarbarian;
	if (code == "N'")  return FragrantElephant;
	if (code == "O'")  return WhiteElephant;
	if (code == "P'")  return FreeDreamEater;
	if (code == "U'")  return FreeDemon;
	if (code == "X'")  return RushingBird;
	if (code == "+X'") return RushingBird;
	if (code == "Y'")  return StandardBearer;

	if (code == "A~")  return FlyingHorse;
	if (code == "+A~") return FlyingHorse;
	if (code == "B~")  return NeighboringKing;
	if (code == "+B~") return NeighboringKing;
	if (code == "C~")  return BlindMonkey;
	if (code == "D~")  return Dove;
	if (code == "E~")  return EnchantedBadger;
	if (code == "+E~") return EnchantedBadger;
	if (code == "F~")  return EnchantedFox;
	if (code == "+F~") return EnchantedFox;
	if (code == "G~")  return RacingChariot;
	if (code == "H~")  return SquareMover;
	if (code == "I~")  return PrancingStag;
	if (code == "+I~") return PrancingStag;
	if (code == "J~")  return WhiteTiger;
	if (code == "K~")  return BlueDragon;
	if (code == "M~")  return HowlingDog;
	if (code == "N~")  return ViolentBear;
	if (code == "L~")  return LeftGeneral;
	if (code == "R~")  return RightGeneral;
	if (code == "O~")  return SavageTiger;
	if (code == "P~")  return GoldenBird;
	if (code == "Q~")  return GreatDragon;

	if (code == "W'")  return Wood;

	return MakaDaiDaiShogiPiece::FromStringCode(code);
}

std::string DaiDaiShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case Tengu:
		return "天狗";
	case OldKite:
		return "古鵄";
	case PoisonousSnake:
		return "毒蛇";
	case GreatElephant:
		return "大象";
	case WesternBarbarian:
		return "西戎";
	case EasternBarbarian:
		return "東夷";
	case SouthernBarbarian:
		return "南蛮";
	case NorthernBarbarian:
		return "北狄";
	case FragrantElephant:
		return "香象";
	case WhiteElephant:
		return "白象";
	case FreeDreamEater:
		return "奔獏";
	case FreeDemon:
		return "奔鬼";
	case WaterBuffalo:
		return "水牛";
	case RushingBird:
		return "行鳥";
	case StandardBearer:
		return "前旗";
	case FlyingHorse:
		return "馬麟";
	case NeighboringKing:
		return "近王";
	case BlindMonkey:
		return "盲猿";
	case Dove:
		return "鳩槃";
	case EnchantedBadger:
		return "変狸";
	case EnchantedFox:
		return "変狐";
	case RacingChariot:
		return "走車";
	case SquareMover:
		return "方行";
	case PrancingStag:
		return "踊鹿";
	case WhiteTiger:
		return "白虎";
	case BlueDragon:
		return "青龍";
	case HowlingDog:
		return "𠵇犬";
	case ViolentBear:
		return "猛熊";
	case LeftGeneral:
		return "左将";
	case RightGeneral:
		return "右将";
	case SavageTiger:
		return "猛虎";
	case Wood:
		return "木";
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