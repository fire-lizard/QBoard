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
