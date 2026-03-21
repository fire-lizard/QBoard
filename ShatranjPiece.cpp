#include "ShatranjPiece.h"

ShatranjPiece::ShatranjPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

ShatranjPiece::~ShatranjPiece()
{
}

void ShatranjPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	_pieceType = Queen;
}

std::string ShatranjPiece::StringCode()
{
	switch (_pieceType)
	{
	case King:
		return "K";
	case Queen:
		return "Q";
	case Rook:
		return "R";
	case Bishop:
		return "B";
	case Knight:
		return "N";
    case Archbishop:
        return "A";
    case Chancellor:
        return "C";
    case Pawn:
		return "P";
	default:
		return "";
	}
}

PieceType ShatranjPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"K", King},
		{"Q", Queen},
		{"R", Rook},
		{"B", Bishop},
		{"N", Knight},
        {"A", Archbishop},
        {"C", Chancellor},
        {"P", Pawn}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}
