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
	_taoistPriestCaptured = false;
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

void KoShogiBoard::RemoveShoot(int x, int y)
{
	const auto it = std::remove_if(_shoots.begin(), _shoots.end(), [=](const auto& p) { return p.first == x && p.second == y; });
	_shoots.erase(it, _shoots.end());
}

bool KoShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	// Gun carriage and Chariot of the Gods cannot capture a heavenly fortress by displacement.
	Piece* sp = _data[oldX][oldY];
	if (sp != nullptr && (sp->GetType() == CannonCarriage || sp->GetType() == DivineCarriage) && _data[newX][newY] != nullptr && _data[newX][newY]->GetType() == FreeBoar)
	{
		return false;
	}
	if (_data[oldX][oldY] != nullptr && IsMovePossible(newX, newY))
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
	const bool result = DaiShogiBoard::Move(oldX, oldY, newX, newY, cl);
	// If the Taoist priest is captured, the drum and banner can no longer promote, and if either or both have already promoted, then they immediately revert.
	if (result == true && _data[newX][newY] != nullptr && _data[newX][newY]->GetType() == TaoistPriest)
	{
		_taoistPriestCaptured = true;
		const auto raLocation = EngineOutputHandler::GetPieceLocation(this, RoamingAssault, sp->GetColour() == White ? Black : White);
		if (raLocation.first != -1 && raLocation.second != -1)
		{
			dynamic_cast<KoShogiPiece*>(_data[raLocation.first][raLocation.second])->Demote();
		}
		const auto tcLocation = EngineOutputHandler::GetPieceLocation(this, Thunderclap, sp->GetColour() == White ? Black : White);
		if (tcLocation.first != -1 && tcLocation.second != -1)
		{
			dynamic_cast<KoShogiPiece*>(_data[tcLocation.first][tcLocation.second])->Demote();
		}
	}
	// Whenever the immaculate light is within 5 intersections of the five-li fog, the fog reverts to a Taoist priest.
	if (result == true && sp != nullptr && sp->GetType() == ExtensiveFog)
	{
		const auto hlLocation = EngineOutputHandler::GetPieceLocation(this, HolyLight, sp->GetColour() == White ? Black : White);
		if (hlLocation.first != -1 && hlLocation.second != -1 && abs(hlLocation.first - newX) <= 5 && abs(hlLocation.second - newY) <= 5)
		{
			dynamic_cast<KoShogiPiece*>(sp)->Demote();
		}
	}
	else if (result == true && sp != nullptr && sp->GetType() == HolyLight)
	{
		const auto efLocation = EngineOutputHandler::GetPieceLocation(this, ExtensiveFog, sp->GetColour() == White ? Black : White);
		if (efLocation.first != -1 && efLocation.second != -1 && abs(efLocation.first - newX) <= 5 && abs(efLocation.second - newY) <= 5)
		{
			dynamic_cast<KoShogiPiece*>(_data[efLocation.first][efLocation.second])->Demote();
		}
	}
	return result;
}

void KoShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Pawn:
		// If the drum is killed, the pawns may no longer move forward.
		if (piece->GetColour() == Black)
		{
			if (EngineOutputHandler::GetPieceLocation(this, Drum, piece->GetColour()).first != -1 ||
				EngineOutputHandler::GetPieceLocation(this, Thunderclap, piece->GetColour()).first != -1)
			{
				CheckMove(piece, x, y + 1);
			}
			CheckMove(piece, x, y - 1);
		}
		else
		{
			if (EngineOutputHandler::GetPieceLocation(this, Drum, piece->GetColour()).first != -1 ||
				EngineOutputHandler::GetPieceLocation(this, Thunderclap, piece->GetColour()).first != -1)
			{
				CheckMove(piece, x, y - 1);
			}
			CheckMove(piece, x, y + 1);
		}
		CheckMove(piece, x + 1, y);
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
		getAllPiece2MoveDestinations(x, y, _lionOffsets, piece);
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
	case DoubleKylin:
		getAllPiece2MoveDestinations(x, y, _kylynOffsets, piece);
		break;
	case DoublePhoenix:
		getAllPiece2MoveDestinations(x, y, _phoenixOffsets, piece);
		break;
	case TaoistPriest:
	case SpiritualMonk:
		CheckPriestMove(piece, x + 2, y + 2);
		CheckPriestMove(piece, x - 2, y + 2);
		CheckPriestMove(piece, x + 2, y - 2);
		CheckPriestMove(piece, x - 2, y - 2);
		CheckPriestMove(piece, x + 2, y);
		CheckPriestMove(piece, x - 2, y);
		CheckPriestMove(piece, x, y + 2);
		CheckPriestMove(piece, x, y - 2);
		break;
	case ExtensiveFog:
	case HolyLight:
		getAllPiece2MoveDestinations(x, y, _priestOffsets, piece);
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

		getAllPiece2MoveDestinations(x, y, _lionOffsets, piece);
		break;
	case WingedTiger:
		getAllPiece2MoveDestinations(x, y, _tigerOffsets, piece);

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

		getAllPiece2MoveDestinations(x, y, _hawkOffsets, piece);
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
	case Knight:
	case LongbowKnight:
	case CrossbowKnight:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		break;
	case KnightCaptain:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);

		CheckMove(piece, x + 2, y + 4);
		CheckMove(piece, x + 2, y - 4);
		CheckMove(piece, x - 2, y + 4);
		CheckMove(piece, x - 2, y - 4);
		CheckMove(piece, x, y + 4);
		CheckMove(piece, x, y - 4);
		CheckMove(piece, x + 4, y);
		CheckMove(piece, x - 4, y);
		CheckMove(piece, x + 4, y + 2);
		CheckMove(piece, x - 4, y + 2);
		CheckMove(piece, x + 4, y - 2);
		CheckMove(piece, x - 4, y - 2);
		break;
	case WingedHorse:
		getAllPiece2MoveDestinations(x, y, _knightOffsets, piece);
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

std::vector<std::pair<int, int>> KoShogiBoard::GetShoots(const Piece* piece, int x, int y)
{
	_shoots.clear();
	switch (piece->GetType())
	{
	case TaoistPriest:
	case SpiritualMonk:
	case ExtensiveFog:
	case HolyLight:
		CheckShoot(piece, x + 1, y + 1);
		CheckShoot(piece, x + 1, y);
		CheckShoot(piece, x + 1, y - 1);
		CheckShoot(piece, x, y + 1);
		CheckShoot(piece, x, y - 1);
		CheckShoot(piece, x - 1, y + 1);
		CheckShoot(piece, x - 1, y);
		CheckShoot(piece, x - 1, y - 1);
		break;
	case Longbow:
	case LongbowKnight:
		CheckShootingDirection(piece, x, y, North, 3, false);
		CheckShootingDirection(piece, x, y, NorthEast, 3, false);
		CheckShootingDirection(piece, x, y, East, 3, false);
		CheckShootingDirection(piece, x, y, SouthEast, 3, false);
		CheckShootingDirection(piece, x, y, South, 3, false);
		CheckShootingDirection(piece, x, y, SouthWest, 3, false);
		CheckShootingDirection(piece, x, y, West, 3, false);
		CheckShootingDirection(piece, x, y, NorthWest, 3, false);
		break;
	case Crossbow:
	case CrossbowKnight:
		CheckShootingDirection(piece, x, y, North, 5, false);
		CheckShootingDirection(piece, x, y, NorthEast, 5, false);
		CheckShootingDirection(piece, x, y, East, 5, false);
		CheckShootingDirection(piece, x, y, SouthEast, 5, false);
		CheckShootingDirection(piece, x, y, South, 5, false);
		CheckShootingDirection(piece, x, y, SouthWest, 5, false);
		CheckShootingDirection(piece, x, y, West, 5, false);
		CheckShootingDirection(piece, x, y, NorthWest, 5, false);
		break;
	case Cannon:
	case CannonCarriage:
		CheckShootingDirection(piece, x, y, North, 5, true);
		CheckShootingDirection(piece, x, y, NorthEast, 5, true);
		CheckShootingDirection(piece, x, y, East, 5, true);
		CheckShootingDirection(piece, x, y, SouthEast, 5, true);
		CheckShootingDirection(piece, x, y, South, 5, true);
		CheckShootingDirection(piece, x, y, SouthWest, 5, true);
		CheckShootingDirection(piece, x, y, West, 5, true);
		CheckShootingDirection(piece, x, y, NorthWest, 5, true);
		break;
	case FrankishCannon:
	case DivineCarriage:
		CheckShootingDirection(piece, x, y, North, 5, false);
		CheckShootingDirection(piece, x, y, NorthEast, 5, false);
		CheckShootingDirection(piece, x, y, East, 5, false);
		CheckShootingDirection(piece, x, y, SouthEast, 5, false);
		CheckShootingDirection(piece, x, y, South, 5, false);
		CheckShootingDirection(piece, x, y, SouthWest, 5, false);
		CheckShootingDirection(piece, x, y, West, 5, false);
		CheckShootingDirection(piece, x, y, NorthWest, 5, false);
		break;
	default:
		break;
	}
	return _shoots;
}

void KoShogiBoard::CheckPriestMove(const Piece* piece, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
		if (_data[x][y] != nullptr && _data[x][y]->GetType() != TaoistPriest && _data[x][y]->GetType() != SpiritualMonk &&
			_data[x][y]->GetType() != ExtensiveFog && _data[x][y]->GetType() != HolyLight)
		{
		}
		else if (_data[x][y] == nullptr || _data[x][y]->GetColour() != piece->GetColour())
		{
			_moves.emplace_back(x, y);
		}
	}
}

void KoShogiBoard::Shoot(int x, int y)
{
	if (_data[x][y] != nullptr)
	{
		delete _data[x][y];
		_data[x][y] = nullptr;
	}
}

void KoShogiBoard::CheckShoot(const Piece* piece, int x, int y)
{
	const PieceType pt = piece->GetType();
	// Except for the Taoist priest, spiritual monk, five-li fog or immaculate light, any shooting pieces
	// are disabled from shooting if they are within five intersections of an enemy five-li fog.
	if (pt != TaoistPriest && pt != SpiritualMonk && pt != ExtensiveFog && pt != HolyLight)
	{
		const auto fogLocation = EngineOutputHandler::GetPieceLocation(this, ExtensiveFog, piece->GetColour() == White ? Black : White);
		if (fogLocation.first != -1 && fogLocation.second != -1 && (abs(fogLocation.first - x) <= 5 && abs(fogLocation.second - y) <= 5))
		{
			return;
		}
	}
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
		if (_data[x][y] != nullptr && _data[x][y]->GetColour() != piece->GetColour())
		{
			const auto dt = _data[x][y]->GetType();
			// Longbow and Crossbow cannot shoot a shield, shield unit, chariot, chariot unit, Gun carriage, Chariot of the Gods and heavenly fortress.
			if (pt == Longbow || pt == LongbowKnight || pt == Crossbow || pt == CrossbowKnight)
			{
				if (dt == CatSword || dt == ShieldCaptain || dt == Chariot || dt == Rook || dt == CannonCarriage || dt == DivineCarriage || dt == FreeBoar)
				{
					return;
				}
			}
			// Cannon, Gun carriage, Frankish cannon and Chariot of the Gods cannot shoot a shield unit and heavenly fortress.
			if (pt == Cannon || pt == CannonCarriage || pt == FrankishCannon || pt == DivineCarriage)
			{
				if (dt == ShieldCaptain || dt == FreeBoar)
				{
					return;
				}
			}
			_shoots.emplace_back(x, y);
			RemoveMove(x, y);
		}
	}
}

void KoShogiBoard::CheckShootingDirection(const Piece* piece, int x, int y, Direction direction, int count, bool shootOver)
{
	int i = 0;
	while (InBounds(x, y, direction) && i < count)
	{
		CheckDirectionInc(x, y, direction);
		if (_data[x][y] != nullptr)
		{
			CheckShoot(piece, x, y);
			if (!shootOver)
			{
				break;
			}
		}
		i++;
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
void KoShogiBoard::dfsFiveSteps(int r, int c, int step, PieceColour pieceColour, std::vector<std::pair<int, int>>& currentPath)
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
		for (const auto& point : currentPath)
		{
			_moves.emplace_back(point);
		}
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
		dfsFiveSteps(nr, nc, step + 1, pieceColour, currentPath);
		currentPath.pop_back();                    // backtrack
	}
}

/**
 * Return all possible 5-step paths starting from (startR, startC).
 * Each path is a vector of length 6 (the start square plus 5 subsequent squares).
 * The player may change direction at any step and may not step onto BLACK squares.
 */
void KoShogiBoard::getAll5StepPaths(int startR, int startC, PieceColour pieceColour)
{
	// We'll keep track of the current path in a DFS.
	// Initialize it with the starting position.
	std::vector<std::pair<int, int>> currentPath;
	currentPath.emplace_back(startR, startC);

	// Depth-limited DFS for exactly 5 steps.
	dfsFiveSteps(startR, startC, /* step = */ 0, pieceColour, currentPath);
}

/**
 * Return all squares a piece can move to in exactly 1 piece move from (r, c).
 * We skip squares with occupant=FRIENDLY (the piece's own color).
 */
std::vector<std::pair<int, int>> KoShogiBoard::getSinglePieceMoves(int r, int c, const std::vector<std::pair<int, int>>& offsets, const Piece *piece) const
{
	constexpr int N = 19;
	std::vector<std::pair<int, int>> result;
	for (auto& offset : offsets) {
		int rr = r + offset.first;
		int cc = c + offset.second;
		if (rr < 0 || rr >= N || cc < 0 || cc >= N) {
			continue;
		}

		if (piece->GetType() == ExtensiveFog || piece->GetType() == HolyLight)
		{
			if (_data[rr][cc] != nullptr && _data[rr][cc]->GetType() != TaoistPriest && _data[rr][cc]->GetType() != SpiritualMonk &&
				_data[rr][cc]->GetType() != ExtensiveFog && _data[rr][cc]->GetType() != HolyLight) {
				continue;
			}
		}

		// The piece can land on this square if it's EMPTY or ENEMY
		if (_data[rr][cc] != nullptr && _data[rr][cc]->GetColour() == piece->GetColour()) {
			continue;
		}

		result.emplace_back(rr, cc);
	}
	return result;
}

/**
 * Return all possible distinct destination squares after EXACTLY 2 piece moves
 * from the starting position (startR, startC).
 */
void KoShogiBoard::getAllPiece2MoveDestinations(int startR, int startC, const std::vector<std::pair<int, int>>& offsets, const Piece* piece)
{
	std::set<std::pair<int, int>> destinations;  // use a set to avoid duplicates

	// First-move candidates
	const auto firstMoves = getSinglePieceMoves(startR, startC, offsets, piece);
	for (auto& square2 : firstMoves) {
		destinations.insert(square2);
	}

	// For each square reachable in one piece move:
	for (const auto& square1 : firstMoves) {
		const int r1 = square1.first;
		const int c1 = square1.second;
		// Now get second-move candidates from (r1, c1)
		auto secondMoves = getSinglePieceMoves(r1, c1, offsets, piece);
		for (auto& square2 : secondMoves) {
			destinations.insert(square2);
		}
	}

	_moves.insert(_moves.end(), destinations.begin(), destinations.end());
}

bool KoShogiBoard::IsTaoistPlayerCaptured() const
{
	return _taoistPriestCaptured;
}
