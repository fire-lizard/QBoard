#include "Board.h"

Board::~Board()
{
}

std::vector<std::pair<int, int>> Board::Moves() const
{
	return _moves;
}

Piece* Board::GetData(int x, int y) const
{
	return _data[x][y];
}

void Board::SetData(int x, int y, Piece *p)
{
	_data[x][y] = p;
}

int Board::GetWidth() const
{
	return _width;
}

int Board::GetHeight() const
{
	return _height;
}

void Board::CheckDirectionInc(int &x, int &y, Direction direction)
{
	switch (direction)
	{
	case North:
		y++;
		break;
	case South:
		y--;
		break;
	case East:
		x++;
		break;
	case West:
		x--;
		break;
	case NorthWest:
		x--; y++;
		break;
	case NorthEast:
		x++; y++;
		break;
	case SouthWest:
		x--; y--;
		break;
	case SouthEast:
		x++; y--;
		break;
	}
}

void Board::CheckMove(const Piece *piece, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
		if (_data[x][y] == nullptr || _data[x][y]->GetColour() != piece->GetColour())
		{
			_moves.emplace_back(x, y);
		}
	}
}

void Board::CheckDirection(const Piece *piece, int x, int y, Direction direction)
{
	while (CheckDirectionAux(x, y, direction))
	{
		CheckDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
		if (_data[x][y] != nullptr)
		{
			break;
		}
	}
}

bool Board::CheckDirectionAux(int x, int y, Direction direction) const
{
	switch (direction)
	{
	case North:
		return y < _height - 1;
	case South:
		return y > 0;
	case East:
		return x < _width - 1;
	case West:
		return x > 0;
	case NorthWest:
		return x > 0 && y < _height - 1;
	case NorthEast:
		return x < _width - 1 && y < _height - 1;
	case SouthWest:
		return x > 0 && y > 0;
	case SouthEast:
		return x < _width - 1 && y > 0;
	default:
		return false;
	}
}

bool Board::Move(int oldX, int oldY, int newX, int newY)
{
	for (size_t index = 0; index < _moves.size(); index++)
	{
		if (_moves[index].first == newX && _moves[index].second == newY)
		{
			if (_data[newX][newY] != nullptr)
			{
				delete _data[newX][newY];
			}
			_data[newX][newY] = _data[oldX][oldY];
			_data[oldX][oldY] = nullptr;
			return true;
		}
	}
	return false;
}

void Board::RemoveMove(int x, int y)
{
	for (size_t index = _moves.size() - 1; index >= 0; index--)
	{
		if (_moves[index].first == x && _moves[index].second == y)
			_moves.erase(_moves.begin() + index);
	}
}

std::vector<std::tuple<int, int, int, int>> Board::GetAllMoves(PieceColour pieceColour)
{
	std::vector<std::tuple<int, int, int, int>> result;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_data[i][j] != nullptr && _data[i][j]->GetColour() == pieceColour)
			{
				GetMoves(_data[i][j], i, j);
				for_each(_moves.begin(), _moves.end(), [&](std::pair<int, int> p) {result.emplace_back(i, j, p.first, p.second); });
			}
		}
	}
	return result;
}

bool Board::CheckPosition(int x, int y) const
{
	return y < _height && y >= 0 && x < _width && x >= 0;
}
