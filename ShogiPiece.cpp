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
		_pieceType = Prince;
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
	case Prince:
		return "+E";
	case DragonKing:
		return "+R";
	case DragonHorse:
		return "+B";
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
	case Tokin:
		return "+P";
	case PromotedLance:
		return "+L";
	case PromotedKnight:
		return "+N";
	case PromotedSilver:
		return "+S";
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
		{"+R", DragonKing},
		{"+B", DragonHorse},
		{"R", Rook},
		{"B", Bishop},
		{"L", Lance},
		{"+L", PromotedLance},
		{"S", Silver},
		{"+S", PromotedSilver},
		{"G", Gold},
		{"N", Knight},
		{"+N", PromotedKnight},
		{"P", Pawn},
		{"+P", Tokin},
		{"E", Elephant},
		{"+E", Prince}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}

std::string ShogiPiece::ToStringCode(PieceType piece)
{
	static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
		{King, "K"},
		{DragonKing, "+R"},
		{DragonHorse, "+B"},
		{Rook, "R"},
		{Bishop, "B"},
		{Lance, "L"},
		{PromotedLance, "+L"},
		{Silver, "S"},
		{PromotedSilver, "+S"},
		{Gold, "G"},
		{Knight, "N"},
		{PromotedKnight, "+N"},
		{Pawn, "P"},
		{Tokin, "+P"},
		{Elephant, "E"},
		{Prince, "+E"}
	};

	const auto it = pieceTypeToCode.find(piece);
	return it != pieceTypeToCode.end() ? it->second : "";
}

std::string ShogiPiece::Description() const
{
	return PieceType2Description(_pieceType);
}

std::string ShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	case King:
		return _pieceColour == White ? "王" : "玉";
	case Prince:
		return "太";
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
	std::string imageFileName = GetImageFileName();
	if (_isPromoted)
	{
		const std::string colour = _pieceColour == White ? "White" : "Black";
		if (_pieceType == DragonHorse)
		{
			return colour + "CrownedBishop.png";
		}
		if (_pieceType == DragonKing)
		{
			return colour + "CrownedRook.png";
		}
		if (_pieceType == Prince)
		{
			return colour + "King.png";
		}
	}
	return imageFileName;
}

std::string ShogiPiece::GetKanjiImageFileName2()
{
	std::string colour = _pieceColour == White ? "_piece_B_" : "_piece_W_";
	colour += _isPromoted ? "prom" : "norm";
	switch (_pieceType)
	{
	case King:
		return "Korol" + colour + ".png";
	case Prince:
		return "Kronprinc" + colour + ".png";
	case DragonKing:
		return "Car_Drakon" + colour + ".png";
	case DragonHorse:
		return "Loshad" + colour + ".png";
	case Rook:
		return "Ladja" + colour + ".png";
	case Bishop:
		return "Slon" + colour + ".png";
	case Lance:
		return "Strelka" + colour + ".png";
	case Elephant:
		return "Pjanyj_slon" + colour + ".png";
	case Gold:
		return "Zolotoj_general" + colour + ".png";
	case Tokin:
		return "Tokin" + colour + ".png";
	case Silver:
		return "Serebrjanyj_general" + colour + ".png";
	case Pawn:
		return "Peshka" + colour + ".png";
	case Knight:
		return "Kon" + colour + ".png";
	case PromotedLance:
		return "Perevernutaja_strelka" + colour + ".png";
	case PromotedKnight:
		return "Perevernutyj_vsadnik" + colour + ".png";
	case PromotedSilver:
		return "Perevernutyj_serebrjanyj_general" + colour + ".png";
	default:
		return "";
	}
}
