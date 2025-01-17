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
		return "N";
	case Elephant:
		return "B";
	case Pawn:
		return "P";
	default:
		return "";
	}
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
