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
		return "D'";
	case MultiGeneral:
		return "+D'";
	case ViceGeneral:
		return _basePieceType == BishopGeneral ? "+B!" : "V!";
	case GreatGeneral:
		return _basePieceType == RookGeneral ? "+R!" : "Q!";
	case BishopGeneral:
		return _basePieceType == Unicorn ? "+F!" : "B!";
	case RookGeneral:
		return _basePieceType == Eagle ? "+E!" : "R!";
	case FreeEagle:
		return _basePieceType == Queen ? "+Q" : "Q'";
	case LionHawk:
		return _basePieceType == Lion ? "+N" : "H!";
	case SideSoldier:
		return _basePieceType == Knight ? "+Y" : "S'";
	case VerticalSoldier:
		return _basePieceType == Iron ? "+J" : "V'";
	case ChariotSoldier:
		return _basePieceType == VerticalSoldier ? "+V'" : "C!";
	case HeavenlyTetrarch:
		return "+C!";
	case WaterBuffalo:
		return _basePieceType == SideSoldier ? "+S'" : "W!";
	case FireDemon:
		return _basePieceType == WaterBuffalo ? "+W!" : "D!";
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
		{"D'", Dog},
		{"+D'", MultiGeneral},
		{"V!", ViceGeneral},
		{"Q!", GreatGeneral},
		{"B!", BishopGeneral},
		{"+B!", BishopGeneral},
		{"R!", RookGeneral},
		{"+R!", RookGeneral},
		{"Q'", FreeEagle},
		{"H!", LionHawk},
		{"S'", SideSoldier},
		{"+S'", SideSoldier},
		{"V'", VerticalSoldier},
		{"+V'", VerticalSoldier},
		{"C!", ChariotSoldier},
		{"+C!", HeavenlyTetrarch},
		{"D!", FireDemon},
		{"F!", Unicorn},
		{"+F!", Unicorn},
		{"E!", Eagle},
		{"+E!", Eagle},
		{"+Q", Queen},
		{"+N", Lion}
	};

	const auto it = codeToPieceType.find(code);
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
