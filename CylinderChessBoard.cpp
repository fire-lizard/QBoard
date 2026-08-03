#include "CylinderChessBoard.h"

CylinderChessBoard::CylinderChessBoard()
{
	_width = 8;
	_height = 8;
	CylinderChessBoard::Initialize();
}

CylinderChessBoard::~CylinderChessBoard()
{
}

Board* CylinderChessBoard::Clone()
{
	CylinderChessBoard* cb = new CylinderChessBoard();
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

void CylinderChessBoard::Initialize()
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

void CylinderChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case King:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
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
	case Queen:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Bishop:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Knight:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		break;
	case Rook:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case Pawn:
		if (piece->Colour == Black)
		{
			if (y == 1 && GetData(x, y + 1) == std::nullopt && GetData(x, y + 2) == std::nullopt)
			{
				CheckMove(piece, x, y + 2);
			}
			if (y + 1 < _height && GetData(x, y + 1) == std::nullopt)
			{
				CheckMove(piece, x, y + 1);
			}
			if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != std::nullopt)
			{
				CheckMove(piece, x + 1, y + 1);
			}
			if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != std::nullopt)
			{
				CheckMove(piece, x - 1, y + 1);
			}
			// En passant
			if (_ep != "-")
			{
				GetEnPassantMoves(piece.value(), x, y);
			}
		}
		else
		{
			if (y == _height - 2 && GetData(x, y - 1) == std::nullopt && GetData(x, y - 2) == std::nullopt)
			{
				CheckMove(piece, x, y - 2);
			}
			if (y - 1 >= 0 && GetData(x, y - 1) == std::nullopt)
			{
				CheckMove(piece, x, y - 1);
			}
			if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != std::nullopt)
			{
				CheckMove(piece, x + 1, y - 1);
			}
			if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != std::nullopt)
			{
				CheckMove(piece, x - 1, y - 1);
			}
			// En passant
			if (_ep != "-")
			{
				GetEnPassantMoves(piece.value(), x, y);
			}
		}
		break;
	default:
		ChessBoard::GetMoves(piece, x, y);
		break;
	}
}
