#include "XiangqiPiece.h"

XiangqiPiece::XiangqiPiece(PieceType pieceType, PieceColour pieceColour) : KanjiPiece(pieceType, pieceColour)
{
}

XiangqiPiece::~XiangqiPiece()
{
}

void XiangqiPiece::Promote(PieceType pieceType)
{
}

std::string XiangqiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case Silver:
		return "A";
	case Rook:
		return "R";
	case Cannon:
		return "C";
	case Knight:
		return "H";
	case Elephant:
		return "E";
	case Pawn:
		return "P";
	default:
		return "";
	}
}

PieceType XiangqiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"K", King},
		{"A", Silver},
		{"R", Rook},
		{"C", Cannon},
		{"N", Knight},
		{"H", Knight},
		{"B", Elephant},
		{"E", Elephant},
		{"P", Pawn}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}

std::string XiangqiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return _pieceColour == Black ? "將" : "帥";
	case Silver:
		return _pieceColour == Black ? "士" : "仕";
	case Rook:
		return _pieceColour == Black ? "車" : "俥";
	case Cannon:
		return _pieceColour == Black ? "砲" : "炮";
	case Knight:
		return _pieceColour == Black ? "馬" : "傌";
	case Elephant:
		return _pieceColour == Black ? "象" : "相";
	case Pawn:
		return _pieceColour == Black ? "卒" : "兵";
	default:
		return "";
	}
}

std::string XiangqiPiece::GetKanjiImageFileName()
{
	const std::string colour = _pieceColour == White ? "r" : "b";
	switch (_pieceType)
	{
	case King:
		return colour + "king.png";
	case Rook:
		return colour + "chariot.png";
	case Cannon:
		return colour + "cannon.png";
	case Elephant:
		return colour + "elephant.png";
	case Silver:
		return colour + "advisor.png";
	case Pawn:
		return colour + "pawn.png";
	case Knight:
		return colour + "horse.png";
	default:
		return "";
	}
}

std::string XiangqiPiece::GetKanjiImageFileName2()
{
	return GetKanjiImageFileName();
}