#include "TenjikuShogiPiece.h"

TenjikuShogiPiece::TenjikuShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

TenjikuShogiPiece::~TenjikuShogiPiece()
{
}

void TenjikuShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case BishopGeneral:
		_pieceType = ViceGeneral;
		break;
	case RookGeneral:
		_pieceType = GreatGeneral;
		break;
	case Dog:
		_pieceType = MultiGeneral;
		break;
	case SideSoldier:
		_pieceType = WaterBuffalo;
		break;
	case VerticalSoldier:
		_pieceType = ChariotSoldier;
		break;
	case ChariotSoldier:
		_pieceType = HeavenlyTetrarch;
		break;
	case WaterBuffalo:
		_pieceType = FireDemon;
		break;
	case Queen:
		_pieceType = FreeEagle;
		break;
	case Iron:
		_pieceType = VerticalSoldier;
		break;
	case Knight:
		_pieceType = SideSoldier;
		break;
	case Lion:
		_pieceType = LionHawk;
		break;
	case Unicorn:
		_pieceType = BishopGeneral;
		break;
	case Eagle:
		_pieceType = RookGeneral;
		break;
	default:
		DaiShogiPiece::Promote(pieceType);
		break;
	}
}

std::string TenjikuShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case Dog:
		return "D";
	case MultiGeneral:
		return "+D";
	case ViceGeneral:
		return "V!";
	case GreatGeneral:
		return "Q!";
	case BishopGeneral:
		return "B!";
	case RookGeneral:
		return "R!";
	case FreeEagle:
		return "Q'";
	case LionHawk:
		return "H!";
	case SideSoldier:
		return "S'";
	case VerticalSoldier:
		return "V'";
	case ChariotSoldier:
		return "C!";
	case HeavenlyTetrarch:
		return "+C!";
	case WaterBuffalo:
		return "W!";
	case FireDemon:
		return "D!";
	case Unicorn:
		return "F!";
	case Eagle:
		return "E!";
	default:
		return DaiShogiPiece::StringCode();
	}
}

PieceType TenjikuShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"D", Dog},
		{"+D", MultiGeneral},
		{"V!", ViceGeneral},
		{"Q!", GreatGeneral},
		{"B!", BishopGeneral},
		{"R!", RookGeneral},
		{"Q'", FreeEagle},
		{"H!", LionHawk},
		{"S'", SideSoldier},
		{"V'", VerticalSoldier},
		{"C!", ChariotSoldier},
		{"+C!", HeavenlyTetrarch},
		{"W!", WaterBuffalo},
		{"D!", FireDemon},
		{"F!", Unicorn},
		{"E!", Eagle}
	};

	auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : DaiShogiPiece::FromStringCode(code);
}

std::string TenjikuShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case ViceGeneral:
		return "副";
	case GreatGeneral:
		return "大";
	case BishopGeneral:
		return "用";
	case RookGeneral:
		return "升";
	case MultiGeneral:
		return "雜";
	case Dog:
		return "犬";
	case FreeEagle:
		return "就";
	case LionHawk:
		return "師";
	case SideSoldier:
		return "黄";
	case VerticalSoldier:
		return "立";
	case ChariotSoldier:
		return "車";
	case WaterBuffalo:
		return "水";
	case HeavenlyTetrarch:
		return "天";
	case FireDemon:
		return "火";
	default:
		return DaiShogiPiece::KanjiStringCode();
	}
}

std::string TenjikuShogiPiece::GetImageFileName() const
{
	const std::string colour = _pieceColour == White ? "_B" : "_W";
	const std::string promo = _isPromoted ? "P" : "";
	switch (_pieceType)
	{
	case ViceGeneral:
		return "ViceGeneral" + colour + ".png";
	case GreatGeneral:
		return "GreatGeneral" + colour + ".png";
	case BishopGeneral:
		return promo + "BishopGeneral" + colour + ".png";
	case RookGeneral:
		return promo + "RookGeneral" + colour + ".png";
	case MultiGeneral:
		return "Multi-General" + colour + "2.png";
	case Dog:
		return promo + "Dog" + colour + ".png";
	case FreeEagle:
		return "FreeEagle" + colour + ".png";
	case LionHawk:
		return "Lion-Hawk" + colour + ".png";
	case SideSoldier:
		return promo + "SideSoldier" + colour + ".png";
	case VerticalSoldier:
		return promo + "VerticalSoldier" + colour + ".png";
	case ChariotSoldier:
		return promo + "ChariotSoldier" + colour + ".png";
	case Phoenix:
		return "Phoenix" + colour + ".png";
	case Elephant:
		return promo + "Elephant" + colour + ".png";
	case Tiger:
		return "Tiger" + colour + ".png";
	case Leopard:
		return "Leopard" + colour + ".png";
	case WaterBuffalo:
		return promo + "WaterBuffalo" + colour + ".png";
	case HeavenlyTetrarch:
		return "Heaven" + colour + ".png";
	case FireDemon:
		return "FireDemon" + colour + ".png";
	case Queen:
		return promo + "Queen" + colour + ".png";
	case Knight:
		return "Knight" + colour + ".png";
	case Iron:
		return "Iron" + colour + ".png";
	case Tokin:
		return promo + "Gold" + colour + ".png";
	case FreeBoar:
		return "FBoar" + colour + ".png";
	case FlyingOx:
		return "pOx" + colour + ".png";
	default:
		return GetMnemonicImageFileName();
	}
}

std::string TenjikuShogiPiece::GetKanjiImageFileName()
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
	case Knight:
		return "Knight" + colour + ".png";
	case VerticalMover:
		return "VerticalMover" + colour + ".png";
	case SideMover:
		return "SideMover" + colour + ".png";
	case Cannon:
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
	case ViolentOx:
		return "ViolentOx" + colour + ".png";
	case FlyingDragon:
		return "FlyingDragon" + colour + ".png";
	case AngryBoar:
		return "AngryBoar" + colour + ".png";
	case CatSword:
		return "CatSword" + colour + ".png";
	case EvilWolf:
		return "EvilWolf" + colour + ".png";
	case Iron:
		return "Iron" + colour + ".png";
	case Stone:
		return "Stone" + colour + ".png";
	case ViceGeneral:
		return "Vice" + colour + ".png";
	case GreatGeneral:
		return "Great" + colour + ".png";
	case BishopGeneral:
		return "BishopGeneral" + colour + ".png";
	case RookGeneral:
		return "RookGeneral" + colour + ".png";
	case MultiGeneral:
		return "Multi" + colour + ".png";
	case Dog:
		return "Dog" + colour + ".png";
	case FreeEagle:
		return "FreeEagle" + colour + ".png";
	case LionHawk:
		return "LionHawk" + colour + ".png";
	case SideSoldier:
		return "SideSoldier" + colour + ".png";
	case VerticalSoldier:
		return "VerticalSoldier" + colour + ".png";
	case ChariotSoldier:
		return "ChariotSoldier" + colour + ".png";
	case WaterBuffalo:
		return "WaterBuffalo" + colour + ".png";
	case HeavenlyTetrarch:
		return "HeavenlyTetrarch" + colour + ".png";
	case FireDemon:
		return "FireDemon" + colour + ".png";
	default:
		return "";
	}
}
