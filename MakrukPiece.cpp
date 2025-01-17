#include "MakrukPiece.h"

MakrukPiece::MakrukPiece(PieceType pieceType, PieceColour pieceColour) : ShatranjPiece(pieceType, pieceColour)
{
}

MakrukPiece::~MakrukPiece()
{
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
