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
	case Dog:
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
		return "+S";
	case Lance:
		return "O";
	case Tokin:
		return "+P";
	case Pawn:
		return "P";
	case SideMover:
		return "S";
	case PloddingOx:
		return "+O";
	case LiberatedHorse:
		return "H";
	case HeavenlyHorse:
		return "+H";
	case SwoopingOwl:
		return "L";
	case CloudEagle:
		return "E";
	case StruttingCrow:
		return "U";
	case FlyingFalcon:
		return "F";
	case FlyingCock:
		return "C";
	case RaidingFalcon:
		return "+C";
	case FlyingGoose:
		return "G";
	case ClimbingMonkey:
		return "M";
	case Silver:
		return "V";
	case Dog:
		return "D";
	case Gold:
		return "W";
	case Elephant:
		return "+V";
	case BearEyes:
		return "+W";
	case RunningRabbit:
		return "R";
	case TreacherousFox:
		return "X";
	case TenaciousFalcon:
		return "+F";
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
		return "Liberated Horse";
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
	case Dog:
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
	if (longStringCode == "Cloud Eagle") return CloudEagle;
	if (longStringCode == "Liberated Horse") return LiberatedHorse;
	if (longStringCode == "Swooping Owl") return SwoopingOwl;
	if (longStringCode == "Strutting Crow") return StruttingCrow;
	if (longStringCode == "Flying Falcon") return FlyingFalcon;
	if (longStringCode == "Flying Cock") return FlyingCock;
	if (longStringCode == "Flying Goose") return FlyingGoose;
	if (longStringCode == "Climbing Monkey") return ClimbingMonkey;
	if (longStringCode == "Violent Stag") return Silver;
	if (longStringCode == "Violent Wolf") return Gold;
	if (longStringCode == "Blind Dog") return Dog;
	if (longStringCode == "Running Rabbit") return RunningRabbit;
	if (longStringCode == "Treacherous Fox") return TreacherousFox;
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
		return "歩";
	case SideMover:
		return "燕";
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
		return "猿";
	case Silver:
		return "鹿";
	case Dog:
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
		return "鶏鷹";
	default:
		return "";
	}
}

std::string WaShogiPiece::GetImageFileName() const
{
	std::string colour = _pieceColour == White ? "B" : "W";
	if (_isPromoted && (_pieceType == CloudEagle || _pieceType == FlyingFalcon || _pieceType == Rook
		|| _pieceType == SideMover || _pieceType == Gold || _pieceType == Silver || _pieceType == TreacherousFox))
	{
		colour += "+";
	}
	switch (_pieceType)
	{
	case King:
		return colour + "craneking.png";
	case Rook:
		return colour + "GlidingSwallow.png";
	case Lance:
		return colour + "oxcart.png";
	case Tokin:
		return colour + "GoldenBird.png";
	case Pawn:
		return colour + "SparrowPawn.png";
	case SideMover:
		return colour + "Swallowswings.png";
	case PloddingOx:
		return colour + "PloddingOx.png";
	case LiberatedHorse:
		return colour + "LiberatedHorse.png";
	case HeavenlyHorse:
		return colour + "HeavenlyHorse.png";
	case SwoopingOwl:
		return colour + "SwoopingOwl.png";
	case CloudEagle:
		return colour + "CloudEagle.png";
	case StruttingCrow:
		return colour + "StruttingCrow.png";
	case FlyingFalcon:
		return colour + "FlyingFalcon.png";
	case FlyingCock:
		return colour + "FlyingCockerel.png";
	case RaidingFalcon:
		return colour + "RaidingFalcon.png";
	case FlyingGoose:
		return colour + "FlyingGoose.png";
	case ClimbingMonkey:
		return colour + "ClimbingMonkey.png";
	case Silver:
		return colour + "ViolentStag.png";
	case Dog:
		return colour + "Blinddog.png";
	case Gold:
		return colour + "ViolentWolf.png";
	case Elephant:
		return colour + "RoamingBoar.png";
	case BearEyes:
		return colour + "BearEyes.png";
	case RunningRabbit:
		return colour + "RunningRabbit.png";
	case TreacherousFox:
		return colour + "TreacherousFox.png";
	case TenaciousFalcon:
		return colour + "TenaciousFalcon.png";
	default:
		return "";
	}
}

std::string WaShogiPiece::GetKanjiImageFileName()
{
	return GetImageFileName();
}
