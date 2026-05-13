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
	case ReverseChariot:
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
		_pieceType = Prince;
		break;
	case Tiger:
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
	case Leopard:
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
	case Prince:
		return "+E";
	case Lion:
		return _basePieceType == Kylin ? "+O" : "N";
	case Queen:
		return _basePieceType == Phoenix ? "+X" : "Q";
	case DragonKing:
		return _basePieceType == Rook ? "+R" : "D";
	case DragonHorse:
		return _basePieceType == Bishop ? "+B" : "H";
	case Rook:
		return _basePieceType == Gold ? "+G": "R";
	case Bishop:
		return _basePieceType == Leopard ? "+F" : "B";
	case VerticalMover:
		return _basePieceType == Silver ? "+S" : "V";
	case SideMover:
		return _basePieceType == Copper ? "+C" : "M";
	case ReverseChariot:
		return "A";
	case Lance:
		return "L";
	case Kylin:
		return "O";
	case Phoenix:
		return "X";
	case Elephant:
		return _basePieceType == GoBetween ? "+I" : "E";
	case Tiger:
		return "T";
	case Gold:
		return "G";
	case Silver:
		return "S";
	case Copper:
		return "C";
	case Leopard:
		return "F";
	case GoBetween:
		return "I";
	case Pawn:
		return "P";
	case Tokin:
		return "+P";
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

PieceType ChuShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"K", King},
		{"N", Lion},
		{"Q", Queen},
		{"D", DragonKing},
		{"H", DragonHorse},
		{"R", Rook},
		{"+R", Rook},
		{"B", Bishop},
		{"+B", Bishop},
		{"V", VerticalMover},
		{"M", SideMover},
		{"A", ReverseChariot},
		{"L", Lance},
		{"O", Kylin},
		{"+O", Kylin},
		{"X", Phoenix},
		{"+X", Phoenix},
		{"E", Elephant},
		{"T", Tiger},
		{"G", Gold},
		{"+G", Gold},
		{"S", Silver},
		{"+S", Silver},
		{"C", Copper},
		{"+C", Copper},
		{"F", Leopard},
		{"+F", Leopard},
		{"I", GoBetween},
		{"+I", GoBetween},
		{"P", Pawn},
		{"+P", Tokin},
		{"+D", Eagle},
		{"+H", Unicorn},
		{"+V", FlyingOx},
		{"+M", FreeBoar},
		{"+T", FlyingStag},
		{"+L", WhiteHorse},
		{"+A", Whale},
		{"+E", Prince}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}

std::string ChuShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return _pieceColour == White ? "王" : "玉";
	case Prince:
		return "太";
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
	case ReverseChariot:
		return "反";
	case Lance:
		return "香";
	case Kylin:
		return "麒";
	case Phoenix:
		return "鳳";
	case Elephant:
		return "酔";
	case Tiger:
		return "虎";
	case Gold:
		return "金";
	case Tokin:
		return "と";
	case Silver:
		return "銀";
	case Copper:
		return "銅";
	case Leopard:
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
