#include "KnightmateChessBoard.h"

KnightmateChessBoard::KnightmateChessBoard()
{
	_width = 8;
	_height = 8;
	KnightmateChessBoard::Initialize();
}

KnightmateChessBoard::~KnightmateChessBoard()
{
}

Board* KnightmateChessBoard::Clone()
{
	KnightmateChessBoard* cb = new KnightmateChessBoard();
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
	return cb;
}

void KnightmateChessBoard::Initialize()
{
	_moveCount = 0;
	_halfMoveCount = 0;
	_pgn = "";
	_wkc = true;
	_wqc = true;
	_bkc = true;
	_bqc = true;
	_ep = "-";
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

void KnightmateChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case King:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		// Check castling
		if (!piece->HasMoved)
		{
			if (GetData(0, y) != std::nullopt)
			{
				const std::optional<Piece> cp = GetData(0, y);
				if (!cp->HasMoved && cp->Type == Rook && GetData(1, y) == std::nullopt && GetData(2, y) == std::nullopt && GetData(3, y) == std::nullopt)
				{
					if ((piece->Colour == White && _wqc == true) || (piece->Colour == Black && _bqc == true))
					{
						_moves.emplace_back(0, y);
					}
				}
			}
			if (GetData(_width - 1, y) != std::nullopt)
			{
				const std::optional<Piece> cp = GetData(_width - 1, y);
				if (!cp->HasMoved && cp->Type == Rook && GetData(5, y) == std::nullopt && GetData(6, y) == std::nullopt)
				{
					if ((piece->Colour == White && _wkc == true) || (piece->Colour == Black && _bkc == true))
					{
						_moves.emplace_back(_width - 1, y);
					}
				}
			}
		}
		break;
	case Silver:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	default:
		ChessBoard::GetMoves(piece, x, y);
		break;
	}
}

std::string KnightmateChessBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	PieceType pieceType = GetData(x, y)->Type;
	switch (pieceType)
	{
	case Silver:
		return "M";
	default:
		return ChessBoard::GetStringCode(x, y);
	}
}
