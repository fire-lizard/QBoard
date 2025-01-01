#include "ChuShogiPiece.h"

ChuShogiPiece::ChuShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
	_hasMovedOnce = false;
}

ChuShogiPiece::~ChuShogiPiece()
{
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
		_pieceType = Tokin;
		break;
	default:
		break;
	}
}

std::string ChuShogiPiece::StringCode()
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

std::string ChuShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return _basePieceType == Elephant ? "太" : _pieceColour == Black ? "王" : "玉";
	case Lion:
		return "獅";
	case Queen:
		return "奔";
	case DragonKing:
		return "竜";
	case DragonHorse:
		return "馬";
	case Rook:
		return "飛";
	case Bishop:
		return "角";
	case VerticalMover:
		return "竪";
	case SideMover:
		return "横";
	case Cannon:
		return "反";
	case Lance:
		return "香";
	case Kylin:
		return "麒";
	case Phoenix:
		return "鳳";
	case Elephant:
		return "酔";
	case BlindTiger:
		return "虎";
	case Gold:
		return "金";
	case Tokin:
		return "と";
	case Silver:
		return "銀";
	case Copper:
		return "銅";
	case FerociousLeopard:
		return "豹";
	case Cobra:
		return "仲";
	case Pawn:
		return "歩";
	case Eagle:
		return "鷲";
	case Unicorn:
		return "鷹";
	case NarrowQueen:
		return "牛";
	case SleepingQueen:
		return "猪";
	case FlyingStag:
		return "鹿";
	case WhiteHorse:
		return "駒";
	case Whale:
		return "鯨";
	default:
		return "";
	}
}

void ChuShogiPiece::MoveOnce()
{
	_hasMovedOnce = true;
}

void ChuShogiPiece::EndMove()
{
	_hasMovedOnce = false;
}

bool ChuShogiPiece::HasMovedOnce() const
{
	return _hasMovedOnce;
}
