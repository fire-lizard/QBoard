#include "ChuShogiBoard.h"

ChuShogiBoard::ChuShogiBoard()
{
	_width = 12;
	_height = 12;
	ChuShogiBoard::Initialize();
}

ChuShogiBoard::~ChuShogiBoard()
{
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

bool ChuShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	// Lion capture rule #2
	if (_wasLionCapturedByNonLion)
	{
		if (_data[oldX][oldY]->GetType() != Lion && _data[newX][newY] != nullptr && _data[newX][newY]->GetType() == Lion)
		{
			return false;
		}
	}
	_wasLionCapturedByNonLion = _data[oldX][oldY]->GetType() != Lion && _data[newX][newY] != nullptr && _data[newX][newY]->GetType() == Lion;
	return Board::Move(oldX, oldY, newX, newY, cl);
}

void ChuShogiBoard::CheckNullMove(const Piece* piece, int x, int y)
{
	if (IsMovePossible(x + 1, y + 1) || IsMovePossible(x + 1, y) || IsMovePossible(x + 1, y - 1) || IsMovePossible(x, y + 1) ||
		IsMovePossible(x, y - 1) || IsMovePossible(x - 1, y + 1) || IsMovePossible(x - 1, y) || IsMovePossible(x - 1, y - 1))
	{
		_moves.emplace_back(x, y);
	}
}

void ChuShogiBoard::GetMoves(Piece *piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case King:
	case Prince:
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
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

		CheckNullMove(piece, x, y);

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
	case Tiger:
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
	case Leopard:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case GoBetween:
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
		_moves.push_back({ x, y });

		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, West);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case Unicorn:
		_moves.push_back({ x, y });

		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x, y + 2);
			CheckDirection(piece, x, y, South);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x, y - 2);
			CheckDirection(piece, x, y, North);
		}
		break;
	case FlyingOx:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case FreeBoar:
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

bool ChuShogiBoard::IsMovePossible(int x, int y)
{
	return std::any_of(_moves.begin(), _moves.end(), [=](std::pair<int, int> t) {return t.first == x && t.second == y; });
}

bool ChuShogiBoard::LionMove(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if ((x1 == x3 && y1 == y3) || std::any_of(_moves.begin(), _moves.end(), [=](std::pair<int, int> t) {return t.first == x3 && t.second == y3; }))
	{
		// Lion capture rule #1
		if ((abs(x1 - x3) == 2 || abs(y1 - y3) == 2) &&
			_data[x3][y3] != nullptr && _data[x3][y3]->GetType() == Lion)
		{
			std::vector<std::pair<int, int>> lionDefenders;
			GetDefenders(x3, y3, lionDefenders);
			if (!lionDefenders.empty())
			{
				if (_data[x2][y2] == nullptr || (_data[x2][y2]->GetType() != Pawn && _data[x2][y2]->GetType() != GoBetween))
				{
					return false;
				}
			}
		}
		if (_data[x2][y2] != nullptr)
		{
			delete _data[x2][y2];
			_data[x2][y2] = nullptr;
		}
		if (x1 != x3 || y1 != y3)
		{
			if (_data[x3][y3] != nullptr)
			{
				delete _data[x3][y3];
			}
			_data[x3][y3] = _data[x1][y1];
			_data[x1][y1] = nullptr;
		}
		return true;
	}
	return false;
}