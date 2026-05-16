#include "ShogiPiece.h"

ShogiPiece::ShogiPiece(PieceType pieceType, PieceColour pieceColour) : Piece(pieceType, pieceColour)
{
}

ShogiPiece::~ShogiPiece()
{
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
