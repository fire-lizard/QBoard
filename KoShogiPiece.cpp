#include "KoShogiPiece.h"

KoShogiPiece::KoShogiPiece(PieceType pieceType, PieceColour pieceColour) : DaiShogiPiece(pieceType, pieceColour)
{
}

KoShogiPiece::~KoShogiPiece()
{
}

void KoShogiPiece::Promote(PieceType pieceType)
{
	_isPromoted = true;
	switch (_pieceType)
	{
	default:
		DaiShogiPiece::Promote(pieceType);
		break;
	}
}

std::string KoShogiPiece::StringCode()
{
	switch (_pieceType)
	{
	default:
		return DaiShogiPiece::StringCode();
	}
}

PieceType KoShogiPiece::FromStringCode(const std::string& code)
{
	static const std::unordered_map<std::string, PieceType> codeToPieceType = {
	};

	const auto it = codeToPieceType.find(code);
	return it != codeToPieceType.end() ? it->second : DaiShogiPiece::FromStringCode(code);
}

std::string KoShogiPiece::KanjiStringCode()
{
	switch (_pieceType)
	{
	default:
		return DaiShogiPiece::KanjiStringCode();
	}
}

std::string KoShogiPiece::GetKanjiImageFileName()
{
	std::string colour = _pieceColour == White ? "" : "Flip";
	if (_isPromoted && _pieceType != King)
	{
		colour = "P" + colour;
	}
	switch (_pieceType)
	{
	default:
		return DaiShogiPiece::GetKanjiImageFileName();
	}
}

std::string KoShogiPiece::PieceType2Description(PieceType pieceType)
{
	switch (pieceType)
	{
	default: return "";
	}
}

PieceType KoShogiPiece::Description2PieceType(const std::string& description)
{
	return None;
}
