#include "WaShogiPiece.h"

WaShogiPiece::WaShogiPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

WaShogiPiece::~WaShogiPiece()
{
}

void WaShogiPiece::Promote(PieceType pieceType)
{
	IsPromoted = true;
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
