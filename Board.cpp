#include "Board.h"

#include <utility>

Board::~Board()
{
	Clear();
}

void Board::Clear()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_data[i][j] != nullptr)
			{
				delete _data[i][j];
				_data[i][j] = nullptr;
			}
		}
	}
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

int Board::MoveCount()
{
	return (_moveCount / 2) + 1;
}

template <typename T> std::basic_string<T> Board::lowercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::tolower(v)); });
	return s2;
}

std::string Board::GetFEN()
{
	std::string fen;
	int emptySquares = 0;
	for (int j = 0; j < _height; j++)
	{
		for (int i = 0; i < _width; i++)
		{
			if (_data[i][j] != nullptr)
			{
				if (emptySquares > 0)
				{
					fen.append(std::to_string(emptySquares));
					emptySquares = 0;
				}
				std::string sc = _data[i][j]->GetColour() == Black ?
					lowercase(_data[i][j]->StringCode()) : _data[i][j]->StringCode();
				fen.append(sc);
			}
			else
			{
				emptySquares++;
			}
		}
		if (emptySquares > 0)
		{
			fen.append(std::to_string(emptySquares));
		}
		if (j < _height - 1)
		{
			fen.append("/");
		}
		emptySquares = 0;
	}
	return fen;
}

void Board::SetFEN(std::string fen)
{
	_fen = std::move(fen);
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
	}
	return false;
}

bool Board::Move(int oldX, int oldY, int newX, int newY)
{
	if (std::any_of(_moves.begin(), _moves.end(), [=](std::pair<int, int> t) {return t.first == newX && t.second == newY; }))
	{
		if (_data[newX][newY] != nullptr)
		{
			delete _data[newX][newY];
		}
		_data[newX][newY] = _data[oldX][oldY];
		_data[oldX][oldY] = nullptr;
		return true;
	}
	return false;
}

void Board::RemoveMove(int x, int y)
{
	const long long cnt = static_cast<long long>(_moves.size()) - 1;
	for (long long index = cnt; index >= 0; index--)
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
				for_each(_moves.begin(), _moves.end(), [&](std::pair<int, int> p) {result.emplace_back(i, j, p.first, p.second);});
			}
		}
	}
	return result;
}

bool Board::CheckPosition(int x, int y) const
{
	return y < _height && y >= 0 && x < _width && x >= 0;
}

void Board::GetAttackers(int x, int y, std::vector<std::pair<int, int>>& vec)
{
	vec.clear();
	if (_data[x][y] == nullptr)
	{
		return;
	}
	PieceColour pieceColour = _data[x][y]->GetColour();
	Board* board = this->Clone();
	board->SetData(x, y, nullptr);
	auto opponentMoves = board->GetAllMoves(pieceColour == White ? Black : White);
	for (size_t index = 0; index < opponentMoves.size(); index++)
	{
		auto tpl = opponentMoves[index];
		if (std::get<2>(tpl) == x && std::get<3>(tpl) == y)
		{
			vec.emplace_back(std::get<0>(tpl), std::get<1>(tpl));
		}
	}
	delete board;
}

void Board::GetDefenders(int x, int y, std::vector<std::pair<int, int>>& vec)
{
	vec.clear();
	if (_data[x][y] == nullptr)
	{
		return;
	}
	PieceColour pieceColour = _data[x][y]->GetColour();
	Board* board = this->Clone();
	board->SetData(x, y, nullptr);
	auto playerMoves = board->GetAllMoves(pieceColour);
	for (size_t index = 0; index < playerMoves.size(); index++)
	{
		auto tpl = playerMoves[index];
		if (std::get<2>(tpl) == x && std::get<3>(tpl) == y)
		{
			vec.emplace_back(std::get<0>(tpl), std::get<1>(tpl));
		}
	}
	delete board;
}

bool Board::operator == (const PieceType other[16][16]) const
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_data[j][i] != nullptr && _data[j][i]->GetType() != other[i][j])
			{
				return false;
			}
		}
	}
	return true;
}