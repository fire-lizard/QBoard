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
	case Tengu:
		return "天狗";
	case OldKite:
		return "古鵄";
	case PoisonousSnake:
		return "毒蛇";
	case GreatElephant:
		return "大象";
	case FuriousFiend:
		return "奮迅";
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