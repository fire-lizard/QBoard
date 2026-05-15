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

std::string ShogiPiece::ToStringCode(PieceType piece)
{
	static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
		{Rook, "R"},
		{Bishop, "B"},
		{Lance, "L"},
		{Silver, "S"},
		{Gold, "G"},
		{Knight, "N"},
        {Pawn, "P"}
	};

	const auto it = pieceTypeToCode.find(piece);
	return it != pieceTypeToCode.end() ? it->second : "";
}
