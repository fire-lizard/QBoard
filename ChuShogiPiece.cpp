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
	case ReverseChariot:
		return "A";
	case Lance:
		return "L";
	case Kylin:
		return "O";
	case Phoenix:
		return "X";
	case Elephant:
		return "E";
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
		{"B", Bishop},
		{"V", VerticalMover},
		{"M", SideMover},
		{"A", ReverseChariot},
		{"L", Lance},
		{"O", Kylin},
		{"X", Phoenix},
		{"E", Elephant},
		{"T", Tiger},
		{"G", Gold},
		{"S", Silver},
		{"C", Copper},
		{"F", Leopard},
		{"I", GoBetween},
		{"P", Pawn},
		{"+P", Tokin},
		{"+D", Eagle},
		{"+H", Unicorn},
		{"+V", FlyingOx},
		{"+M", FreeBoar},
		{"+T", FlyingStag},
		{"+L", WhiteHorse},
		{"+A", Whale}
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

std::string ChuShogiPiece::GetKanjiImageFileName()
{
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	case King:
		return "King" + colour + ".png";
	case Prince:
		return "Prince" + colour + ".png";
	case Lion:
		return "Lion" + colour + ".png";
	case Queen:
		return "Queen" + colour + ".png";
	case DragonKing:
		return "DragonKing" + colour + ".png";
	case DragonHorse:
		return "DragonHorse" + colour + ".png";
	case Rook:
		return "Rook" + colour + ".png";
	case Bishop:
		return "Bishop" + colour + ".png";
	case VerticalMover:
		return "VerticalMover" + colour + ".png";
	case SideMover:
		return "SideMover" + colour + ".png";
	case ReverseChariot:
		return "Chariot" + colour + ".png";
	case Lance:
		return "Lance" + colour + ".png";
	case Kylin:
		return "Kirin" + colour + ".png";
	case Phoenix:
		return "Phoenix" + colour + ".png";
	case Elephant:
		return "Elephant" + colour + ".png";
	case Tiger:
		return "Tiger" + colour + ".png";
	case Gold:
	case Tokin:
		return "Gold" + colour + ".png";
	case Silver:
		return "Silver" + colour + ".png";
	case Copper:
		return "Copper" + colour + ".png";
	case Leopard:
		return "Leopard" + colour + ".png";
	case GoBetween:
		return "GoBetween" + colour + ".png";
	case Pawn:
		return "Pawn" + colour + ".png";
	case Eagle:
		return "Eagle" + colour + ".png";
	case Unicorn:
		return "Hawk" + colour + ".png";
	case FlyingOx:
		return "FlyingOx" + colour + ".png";
	case FreeBoar:
		return "FreeBoar" + colour + ".png";
	case FlyingStag:
		return "Stag" + colour + ".png";
	case WhiteHorse:
		return "White" + colour + ".png";
	case Whale:
		return "Whale" + colour + ".png";
	default:
		return "";
	}
}

std::string ChuShogiPiece::GetKanjiImageFileName2()
{
	std::string colour = _pieceColour == White ? "_piece_B_" : "_piece_W_";
	colour += _isPromoted ? "prom" : "norm";
	switch (_pieceType)
	{
	case King:
		return "Korol" + colour + ".png";
	case Prince:
		return "Kronprinc" + colour + ".png";
	case Lion:
		return "Lev" + colour + ".png";
	case Queen:
		return "Ferz" + colour + ".png";
	case DragonKing:
		return "Car_Drakon" + colour + ".png";
	case DragonHorse:
		return "Loshad" + colour + ".png";
	case Rook:
		return "Ladja" + colour + ".png";
	case Bishop:
		return "Slon" + colour + ".png";
	case VerticalMover:
		return "Vertikalnyj_hodok" + colour + ".png";
	case SideMover:
		return "Gorizontalnyj_hodok" + colour + ".png";
	case ReverseChariot:
		return "Kontrstrelka" + colour + ".png";
	case Lance:
		return "Strelka" + colour + ".png";
	case Kylin:
		return "Edinorog" + colour + ".png";
	case Phoenix:
		return "Feniks" + colour + ".png";
	case Elephant:
		return "Pjanyj_slon" + colour + ".png";
	case Tiger:
		return "Slepoj_tigr" + colour + ".png";
	case Gold:
		return "Zolotoj_general" + colour + ".png";
	case Tokin:
		return "Tokin" + colour + ".png";
	case Silver:
		return "Serebrjanyj_general" + colour + ".png";
	case Copper:
		return "Mednyj_general" + colour + ".png";
	case Leopard:
		return "JArostnyj_leopard" + colour + ".png";
	case GoBetween:
		return "Posrednik" + colour + ".png";
	case Pawn:
		return "Peshka" + colour + ".png";
	case Eagle:
		return "Parjashij_orjol" + colour + ".png";
	case Unicorn:
		return "Rogatyj_sokol" + colour + ".png";
	case FlyingOx:
		return "Letajushij_byk" + colour + ".png";
	case FreeBoar:
		return "Begajushij_vepr" + colour + ".png";
	case FlyingStag:
		return "Letajushij_olen" + colour + ".png";
	case WhiteHorse:
		return "Belyj_kon" + colour + ".png";
	case Whale:
		return "Kit" + colour + ".png";
	default:
		return "";
	}
}

std::string ChuShogiPiece::GetMnemonicImageFileName() const
{
	const std::string colour = _pieceColour == White ? "_B" : "_W";
	const std::string promo = _isPromoted ? "P" : "";
	switch (_pieceType)
	{
	case King:
		return "King" + colour + ".png";
	case Prince:
		return "Prince" + colour + ".png";
	case Lion:
		return promo + "Lion" + colour + ".png";
	case Queen:
		return promo + "FreeKing" + colour + ".png";
	case DragonKing:
		return promo + "Dragon" + colour + ".png";
	case DragonHorse:
		return promo + "Horse" + colour + ".png";
	case Rook:
		return promo + "Rook" + colour + ".png";
	case Bishop:
		return promo + "Bishop" + colour + ".png";
	case VerticalMover:
		return promo + "Vertical" + colour + ".png";
	case SideMover:
		return promo + "Side" + colour + ".png";
	case ReverseChariot:
		return "Reverse" + colour + ".png";
	case Lance:
		return "Lance" + colour + ".png";
	case Kylin:
		return "Kylin" + colour + ".png";
	case Phoenix:
		return "Phoenix" + colour + ".png";
	case Elephant:
		return promo + "Elephant" + colour + ".png";
	case Tiger:
		return "Tiger" + colour + ".png";
	case Leopard:
		return "Leopard" + colour + ".png";
	case Gold:
		return "Gold" + colour + ".png";
	case Silver:
		return "Silver" + colour + ".png";
	case Copper:
		return "Copper" + colour + ".png";
	case GoBetween:
		return "GoBetween" + colour + ".png";
	case Eagle:
		return "Eagle" + colour + ".png";
	case Unicorn:
		return "Falcon" + colour + ".png";
	case FlyingStag:
		return "Stag" + colour + ".png";
	case FreeBoar:
		return "Boar" + colour + ".png";
	case FlyingOx:
		return "Ox" + colour + ".png";
	case WhiteHorse:
		return "WHorse" + colour + ".png";
	case Whale:
		return "Whale" + colour + ".png";
	case Tokin:
		return "Tokin" + colour + ".png";
	case Pawn:
		return "Pawn" + colour + ".png";
	default:
		return "";
	}
}