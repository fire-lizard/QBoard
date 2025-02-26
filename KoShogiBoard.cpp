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
		break;
	case Thunderclap:
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
	case DoubleKylin:
		break;
	case DoublePhoenix:
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
	case ExtensiveFog:
		break;
	case HolyLight:
		break;
	case SkywardNet:
		break;
	case EarthwardNet:
		break;
	case RisingDragon:
		break;
	case Quartermaster:
		break;
	case WingedTiger:
		break;
	case FlyingHawk:
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
	case KnightCaptain:
		break;
	case WingedHorse:
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

void KoShogiBoard::CheckLionDirection(const Piece* piece, int x, int y, Direction direction, int count)
{
	int i = 0;
	while (InBounds(x, y, direction) && i < count)
	{
		CheckDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
		if (_data[x][y] != nullptr && _data[x][y]->GetColour() == piece->GetColour())
		{
			break;
		}
		i++;
	}
}

/**
 * A recursive DFS function that collects all 5-step paths.
 *
 *  - board: a 19x19 grid
 *  - r, c: current position on the board.
 *  - step: how many moves have been taken so far (0..5).
 *  - currentPath: the partial path we have so far (list of positions).
 *  - allPaths: a container where we store complete 5-step paths.
 *
 * Once step == 5, we record the currentPath (which has 6 positions).
 */
void dfsFiveSteps(const Board* board, int r, int c, int step, PieceColour pieceColour,
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
		if (board->GetData(nr, nc) != nullptr && board->GetData(nr, nc)->GetColour() == pieceColour) {
			continue; // cannot step here
		}

		currentPath.emplace_back(nr, nc);           // add next step
		dfsFiveSteps(board, nr, nc, step + 1, pieceColour, currentPath, allPaths);
		currentPath.pop_back();                    // backtrack
	}
}

/**
 * Return all possible 5-step paths starting from (startR, startC).
 * Each path is a vector of length 6 (the start square plus 5 subsequent squares).
 * The player may change direction at any step and may not step onto BLACK squares.
 */
std::vector<std::vector<std::pair<int, int>>> getAll5StepPaths(const Board* board, int startR, int startC, PieceColour pieceColour)
{
	std::vector<std::vector<std::pair<int, int>>> allPaths;
	// We'll keep track of the current path in a DFS.
	// Initialize it with the starting position.
	std::vector<std::pair<int, int>> currentPath;
	currentPath.emplace_back(startR, startC);

	// Depth-limited DFS for exactly 5 steps.
	dfsFiveSteps(board, startR, startC, /* step = */ 0, pieceColour, currentPath, allPaths);

	return allPaths;
}