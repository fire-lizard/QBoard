#include "ChuShogiBoard.h"

ChuShogiBoard::ChuShogiBoard()
{
	_width = 12;
	_height = 12;
	ChuShogiBoard::Initialize();
}

ChuShogiBoard::~ChuShogiBoard()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_data[i][j] != nullptr)
			{
				delete _data[i][j];
			}
		}
	}
}

void ChuShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new ChuShogiPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* ChuShogiBoard::Clone()
{
	ChuShogiBoard *cb = new ChuShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece *p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

Piece* ChuShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new ChuShogiPiece(pieceType, pieceColour);
}

void ChuShogiBoard::GetMoves(Piece *piece, int x, int y)
{
	bool ned;
	bool ed;
	bool sed;
	bool sd;
	bool nd;
	bool nwd;
	bool wd;
	bool swd;
	_moves.clear();
	switch (piece->GetType())
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
		break;
	case Lion:
		ned = CheckLionMove(piece, x + 1, y + 1);
		ed = CheckLionMove(piece, x + 1, y);
		sed = CheckLionMove(piece, x + 1, y - 1);
		nd = CheckLionMove(piece, x, y + 1);
		sd = CheckLionMove(piece, x, y - 1);
		nwd = CheckLionMove(piece, x - 1, y + 1);
		wd = CheckLionMove(piece, x - 1, y);
		swd = CheckLionMove(piece, x - 1, y - 1);

		if (ned)
			CheckMove(piece, x + 2, y + 2);
		if (ned || ed)
			CheckMove(piece, x + 2, y + 1);
		if (ned || ed || sed)
			CheckMove(piece, x + 2, y);
		if (ed || sed)
			CheckMove(piece, x + 2, y - 1);
		if (sed)
			CheckMove(piece, x + 2, y - 2);
		if (nd || ned)
			CheckMove(piece, x + 1, y + 2);
		if (nwd || nd || ned)
			CheckMove(piece, x, y + 2);
		if (nwd || nd)
			CheckMove(piece, x - 1, y + 2);

		if (swd || sd)
			CheckMove(piece, x - 1, y - 2);
		if (swd || sd || sed)
			CheckMove(piece, x, y - 2);
		if (sd || sed)
			CheckMove(piece, x + 1, y - 2);
		if (nwd)
			CheckMove(piece, x - 2, y + 2);
		if (wd || nwd)
			CheckMove(piece, x - 2, y + 1);
		if (swd || wd || nwd)
			CheckMove(piece, x - 2, y);
		if (swd || wd)
			CheckMove(piece, x - 2, y - 1);
		if (swd)
			CheckMove(piece, x - 2, y - 2);
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
	case DragonKing:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case DragonHorse:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Rook:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case Bishop:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case VerticalMover:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case SideMover:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		break;
	case Cannon:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case Lance:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case Kylin:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y);
		break;
	case Phoenix:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);

		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y - 2);
		break;
	case Elephant:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case BlindTiger:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
		}
		break;
	case Gold:
	case Tokin:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case Silver:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case Copper:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case FerociousLeopard:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case Cobra:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		break;
	case Pawn:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case Eagle:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, West);
		if (piece->GetColour() == Black)
		{
			if (CheckLionMove(piece, x + 1, y + 1))
				CheckMove(piece, x + 2, y + 2);
			if (CheckLionMove(piece, x - 1, y + 1))
				CheckMove(piece, x - 2, y + 2);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			if (CheckLionMove(piece, x + 1, y - 1))
				CheckMove(piece, x + 2, y - 2);
			if (CheckLionMove(piece, x - 1, y - 1))
				CheckMove(piece, x - 2, y - 2);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case Unicorn:
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		if (piece->GetColour() == Black)
		{
			if (CheckLionMove(piece, x, y + 1))
				CheckMove(piece, x, y + 2);
			CheckDirection(piece, x, y, South);
		}
		else
		{
			if (CheckLionMove(piece, x, y - 1))
				CheckMove(piece, x, y - 2);
			CheckDirection(piece, x, y, North);
		}
		break;
	case NarrowQueen:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case SleepingQueen:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case FlyingStag:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case WhiteHorse:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, NorthWest);
		}
		else
		{
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		break;
	case Whale:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, NorthWest);
		}
		break;
	default:
		break;
	}
}

bool ChuShogiBoard::CheckLionMove(const Piece* piece, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
		if (_data[x][y] == nullptr || _data[x][y]->GetColour() != piece->GetColour())
		{
			_moves.emplace_back(x, y);
			return true;
		}
	}
	return false;
}

void ChuShogiBoard::GetLionJumps(const Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Lion:
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x - 1, y + 2);

		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x - 2, y - 2);
		break;
	case Eagle:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
		}
		else
		{
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
		}
		break;
	case Unicorn:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 2);
		}
		else
		{
			CheckMove(piece, x, y - 2);
		}
		break;
	default:
		break;
	}
}

void ChuShogiBoard::GetLionMoves(const Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Lion:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case Eagle:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
		}
		else
		{
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
		}
		break;
	case Unicorn:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	default:
		break;
	}
}