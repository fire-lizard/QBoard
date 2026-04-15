#include "MakrukPiece.h"

MakrukPiece::MakrukPiece(PieceType pieceType, PieceColour pieceColour) : ShatranjPiece(pieceType, pieceColour)
{
}

MakrukPiece::~MakrukPiece()
{
}

std::string MakrukPiece::GetImageFileName() const
{
    const std::string colour = _pieceColour == White ? "White" : "Black";
    if (_pieceType == Queen && _isPromoted)
    {
        return colour + "PawnP.png";
    }
    else
    {
        return ShatranjPiece::GetImageFileName();
    }
}

std::string MakrukPiece::StringCode()
{
	switch (_pieceType)
	{
	case Queen:
		return "M";
	case Silver:
		return "S";
	default:
		return ShatranjPiece::StringCode();
	}
}

PieceType MakrukPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
		{"K", King},
		{"M", Queen},
		{"S", Silver},
		{"R", Rook},
		{"N", Knight},
		{"P", Pawn}
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : None;
}
