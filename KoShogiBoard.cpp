#include "KoShogiBoard.h"

KoShogiBoard::KoShogiBoard()
{
	_width = 19;
	_height = 19;
	KoShogiBoard::Initialize();
}

KoShogiBoard::~KoShogiBoard()
{
}

void KoShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new KoShogiPiece(_initialSetup[j][i], j < 8 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* KoShogiBoard::Clone()
{
	KoShogiBoard* cb = new KoShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

Piece* KoShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new KoShogiPiece(pieceType, pieceColour);
}

bool KoShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	if (IsMovePossible(newX, newY))
	{
		auto pieces = GetEnemyPiecesAround(newX, newY, _data[oldX][oldY]->GetColour());
		if (std::any_of(pieces.begin(), pieces.end(), [=](std::pair<int, int> t) {return _data[t.first][t.second]->GetType() == PoisonFlame;}))
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
		// Poison Flame moves
		if (_data[oldX][oldY]->GetType() == PoisonFlame)
		{
			for_each(pieces.begin(), pieces.end(), [&](std::pair<int, int> p) {delete _data[p.first][p.second]; _data[p.first][p.second] = nullptr;});
		}
	}
	return ChuShogiBoard::Move(oldX, oldY, newX, newY, cl);
}

void KoShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Pawn:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		break;
	case MiddleTroop:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case Drum:
	case Flag:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case CompanyCommander:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);

		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case ViceCommissioner:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		if (piece->GetColour() == White)
		{
			CheckDirection(piece, x, y, South);
		}
		else
		{
			CheckDirection(piece, x, y, North);
		}
		break;
	case AdvanceGuard:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckMove(piece, x, y - 1);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckMove(piece, x, y + 1);
		}
		break;
	case RearGuard:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, South);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, North);
			CheckMove(piece, x, y - 1);
		}
		break;
	case ShieldCaptain:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);

		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case Lion:
		GetPossibleMoves(x, y);
		break;
	case Thunderclap:
		getAll5StepPaths(x, y, piece->GetColour());
		break;
	case PoisonFlame:
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
	case DoubleKylin://TODO
		break;
	case DoublePhoenix://TODO
		break;
	case TaoistPriest:
	case SpiritualMonk:
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x - 2, y - 2);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 2);
		break;
	case ExtensiveFog://TODO
		break;
	case HolyLight://TODO
		break;
	case SkywardNet:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 1);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		else
		{
			CheckMove(piece, x, y + 1);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		break;
	case EarthwardNet:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case RisingDragon:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);

		GetPossibleMoves(x, y);
		break;
	case WingedTiger:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);

		if (IsMovePossible(x + 1, y + 1)) CheckMove(piece, x + 2, y + 2);
		if (IsMovePossible(x + 1, y + 1) || IsMovePossible(x + 1, y - 1)) CheckMove(piece, x + 2, y);
		if (IsMovePossible(x + 1, y - 1)) CheckMove(piece, x + 2, y - 2);
		if (IsMovePossible(x + 1, y + 1) || IsMovePossible(x - 1, y + 1)) CheckMove(piece, x, y + 2);

		if (IsMovePossible(x + 1, y - 1) || IsMovePossible(x - 1, y - 1)) CheckMove(piece, x, y - 2);
		if (IsMovePossible(x - 1, y + 1)) CheckMove(piece, x - 2, y + 2);
		if (IsMovePossible(x - 1, y + 1) || IsMovePossible(x - 1, y - 1)) CheckMove(piece, x - 2, y);
		if (IsMovePossible(x - 1, y - 1)) CheckMove(piece, x - 2, y - 2);

		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, West);
		break;
	case FlyingHawk:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);

		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);

		if (IsMovePossible(x + 1, y)) CheckMove(piece, x + 2, y);
		if (IsMovePossible(x, y + 1)) CheckMove(piece, x, y + 2);
		if (IsMovePossible(x, y - 1)) CheckMove(piece, x, y - 2);
		if (IsMovePossible(x - 1, y)) CheckMove(piece, x - 2, y);
		break;
	case Longbow:
	case Crossbow:
	case Cannon:
	case FrankishCannon:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case LongbowKnight:
	case CrossbowKnight:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x - 1, y + 2);
			CheckMove(piece, x + 1, y + 2);
		}
		else
		{
			CheckMove(piece, x - 1, y - 2);
			CheckMove(piece, x + 1, y - 2);
		}
		break;
	case KnightCaptain://TODO
		break;
	case WingedHorse://TODO
		break;
	case RoamingAssault:
		CheckLionDirection(piece, x, y, West, 5);
		CheckLionDirection(piece, x, y, East, 5);
		CheckLionDirection(piece, x, y, North, 5);
		CheckLionDirection(piece, x, y, South, 5);
		break;
	case CannonCarriage:
	case DivineCarriage:
	case Chariot:
		CheckDirection(piece, x, y, West, 5);
		CheckDirection(piece, x, y, East, 5);
		CheckDirection(piece, x, y, North, 5);
		CheckDirection(piece, x, y, South, 5);
		break;
	case Vanguard:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North, 5);
		}
		else
		{
			CheckDirection(piece, x, y, South, 5);
		}
		break;
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}

void KoShogiBoard::GetPossibleMoves(int x, int y)
{
	constexpr int BOARD_SIZE = 5;
	constexpr int MAX_MOVES = 2;
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
	constexpr int startR = MAX_MOVES;
	constexpr int startC = MAX_MOVES;

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
		const State st = q.front();
		q.pop();

		const int r = st.r;
		const int c = st.c;
		const int s = st.steps; // steps used so far

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

/**
 * A recursive DFS function that collects all 5-step paths.
 *
 *  - r, c: current position on the board.
 *  - step: how many moves have been taken so far (0..5).
 *  - currentPath: the partial path we have so far (list of positions).
 *  - allPaths: a container where we store complete 5-step paths.
 *
 * Once step == 5, we record the currentPath (which has 6 positions).
 */
void KoShogiBoard::dfsFiveSteps(int r, int c, int step, PieceColour pieceColour,
	std::vector<std::pair<int, int>>& currentPath, std::vector<std::vector<std::pair<int, int>>>& allPaths)
{
	constexpr int N = 19;
	const std::vector<std::pair<int, int>> directions =
	{
		{ +0, -1 },
		{ +0, +1 },
		{ -1, +0 },
		{ +1, +0 }
	};

	// If we've taken 5 steps already, store this path and return.
	if (step == 5) {
		allPaths.push_back(currentPath);
		return;
	}

	// Otherwise, try moving in each of the 4 orthogonal directions
	for (auto& dir : directions) {
		int nr = r + dir.first;
		int nc = c + dir.second;

		// Check bounds
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
			continue;
		}
		if (_data[nr][nc] != nullptr && _data[nr][nc]->GetColour() == pieceColour) {
			continue; // cannot step here
		}

		currentPath.emplace_back(nr, nc);           // add next step
		dfsFiveSteps(nr, nc, step + 1, pieceColour, currentPath, allPaths);
		currentPath.pop_back();                    // backtrack
	}
}

/**
 * Return all possible 5-step paths starting from (startR, startC).
 * Each path is a vector of length 6 (the start square plus 5 subsequent squares).
 * The player may change direction at any step and may not step onto BLACK squares.
 */
std::vector<std::vector<std::pair<int, int>>> KoShogiBoard::getAll5StepPaths(int startR, int startC, PieceColour pieceColour)
{
	std::vector<std::vector<std::pair<int, int>>> allPaths;
	// We'll keep track of the current path in a DFS.
	// Initialize it with the starting position.
	std::vector<std::pair<int, int>> currentPath;
	currentPath.emplace_back(startR, startC);

	// Depth-limited DFS for exactly 5 steps.
	dfsFiveSteps(startR, startC, /* step = */ 0, pieceColour, currentPath, allPaths);

	for (const auto & path : allPaths)
	{
		for (const auto & point : path)
		{
			_moves.emplace_back(point);
		}
	}
	return allPaths;
}