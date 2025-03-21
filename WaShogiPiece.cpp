﻿#include "WaShogiPiece.h"

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
		return _basePieceType == FlyingGoose ? "+G" : "S";
	case PloddingOx:
		return "+O";
	case LiberatedHorse:
		return "H";
	case HeavenlyHorse:
		return "+H";
	case SwoopingOwl:
		return "L";
	case CloudEagle:
		return _basePieceType == SwoopingOwl ? "+L" : "E";
	case StruttingCrow:
		return "U";
	case FlyingFalcon:
		return _basePieceType == StruttingCrow ? "+U" : "F";
	case FlyingCock:
		return "C";
	case RaidingFalcon:
		return "+C";
	case FlyingGoose:
		return "G";
	case ClimbingMonkey:
		return "M";
	case Silver:
		return _basePieceType == ClimbingMonkey ? "+M" : "V";
	case Dog:
		return "D";
	case Gold:
		return _basePieceType == Dog ? "+D" : "W";
	case Elephant:
		return "+V";
	case BearEyes:
		return "+W";
	case RunningRabbit:
		return "R";
	case TreacherousFox:
		return _basePieceType == RunningRabbit ? "+R" : "X";
	case TenaciousFalcon:
		return "+F";
	default:
		return "";
	}
}

PieceType WaShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"K", King},
		{"+S", Rook},
		{"O", Lance},
		{"+P", Tokin},
		{"P", Pawn},
		{"S", SideMover},
		{"+O", PloddingOx},
		{"H", LiberatedHorse},
		{"+H", HeavenlyHorse},
		{"L", SwoopingOwl},
		{"+L", SwoopingOwl},
		{"E", CloudEagle},
		{"U", StruttingCrow},
		{"+U", StruttingCrow},
		{"F", FlyingFalcon},
		{"C", FlyingCock},
		{"+C", RaidingFalcon},
		{"G", FlyingGoose},
		{"+G", FlyingGoose},
		{"M", ClimbingMonkey},
		{"+M", ClimbingMonkey},
		{"V", Silver},
		{"D", Dog},
		{"+D", Dog},
		{"W", Gold},
		{"+V", Elephant},
		{"+W", BearEyes},
		{"R", RunningRabbit},
		{"+R", RunningRabbit},
		{"X", TreacherousFox},
		{"+F", TenaciousFalcon}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}

std::string WaShogiPiece::ToStringCode(PieceType piece)
{
	static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
	{ King,           "K"  },
	{ Rook,           "+S" },
	{ Lance,          "O"  },
	{ Tokin,          "+P" },
	{ Pawn,           "P"  },
	{ SideMover,      "S"  },
	{ PloddingOx,     "+O" },
	{ LiberatedHorse, "H"  },
	{ HeavenlyHorse,  "+H" },
	{ SwoopingOwl,    "L"  },
	{ CloudEagle,     "E"  },
	{ StruttingCrow,  "U"  },
	{ FlyingFalcon,   "F"  },
	{ FlyingCock,     "C"  },
	{ RaidingFalcon,  "+C" },
	{ FlyingGoose,    "G"  },
	{ ClimbingMonkey, "M"  },
	{ Silver,         "V"  },
	{ Dog,            "D"  },
	{ Gold,           "W"  },
	{ Elephant,       "+V" },
	{ BearEyes,       "+W" },
	{ RunningRabbit,  "R"  },
	{ TreacherousFox, "X"  },
	{ TenaciousFalcon,"+F" }
	};

	const auto it = pieceTypeToCode.find(piece);
	return it != pieceTypeToCode.end() ? it->second : "";
}

std::string WaShogiPiece::Description() const
{
	return PieceType2Description(_pieceType);
}

std::string WaShogiPiece::PieceType2Description(PieceType pieceType)
{
	switch (pieceType)
	{
	case King: return "Crane King";
	case Rook: return "Gliding Swallow";
	case SideMover: return "Swallow's Wings";
	case Lance: return "Ox Cart";
	case Elephant: return "Roaming Boar";
	case Gold: return "Violent Wolf";
	case Silver: return "Violent Stag";
	case Pawn: return "Sparrow Pawn";
	case Tokin: return "Golden Bird";
	case PloddingOx: return "Plodding Ox";
	case LiberatedHorse: return "Liberated Horse";
	case HeavenlyHorse: return "Heavenly Horse";
	case SwoopingOwl: return "Swooping Owl";
	case CloudEagle: return "Cloud Eagle";
	case StruttingCrow: return "Strutting Crow";
	case FlyingFalcon: return "Flying Falcon";
	case FlyingCock: return "Flying Cock";
	case RaidingFalcon: return "Raiding Falcon";
	case FlyingGoose: return "Flying Goose";
	case ClimbingMonkey: return "Climbing Monkey";
	case Dog: return "Blind Dog";
	case BearEyes: return "Bear Eyes";
	case RunningRabbit: return "Running Rabbit";
	case TreacherousFox: return "Treacherous Fox";
	case TenaciousFalcon: return "Tenacious Falcon";
	default: return "";
	}
}

PieceType WaShogiPiece::Description2PieceType(const std::string& description)
{
	if (description == "Crane King")        return King;
	if (description == "Gliding Swallow")   return Rook;
	if (description == "Swallow's Wings")   return SideMover;
	if (description == "Ox Cart")           return Lance;
	if (description == "Roaming Boar")      return Elephant;
	if (description == "Violent Wolf")      return Gold;
	if (description == "Violent Stag")      return Silver;
	if (description == "Sparrow Pawn")      return Pawn;
	if (description == "Golden Bird")       return Tokin;
	if (description == "Plodding Ox")       return PloddingOx;
	if (description == "Liberated Horse")   return LiberatedHorse;
	if (description == "Heavenly Horse")    return HeavenlyHorse;
	if (description == "Swooping Owl")      return SwoopingOwl;
	if (description == "Cloud Eagle")       return CloudEagle;
	if (description == "Strutting Crow")    return StruttingCrow;
	if (description == "Flying Falcon")     return FlyingFalcon;
	if (description == "Flying Cock")       return FlyingCock;
	if (description == "Raiding Falcon")    return RaidingFalcon;
	if (description == "Flying Goose")      return FlyingGoose;
	if (description == "Climbing Monkey")   return ClimbingMonkey;
	if (description == "Blind Dog")         return Dog;
	if (description == "Bear Eyes")         return BearEyes;
	if (description == "Running Rabbit")    return RunningRabbit;
	if (description == "Treacherous Fox")   return TreacherousFox;
	if (description == "Tenacious Falcon")  return TenaciousFalcon;
	return None;
}

std::string WaShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return "靏玉";
	case Rook:
		return "燕行";
	case Lance:
		return "牛車";
	case Tokin:
		return "金鳥";
	case Pawn:
		return "萑歩";
	case SideMover:
		return "燕羽";
	case PloddingOx:
		return "歬牛";
	case LiberatedHorse:
		return "風馬";
	case HeavenlyHorse:
		return "天馬";
	case SwoopingOwl:
		return "鴟行";
	case CloudEagle:
		return "雲鷲";
	case StruttingCrow:
		return "烏行";
	case FlyingFalcon:
		return "飛鷹";
	case FlyingCock:
		return "鶏飛";
	case RaidingFalcon:
		return "延鷹";
	case FlyingGoose:
		return "鳫飛";
	case ClimbingMonkey:
		return "登猿";
	case Silver:
		return "猛鹿";
	case Dog:
		return "盲犬";
	case Gold:
		return "猛狼";
	case Elephant:
		return "行猪";
	case BearEyes:
		return "熊眼";
	case RunningRabbit:
		return "走兎";
	case TreacherousFox:
		return "隠狐";
	case TenaciousFalcon:
		return "奚力 鷹";
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
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	case King:
		return "CraneKing" + colour + ".png";
	case Rook:
		return "GlidingSwallow" + colour + ".png";
	case Lance:
		return "OxCart" + colour + ".png";
	case Tokin:
		return "GoldenBird" + colour + ".png";
	case Pawn:
		return "SparrowPawn" + colour + ".png";
	case SideMover:
		return "SwallowWing" + colour + ".png";
	case PloddingOx:
		return "PloddingOx" + colour + ".png";
	case LiberatedHorse:
		return "LiberatedHorse" + colour + ".png";
	case HeavenlyHorse:
		return "HeavenlyHorse" + colour + ".png";
	case SwoopingOwl:
		return "SwoopingKite" + colour + ".png";
	case CloudEagle:
		return "CloudEagle" + colour + ".png";
	case StruttingCrow:
		return "StruttingCrow" + colour + ".png";
	case FlyingFalcon:
		return "FlyingHawk" + colour + ".png";
	case FlyingCock:
		return "FlyingCock" + colour + ".png";
	case RaidingFalcon:
		return "RaidingHawk" + colour + ".png";
	case FlyingGoose:
		return "FlyingGoose" + colour + ".png";
	case ClimbingMonkey:
		return "ClimbingMonkey" + colour + ".png";
	case Silver:
		return "ViolentStag" + colour + ".png";
	case Dog:
		return "BlindDog" + colour + ".png";
	case Gold:
		return "ViolentWolf" + colour + ".png";
	case Elephant:
		return "RoamingBoar" + colour + ".png";
	case BearEyes:
		return "BearEye" + colour + ".png";
	case RunningRabbit:
		return "RunningRabbit" + colour + ".png";
	case TreacherousFox:
		return "TreacherousFox" + colour + ".png";
	case TenaciousFalcon:
		return "TenaciousHawk" + colour + ".png";
	default:
		return "";
	}
}

std::string WaShogiPiece::GetKanjiImageFileName2()
{
	return GetKanjiImageFileName();
}