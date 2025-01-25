#include "TenjikuShogiBoard.h"

TenjikuShogiBoard::TenjikuShogiBoard()
{
	_width = 16;
	_height = 16;
	TenjikuShogiBoard::Initialize();
}

TenjikuShogiBoard::~TenjikuShogiBoard()
{
}

void TenjikuShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new TenjikuShogiPiece(_initialSetup[j][i], j < 7 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* TenjikuShogiBoard::Clone()
{
	TenjikuShogiBoard* cb = new TenjikuShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

Piece* TenjikuShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new TenjikuShogiPiece(pieceType, pieceColour);
}

void TenjikuShogiBoard::CheckJump(const Piece* piece, int x, int y, Direction direction)
{
	while (CheckDirectionAux(x, y, direction))
	{
		CheckDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
		if (_data[x][y] != nullptr)
		{
			PieceType pieceType = _data[x][y]->GetType();
			if (pieceType == King)
			{
				break;
			}
			else if (piece->GetType() == pieceType || pieceType == GreatGeneral)
			{
				break;
			}
			else if (std::find(std::begin(_jumpingPieces), std::end(_jumpingPieces), pieceType) != std::end(_jumpingPieces))
			{
				break;
			}
		}
	}
}

void TenjikuShogiBoard::CheckIgui(const Piece* piece, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
		if (_data[x][y] != nullptr && _data[x][y]->GetColour() != piece->GetColour())
		{
			_moves.emplace_back(x, y);
		}
	}
}

bool TenjikuShogiBoard::Move(int oldX, int oldY, int newX, int newY)
{
	// Heavenly Tetrach moves
	if (_data[oldX][oldY]->GetType() == HeavenlyTetrarch && abs(oldX - newX) <= 1 && abs(oldY - newY) <= 1 && (oldX != newX || oldY != newY))
	{
		if (std::any_of(_moves.begin(), _moves.end(), [=](std::pair<int, int> t) {return t.first == newX && t.second == newY;}))
		{
			delete _data[newX][newY];
			_data[newX][newY] = nullptr;
			return true;
		}
	}
	else
	{
		if (IsMovePossible(newX, newY))
		{
			auto pieces = GetEnemyPiecesAround(newX, newY, _data[oldX][oldY]->GetColour());
			if (std::any_of(pieces.begin(), pieces.end(), [=](std::pair<int, int> t) {return _data[t.first][t.second]->GetType() == FireDemon;}))
			{
				delete _data[oldX][oldY];
				_data[oldX][oldY] = nullptr;
				if (_data[newX][newY] != nullptr)
				{
					delete _data[newX][newY];
					_data[newX][newY] = nullptr;
				}
				return true;
			}
			// Fire Demon moves
			else if (_data[oldX][oldY]->GetType() == FireDemon)
			{
				for_each(pieces.begin(), pieces.end(), [&](std::pair<int, int> p) {delete _data[p.first][p.second]; _data[p.first][p.second] = nullptr;});
			}
		}
	}
	return Board::Move(oldX, oldY, newX, newY);
}

void TenjikuShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case ViceGeneral:
		CheckJump(piece, x, y, SouthWest);
		CheckJump(piece, x, y, SouthEast);
		CheckJump(piece, x, y, NorthWest);
		CheckJump(piece, x, y, NorthEast);
		GetPossibleMoves(x, y);
		break;
	case FireDemon:
		CheckDirection(piece, x + 1, y + 1, SouthEast);
		CheckDirection(piece, x + 1, y - 1, NorthEast);
		CheckDirection(piece, x, y + 1, East);
		CheckDirection(piece, x, y - 1, West);
		CheckDirection(piece, x - 1, y + 1, SouthWest);
		CheckDirection(piece, x - 1, y - 1, NorthWest);
		GetPossibleMoves(x, y);
		break;
	case HeavenlyTetrarch:
		CheckIgui(piece, x + 1, y + 1);
		CheckIgui(piece, x + 1, y);
		CheckIgui(piece, x + 1, y - 1);
		CheckIgui(piece, x, y + 1);
		CheckIgui(piece, x, y - 1);
		CheckIgui(piece, x - 1, y + 1);
		CheckIgui(piece, x - 1, y);
		CheckIgui(piece, x - 1, y - 1);

		CheckDirection(piece, x + 1, y + 1, SouthEast);
		CheckDirection(piece, x + 1, y - 1, NorthEast);
		CheckDirection(piece, x, y + 1, South);
		CheckDirection(piece, x, y - 1, North);
		CheckDirection(piece, x - 1, y + 1, SouthWest);
		CheckDirection(piece, x - 1, y - 1, NorthWest);

		CheckMove(piece, x + 2, y);
		if (_data[x + 2][y] == nullptr)
		{
			CheckMove(piece, x + 3, y);
		}
		CheckMove(piece, x - 2, y);
		if (_data[x - 2][y] == nullptr)
		{
			CheckMove(piece, x - 3, y);
		}
		break;
	case GreatGeneral:
		CheckJump(piece, x, y, SouthWest);
		CheckJump(piece, x, y, SouthEast);
		CheckJump(piece, x, y, NorthWest);
		CheckJump(piece, x, y, NorthEast);
		CheckJump(piece, x, y, West);
		CheckJump(piece, x, y, East);
		CheckJump(piece, x, y, North);
		CheckJump(piece, x, y, South);
		break;
	case BishopGeneral:
		CheckJump(piece, x, y, SouthWest);
		CheckJump(piece, x, y, SouthEast);
		CheckJump(piece, x, y, NorthWest);
		CheckJump(piece, x, y, NorthEast);
		break;
	case RookGeneral:
		CheckJump(piece, x, y, West);
		CheckJump(piece, x, y, East);
		CheckJump(piece, x, y, North);
		CheckJump(piece, x, y, South);
		break;
	case MultiGeneral:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case Dog:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case SideSoldier:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y + 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 2);
		}
		else
		{
			CheckMove(piece, x, y + 2);
		}
		break;
	case VerticalSoldier:
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y + 1);
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckMove(piece, x, y - 1);
		}
		break;
	case ChariotSoldier:
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, North);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 2, y);
		break;
	case WaterBuffalo:
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y - 2);
		break;
	case LionHawk:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

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

		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		break;
	case FreeEagle:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x, y + 2);

		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 2);

		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);

		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		break;
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}

std::vector<std::pair<int, int>> TenjikuShogiBoard::GetEnemyPiecesAround(int x, int y, PieceColour pieceColour) const
{
	std::vector<std::pair<int, int>> result;
	const int directions[8][2] =
	{
		{0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Right, Down, Left, Up
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1} // NW, NE, SW, SE
	};
	for (int index = 0; index < 8; index++)
	{
		int i = x + directions[index][0];
		int j = y + directions[index][1];
		if (i < 0 || i > _width - 1 || j < 0 || j > _height - 1)
		{
			continue;
		}
		else if (_data[i][j] == nullptr)
		{
			continue;
		}
		else if (_data[i][j]->GetColour() == pieceColour)
		{
			continue;
		}
		else if (_data[i][j]->GetColour() != pieceColour)
		{
			result.emplace_back(i, j);
		}
	}
	return result;
}

void TenjikuShogiBoard::GetPossibleMoves(int x, int y)
{
	const int directions[8][2] = 
	{
		{0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Right, Down, Left, Up
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1} // NW, NE, SW, SE
	};
	int n = 7;
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -3; j <= 3; j++)
		{
			if (x + i < 0 || x + i > _width - 1 || y + j < 0 || y + j > _height - 1)
			{
				_vcMoves[i + 3][j + 3] = 1;
			}
			else if (_data[x + i][y + j] != nullptr && _data[x + i][y + j]->GetColour() != _data[x][y]->GetColour())
			{
				_vcMoves[i + 3][j + 3] = 1;
			}
			else if (_data[x + i][y + j] != nullptr && _data[x + i][y + j]->GetColour() == _data[x][y]->GetColour())
			{
				_vcMoves[i + 3][j + 3] = 2;
			}
			else
			{
				_vcMoves[i + 3][j + 3] = 0;
			}
		}
	}
	std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
	std::queue<Position> q;

	q.push({ 3, 3, 0 });
	visited[3][3] = true;

	while (!q.empty()) 
	{
		Position current = q.front();
		q.pop();

		if (current.steps > 0) 
		{
			_moves.push_back({ x + current.x - 3, y + current.y - 3 });
		}

		if (current.steps == 3) continue;

		for (const auto& dir : directions) 
		{
			int newX = current.x + dir[0];
			int newY = current.y + dir[1];

			if (newX >= 0 && newX < n && newY >= 0 && newY < n && !visited[newX][newY])
			{
				if (_vcMoves[newX][newY] == 0)
				{
					visited[newX][newY] = true;
					q.push({ newX, newY, current.steps + 1 });
				}
				else if (_vcMoves[newX][newY] == 1)
				{
					q.push({ newX, newY, current.steps + 1 });
					break;
				}
			}
		}
	}
}
