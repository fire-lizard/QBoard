#include "ChuShogiPiece.h"

ChuShogiPiece::ChuShogiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted) : Piece(pieceType, pieceColour, isPromoted)
{
}

ChuShogiPiece::~ChuShogiPiece()
{
	//dtor
}

void ChuShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case DragonKing:
		_pieceType = Eagle;
		break;
	case DragonHorse:
		_pieceType = Unicorn;
		break;
	case Rook:
		_pieceType = DragonKing;
		break;
	case Bishop:
		_pieceType = DragonHorse;
		break;
	case VerticalMover:
		_pieceType = NarrowQueen;
		break;
	case SideMover:
		_pieceType = SleepingQueen;
		break;
	case Cannon:
		_pieceType = Whale;
		break;
	case Lance:
		_pieceType = WhiteHorse;
		break;
	case Kylin:
		_pieceType = Lion;
		break;
	case Phoenix:
		_pieceType = Queen;
		break;
	case Elephant:
		_pieceType = King;
		break;
	case BlindTiger:
		_pieceType = FlyingStag;
		break;
	case Gold:
		_pieceType = Rook;
		break;
	case Silver:
		_pieceType = VerticalMover;
		break;
	case Copper:
		_pieceType = SideMover;
		break;
	case FerociousLeopard:
		_pieceType = Bishop;
		break;
	case Cobra:
		_pieceType = Elephant;
		break;
	case Pawn:
		_pieceType = Gold;
		break;
	default:
		break;
	}
}

string ChuShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case Lion:
		return "N";
	case Queen:
		return "Q";
	case DragonKing:
		return "D";
	case DragonHorse:
		return "H";
	case Rook:
		return "R";
	case Bishop:
		return "B";
	case VerticalMover:
		return "V";
	case SideMover:
		return "S";
	case Cannon:
		return "A";
	case Lance:
		return "L";
	case Kylin:
		return "O";
	case Phoenix:
		return "X";
	case Elephant:
		return "E";
	case BlindTiger:
		return "T";
	case Gold:
		return "G";
	case Silver:
		return "S";
	case Copper:
		return "C";
	case FerociousLeopard:
		return "F";
	case Cobra:
		return "I";
	case Pawn:
		return "P";
	case Eagle:
		return "+D";
	case Unicorn:
		return "+H";
	case NarrowQueen:
		return "+V";
	case SleepingQueen:
		return "+M";
	case FlyingStag:
		return "+T";
	case WhiteHorse:
		return "+L";
	case Whale:
		return "+A";
	default:
		return "";
	}
}
