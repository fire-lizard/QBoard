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
