#include "WaShogiPiece.h"

WaShogiPiece::WaShogiPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

WaShogiPiece::~WaShogiPiece()
{
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
