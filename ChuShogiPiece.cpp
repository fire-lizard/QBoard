#include "ChuShogiPiece.h"

ChuShogiPiece::ChuShogiPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

ChuShogiPiece::~ChuShogiPiece()
{
	//dtor
}

void ChuShogiPiece::Promote()
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
