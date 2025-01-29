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
	bool beforeJump = true;
	while (CheckDirectionAux(x, y, direction))
	{
		CheckDirectionInc(x, y, direction);
		if (beforeJump)
		{
			CheckMove(piece, x, y);
		}
		if (_data[x][y] != nullptr)
		{
			beforeJump = false;
			CheckMove(piece, x, y);
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

bool TenjikuShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
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
	return Board::Move(oldX, oldY, newX, newY, cl);
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

		CheckNullMove(x, y);
		break;
	case FireDemon:
		CheckDirection(piece, x + 1, y + 1, SouthEast);
		CheckDirection(piece, x + 1, y - 1, NorthEast);
		CheckDirection(piece, x, y + 1, East);
		CheckDirection(piece, x, y - 1, West);
		CheckDirection(piece, x - 1, y + 1, SouthWest);
		CheckDirection(piece, x - 1, y - 1, NorthWest);

		GetPossibleMoves(x, y);

		CheckNullMove(x, y);
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

		CheckNullMove(x, y);

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
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
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

		CheckNullMove(x, y);

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
	const int BOARD_SIZE = 7;
	const int MAX_MOVES = 3;
	char board[BOARD_SIZE][BOARD_SIZE];
	for (int i = -MAX_MOVES; i <= MAX_MOVES; i++)
	{
		for (int j = -MAX_MOVES; j <= MAX_MOVES; j++)
		{
			if (x + i < 0 || x + i > _width - 1 || y + j < 0 || y + j > _height - 1)
			{
				board[i + MAX_MOVES][j + MAX_MOVES] = 'W';
			}
			else if (_data[x + i][y + j] != nullptr && _data[x + i][y + j]->GetColour() != _data[x][y]->GetColour())
			{
				board[i + MAX_MOVES][j + MAX_MOVES] = 'W';
			}
			else if (_data[x + i][y + j] != nullptr && _data[x + i][y + j]->GetColour() == _data[x][y]->GetColour())
			{
				board[i + MAX_MOVES][j + MAX_MOVES] = 'B';
			}
			else
			{
				board[i + MAX_MOVES][j + MAX_MOVES] = '.';
			}
		}
	}

	// Initial position.
	const int startR = MAX_MOVES;
	const int startC = MAX_MOVES;

	// Directions: 8 neighbors (vertical, horizontal, diagonal).
	static const std::vector<std::pair<int, int>> directions =
	{
		{-1,  0}, {1,  0},  // up, down
		{0, -1},  {0,  1},  // left, right
		{-1, -1}, {-1,  1}, // diag up-left, up-right
		{ 1, -1}, { 1,  1}  // diag down-left, down-right
	};

	// We will do a BFS.
	// visited[r][c][stepsUsed] = true if that state has been visited.
	bool visited[BOARD_SIZE][BOARD_SIZE][4];
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			for (int s = 0; s < 4; s++)
			{
				visited[r][c][s] = false;
			}
		}
	}

	// A queue for BFS states (r, c, stepsUsed so far).
	std::queue<State> q;
	// Start from the initial position with 0 steps used.
	q.push({ startR, startC, 0 });
	visited[startR][startC][0] = true;

	// We'll keep track of all reachable squares in a set to avoid duplicates.
	std::set<std::pair<int, int>> reachablePositions;
	reachablePositions.insert({ startR, startC });

	while (!q.empty())
	{
		State st = q.front();
		q.pop();

		int r = st.r;
		int c = st.c;
		int s = st.steps; // steps used so far

		// If we've already used all steps, we can't move further.
		if (s == MAX_MOVES)
		{
			continue;
		}

		// Try all 8 directions for the next step.
		for (auto& dir : directions)
		{
			int rr = r + dir.first;
			int cc = c + dir.second;

			// Check boundaries
			if (rr < 0 || rr >= BOARD_SIZE || cc < 0 || cc >= BOARD_SIZE)
			{
				continue;
			}

			// Check if black flag => cannot pass at all.
			if (board[rr][cc] == 'B')
			{
				continue;
			}

			// We can move onto white or empty squares if not visited with steps+1
			if (!visited[rr][cc][s + 1])
			{
				visited[rr][cc][s + 1] = true;
				reachablePositions.insert({ rr, cc });

				// If it's a white flag, we can land but not continue from there.
				if (board[rr][cc] == 'W')
				{
					// Do not add it back to queue for further steps.
					// Because we cannot pass through a white flag.
				}
				else
				{
					// It's empty: we can continue from there if we haven't used up all the steps.
					q.push({ rr, cc, s + 1 });
				}
			}
		}
	}

	for (const auto& reachablePosition : reachablePositions)
	{
		_moves.emplace_back(x + reachablePosition.first - MAX_MOVES, y + reachablePosition.second - MAX_MOVES);
	}
}
