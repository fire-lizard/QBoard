#include "SittuyinBoard.h"

SittuyinBoard::SittuyinBoard()
{
	_width = 8;
	_height = 8;
	SittuyinBoard::Initialize();
}

SittuyinBoard::~SittuyinBoard()
{
}

Board* SittuyinBoard::Clone()
{
	SittuyinBoard* cb = new SittuyinBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
			cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

void SittuyinBoard::Initialize()
{
	_moveCount = 0;
	_pgn = "";
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				SetData(i, j, Piece(_initialSetup[j][i], j < 4 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
	_capturedPieces = {
		{White, Rook},
		{White, Rook},
		{Black, Rook},
		{Black, Rook},
		{White, Knight},
		{White, Knight},
		{Black, Knight},
		{Black, Knight},
		{White, Bishop},
		{White, Bishop},
		{Black, Bishop},
		{Black, Bishop},
		{White, Queen},
		{Black, Queen},
		{White, King},
		{Black, King}
	};
}

void SittuyinBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case Bishop:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	default:
		ShatranjBoard::GetMoves(piece, x, y);
		break;
	}
}

std::string SittuyinBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	PieceType pieceType = GetData(x, y)->Type;
	switch (pieceType)
	{
	case Queen:
		return "F";
	case Bishop:
		return "S";
	default:
		return ShatranjBoard::GetStringCode(x, y);
	}
}

void SittuyinBoard::ClearPiecesInHand()
{
	_capturedPieces.clear();
}
