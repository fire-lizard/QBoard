#include "WaShogiPiece.h"

WaShogiPiece::WaShogiPiece(PieceType pieceType, PieceColour pieceColour) : KanjiPiece(pieceType, pieceColour)
{
}

WaShogiPiece::~WaShogiPiece()
{
}

void WaShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case Lance:
		_pieceType = PloddingOx;
		break;
	case Pawn:
		_pieceType = Tokin;
		break;
	case SideMover:
		_pieceType = Rook;
		break;
	case LiberatedHorse:
		_pieceType = HeavenlyHorse;
		break;
	case SwoopingOwl:
		_pieceType = CloudEagle;
		break;
	case StruttingCrow:
		_pieceType = FlyingFalcon;
		break;
	case FlyingFalcon:
		_pieceType = TenaciousFalcon;
		break;
	case FlyingCock:
		_pieceType = RaidingFalcon;
		break;
	case FlyingGoose:
		_pieceType = SideMover;
		break;
	case ClimbingMonkey:
		_pieceType = Silver;
		break;
	case Silver:
		_pieceType = Elephant;
		break;
	case BlindDog:
		_pieceType = Gold;
		break;
	case Gold:
		_pieceType = BearEyes;
		break;
	case RunningRabbit:
		_pieceType = TreacherousFox;
		break;
	default:
		break;
	}
}

std::string WaShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case Rook:
		return "R";
	case Lance:
		return "L";
	case Tokin:
		return "G";
	case Pawn:
		return "P";
	case SideMover:
		return "E";
	case PloddingOx:
		return "E";
	case LiberatedHorse:
		return "E";
	case HeavenlyHorse:
		return "E";
	case SwoopingOwl:
		return "E";
	case CloudEagle:
		return "E";
	case StruttingCrow:
		return "E";
	case FlyingFalcon:
		return "E";
	case FlyingCock:
		return "E";
	case RaidingFalcon:
		return "E";
	case FlyingGoose:
		return "E";
	case ClimbingMonkey:
		return "E";
	case Silver:
		return "E";
	case BlindDog:
		return "E";
	case Gold:
		return "E";
	case Elephant:
		return "E";
	case BearEyes:
		return "E";
	case RunningRabbit:
		return "E";
	case TreacherousFox:
		return "E";
	case TenaciousFalcon:
		return "E";
	default:
		return "";
	}
}

std::string WaShogiPiece::LongStringCode() const
{
	switch (_pieceType)
	{
	case Lance:
		return "Oxcart";
	case Pawn:
		return "Sparrow Pawn";
	case SideMover:
		return "Swallow's Wings";
	case CloudEagle:
		return "Cloud Eagle";
	case LiberatedHorse:
		return "LiberatedHorse";
	case SwoopingOwl:
		return "Swooping Owl";
	case StruttingCrow:
		return "Strutting Crow";
	case FlyingFalcon:
		return "Flying Falcon";
	case FlyingCock:
		return "Flying Cock";
	case FlyingGoose:
		return "Flying Goose";
	case ClimbingMonkey:
		return "Climbing Monkey";
	case Silver:
		return "Violent Stag";
	case Gold:
		return "Violent Wolf";
	case BlindDog:
		return "Blind Dog";
	case RunningRabbit:
		return "Running Rabbit";
	case TreacherousFox:
		return "Treacherous Fox";
	default:
		return "";
	}
}

PieceType WaShogiPiece::LongStringCode2PieceType(const std::string& longStringCode)
{
	if (longStringCode == "Oxcart") return Lance;
	if (longStringCode == "Sparrow Pawn") return Pawn;
	if (longStringCode == "Swallow's Wings") return SideMover;
	return None;
}

std::string WaShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return "靏";
	case Rook:
		return "行";
	case Lance:
		return "車";
	case Tokin:
		return "金";
	case Pawn:
		return "歩	";
	case SideMover:
		return "燕	";
	case PloddingOx:
		return "牛";
	case LiberatedHorse:
		return "風";
	case HeavenlyHorse:
		return "天";
	case SwoopingOwl:
		return "鴟";
	case CloudEagle:
		return "鷲";
	case StruttingCrow:
		return "烏";
	case FlyingFalcon:
		return "鷹";
	case FlyingCock:
		return "鶏";
	case RaidingFalcon:
		return "延";
	case FlyingGoose:
		return "鳫";
	case ClimbingMonkey:
		return "猿	";
	case Silver:
		return "鹿";
	case BlindDog:
		return "犬";
	case Gold:
		return "狼";
	case Elephant:
		return "猪";
	case BearEyes:
		return "熊";
	case RunningRabbit:
		return "兎";
	case TreacherousFox:
		return "狐";
	case TenaciousFalcon:
		return "鶏	鷹";
	default:
		return "";
	}
}

std::string WaShogiPiece::GetKanjiImageFileName()
{
	return GetImageFileName();
}
