#include "MusketeerChessBoard.h"

MusketeerChessBoard::MusketeerChessBoard()
{
	_width = 8;
	_height = 10;
	MusketeerChessBoard::Initialize();
}

MusketeerChessBoard::~MusketeerChessBoard()
{
}

Board* MusketeerChessBoard::Clone()
{
	MusketeerChessBoard* cb = new MusketeerChessBoard();
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

void MusketeerChessBoard::Initialize()
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

void MusketeerChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case Leopard:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckDirection(piece, x, y, NorthEast, 2);
		CheckDirection(piece, x, y, SouthEast, 2);
		CheckDirection(piece, x, y, SouthWest, 2);
		CheckDirection(piece, x, y, NorthWest, 2);
		break;
	case Cannon:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		break;
	case Unicorn:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);

		CheckMove(piece, x + 1, y + 3);
		CheckMove(piece, x - 1, y + 3);
		CheckMove(piece, x + 3, y + 1);
		CheckMove(piece, x + 3, y - 1);
		CheckMove(piece, x - 3, y + 1);
		CheckMove(piece, x - 3, y - 1);
		CheckMove(piece, x + 1, y - 3);
		CheckMove(piece, x - 1, y - 3);
		break;
	case FlyingDragon:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Elephant:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 2);
		break;
	case Eagle:
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 2);

		CheckMove(piece, x + 3, y + 3);
		CheckMove(piece, x + 3, y);
		CheckMove(piece, x + 3, y - 3);
		CheckMove(piece, x, y + 3);
		CheckMove(piece, x, y - 3);
		CheckMove(piece, x - 3, y + 3);
		CheckMove(piece, x - 3, y);
		CheckMove(piece, x - 3, y - 3);
		break;
	case Fortress:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y);
		CheckDirection(piece, x, y, NorthEast, 3);
		CheckDirection(piece, x, y, SouthEast, 3);
		CheckDirection(piece, x, y, SouthWest, 3);
		CheckDirection(piece, x, y, NorthWest, 3);
		break;
	case Spider:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckDirection(piece, x, y, NorthEast, 2);
		CheckDirection(piece, x, y, SouthEast, 2);
		CheckDirection(piece, x, y, SouthWest, 2);
		CheckDirection(piece, x, y, NorthWest, 2);
		break;
	case Pawn:
		CapablancaChessBoard::GetMoves(piece, x, y);
		if (piece->Colour == Black)
		{
			if (y == 2 && GetData(x, y + 1) == std::nullopt && GetData(x, y + 2) == std::nullopt)
			{
				CheckMove(piece, x, y + 2);
			}
		}
		else
		{
			if (y == _height - 3 && GetData(x, y - 1) == std::nullopt && GetData(x, y - 2) == std::nullopt)
			{
				CheckMove(piece, x, y - 2);
			}
		}
		break;
	default:
		CapablancaChessBoard::GetMoves(piece, x, y);
		break;
	}
	auto moves_to_remove =
		std::ranges::remove_if(_moves, [](const auto& m) { return m.second == 0 || m.second == 9; });
	_moves.erase(moves_to_remove.begin(), moves_to_remove.end());
}

std::string MusketeerChessBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	PieceType pieceType = GetData(x, y)->Type;
	switch (pieceType)
	{
	case Leopard:
		return "L";
	case Cannon:
		return "C";
	case Unicorn:
		return "U";
	case FlyingDragon:
		return "D";
	case Chancellor:
		return "M";
	case Archbishop:
		return "A";
	case Elephant:
		return "E";
	case Eagle:
		return "H";
	case Fortress:
		return "F";
	case Spider:
		return "S";
	default:
		return CapablancaChessBoard::GetStringCode(x, y);
	}
}
