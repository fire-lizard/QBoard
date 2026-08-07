#include "SeirawanChessBoard.h"

SeirawanChessBoard::SeirawanChessBoard()
{
	_width = 8;
	_height = 8;
	SeirawanChessBoard::Initialize();
}

SeirawanChessBoard::~SeirawanChessBoard()
{
}

Board* SeirawanChessBoard::Clone()
{
	SeirawanChessBoard* cb = new SeirawanChessBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
			cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	cb->SetHalfMoveCount(_halfMoveCount);
	cb->SetCastling(GetCastling());
	cb->SetEnPassant(_ep);
	cb->SetCapturedPieces(_capturedPieces);
	return cb;
}

void SeirawanChessBoard::Initialize()
{
	ChessBoard::Initialize();
	_capturedPieces = {
		{White, Archbishop},
		{White, Chancellor},
		{Black, Archbishop},
		{Black, Chancellor}
	};
}

void SeirawanChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	if (piece->Type == Archbishop || piece->Type == Chancellor)
	{
		CapablancaChessBoard::GetMoves(piece, x, y);
	}
	else
	{
		ChessBoard::GetMoves(piece, x, y);
	}
}

std::string SeirawanChessBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	switch (GetData(x, y)->Type)
	{
	case Archbishop:
		return "H";
	case Chancellor:
		return "E";
	default:
		return CapablancaChessBoard::GetStringCode(x, y);
	}
}

int SeirawanChessBoard::BackRank(PieceColour pieceColour) const
{
	return pieceColour == White ? _height - 1 : 0;
}

bool SeirawanChessBoard::Gate(int x, int y, PieceType pieceType, PieceColour pieceColour)
{
	if (!CheckPosition(x, y) || GetData(x, y) != std::nullopt) return false;
	if (!RemoveCapturedPiece(pieceType, pieceColour)) return false;
	Piece gated(pieceType, pieceColour);
	gated.HasMoved = true;
	SetData(x, y, gated);
	return true;
}

std::string SeirawanChessBoard::GatingRights() const
{
	std::string rights = GetCastling() == "-" ? "" : GetCastling();
	for (const PieceColour colour : { White, Black })
	{
		if (std::ranges::none_of(_capturedPieces, [colour](const auto& held) { return held.first == colour; })) continue;
		const int y = BackRank(colour);
		for (int x = 1; x < _width - 1; x++)
		{
			const std::optional<Piece> p = GetData(x, y);
			if (p == std::nullopt || p->Colour != colour || p->HasMoved) continue;
			const char file = static_cast<char>('A' + x);
			rights.push_back(colour == White ? file : static_cast<char>(std::tolower(file)));
		}
	}
	return rights.empty() ? "-" : rights;
}
