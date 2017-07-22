#include "XiangqiPiece.h"

XiangqiPiece::XiangqiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted) : Piece(pieceType, pieceColour, isPromoted)
{
}

XiangqiPiece::~XiangqiPiece()
{
}

void XiangqiPiece::Promote(PieceType pieceType)
{
}

string XiangqiPiece::StringCode()
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
	case WhiteHorse:
		return "H";
	case Elephant:
		return "E";
	case Pawn:
		return "P";
	default:
		return "";
	}
}

string XiangqiPiece::AsianStringCode()
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
	case WhiteHorse:
		return _pieceColour == Black ? "馬" : "傌";
	case Elephant:
		return _pieceColour == Black ? "象" : "相";
	case Pawn:
		return _pieceColour == Black ? "卒" : "兵";
	default:
		return "";
	}
}
