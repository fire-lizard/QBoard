#include "ShogiPiece.h"

ShogiPiece::ShogiPiece(PieceType pieceType, PieceColour pieceColour) : KanjiPiece(pieceType, pieceColour)
{
}

ShogiPiece::~ShogiPiece()
{
}

void ShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	case Rook:
		_pieceType = DragonKing;
		break;
	case Bishop:
		_pieceType = DragonHorse;
		break;
	case Elephant:
		_pieceType = King;
		break;
	case Lance:
		_pieceType = PromotedLance;
		break;
	case Silver:
		_pieceType = PromotedSilver;
		break;
	case Knight:
		_pieceType = PromotedKnight;
		break;
	case Pawn:
		_pieceType = Tokin;
		break;
	default:
		break;
	}
}

std::string ShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case DragonKing:
		return "D";
	case DragonHorse:
		return "H";
	case Rook:
		return "R";
	case Bishop:
		return "B";
	case Lance:
		return "L";
	case Silver:
		return "S";
	case Gold:
		return "G";
	case Knight:
		return "N";
	case Pawn:
		return "P";
	case Elephant:
		return "E";
	default:
		return "";
	}
}

PieceType ShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"K", King},
		{"D", DragonKing},
		{"H", DragonHorse},
		{"R", Rook},
		{"B", Bishop},
		{"L", Lance},
		{"S", Silver},
		{"G", Gold},
		{"N", Knight},
		{"P", Pawn},
		{"E", Elephant}
	};

	auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}

std::string ShogiPiece::LongStringCode() const
{
	switch (_pieceType)
	{
	case Rook:
		return "Rook";
	case Bishop:
		return "Bishop";
	case Lance:
		return "Lance";
	case Silver:
		return "Silver";
	case Gold:
		return "Gold";
	case Knight:
		return "Knight";
	case Pawn:
		return "Pawn";
	default:
		return "";
	}
}

PieceType ShogiPiece::LongStringCode2PieceType(const std::string& longStringCode)
{
	if (longStringCode == "Rook") return Rook;
	if (longStringCode == "Bishop") return Bishop;
	if (longStringCode == "Lance") return Lance;
	if (longStringCode == "Silver") return Silver;
	if (longStringCode == "Gold") return Gold;
	if (longStringCode == "Knight") return Knight;
	if (longStringCode == "Pawn") return Pawn;
	return None;
}

std::string ShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return _basePieceType == Elephant ? "太" : _pieceColour == Black ? "王" : "玉";
	case DragonKing:
		return "竜";
	case DragonHorse:
		return "馬";
	case Rook:
		return "飛";
	case Bishop:
		return "角";
	case Lance:
		return "香";
	case Silver:
		return "銀";
	case Gold:
		return "金";
	case Tokin:
		return "と";
	case PromotedLance:
		return "杏";
	case PromotedKnight:
		return "圭";
	case PromotedSilver:
		return "全";
	case Knight:
		return "桂";
	case Pawn:
		return "歩";
	case Elephant:
		return "酔";
	default:
		return "";
	}
}

std::string ShogiPiece::GetKanjiImageFileName()
{
	return GetImageFileName();
}
