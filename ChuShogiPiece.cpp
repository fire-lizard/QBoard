#include "ChuShogiPiece.h"

ChuShogiPiece::ChuShogiPiece(PieceType pieceType, PieceColour pieceColour) : ShogiPiece(pieceType, pieceColour)
{
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
		_pieceType = FlyingOx;
		break;
	case SideMover:
		_pieceType = FreeBoar;
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
	case GoBetween:
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
		return "M";
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
	case GoBetween:
		return "I";
	case Pawn:
		return "P";
	case Eagle:
		return "+D";
	case Unicorn:
		return "+H";
	case FlyingOx:
		return "+V";
	case FreeBoar:
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
	case GoBetween:
		return "仲";
	case Pawn:
		return "歩";
	case Eagle:
		return "鷲";
	case Unicorn:
		return "鷹";
	case FlyingOx:
		return "牛";
	case FreeBoar:
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

void ChuShogiPiece::replaceSubstring(std::string& str, const std::string& from, const std::string& to)
{
	size_t startPos = 0;
	while ((startPos = str.find(from, startPos)) != std::string::npos)
	{
		str.replace(startPos, from.length(), to);
		startPos += to.length(); // Move past the replacement
	}
}

std::string ChuShogiPiece::GetKanjiImageFileName()
{
	std::string imageFileName = GetImageFileName();
	if (_isPromoted)
	{
		constexpr PieceType pieces[] = { Bishop, Rook, Queen, Lion, Elephant, DragonHorse, DragonKing, SideMover, VerticalMover };

		if (std::find(std::begin(pieces), std::end(pieces), _pieceType) != std::end(pieces))
		{
			const std::string colour = _pieceColour == White ? "White" : "Black";
			replaceSubstring(imageFileName, colour, colour + "Promo");
		}
	}
	return imageFileName;
}
