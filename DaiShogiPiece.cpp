#include "DaiShogiPiece.h"

DaiShogiPiece::DaiShogiPiece(PieceType pieceType, PieceColour pieceColour) : ChuShogiPiece(pieceType, pieceColour)
{
}

DaiShogiPiece::~DaiShogiPiece()
{
}

void DaiShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case Iron:
	case Stone:
	case AngryBoar:
	case ViolentOx:
	case FlyingDragon:
	case EvilWolf:
	case CatSword:
	case Knight:
		_pieceType = Gold;
		break;
	default:
		ChuShogiPiece::Promote(pieceType);
		break;
	}
}

std::string DaiShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case Iron:
		return "J";
	case Stone:
		return "U";
	case AngryBoar:
		return "A'";
	case ViolentOx:
		return "V'";
	case FlyingDragon:
		return "F'";
	case EvilWolf:
		return "W";
	case CatSword:
		return "Z";
	case Knight:
		return "Y";
	case WaterBuffalo:
		return "W!";
	case Gold:
		switch (_basePieceType)
		{
		case Iron:
			return "+J";
		case Stone:
			return "+U";
		case AngryBoar:
			return "+A'";
		case ViolentOx:
			return "+V'";
		case FlyingDragon:
			return "+F'";
		case EvilWolf:
			return "+W";
		case CatSword:
			return "+Z";
		case Knight:
			return "+Y";
		default:
			return "G";
		}
	default:
		return ChuShogiPiece::StringCode();
	}
}

PieceType DaiShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"J", Iron},
		{"U", Stone},
		{"A'", AngryBoar},
		{"V'", ViolentOx},
		{"F'", FlyingDragon},
		{"W", EvilWolf},
		{"Z", CatSword},
		{"Y", Knight},
		{"W!", WaterBuffalo},
		{"+J", Iron},
		{"+U", Stone},
		{"+A'", AngryBoar},
		{"+V'", ViolentOx},
		{"+F'", FlyingDragon},
		{"+W", EvilWolf},
		{"+Z", CatSword},
		{"+Y", Knight},
		{"+W!", WaterBuffalo}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : ChuShogiPiece::FromStringCode(code);
}

std::string DaiShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case Iron:
		return "鉄";
	case Stone:
		return "石";
	case AngryBoar:
		return "猪";
	case ViolentOx:
		return "牛";
	case FlyingDragon:
		return "龍";
	case EvilWolf:
		return "狼";
	case CatSword:
		return "猫";
	case Knight:
		return "桂";
	default:
		return ChuShogiPiece::KanjiStringCode();
	}
}

void DaiShogiPiece::replaceSubstring(std::string& str, const std::string& from, const std::string& to)
{
	size_t startPos = 0;
	while ((startPos = str.find(from, startPos)) != std::string::npos)
	{
		str.replace(startPos, from.length(), to);
		startPos += to.length(); // Move past the replacement
	}
}
