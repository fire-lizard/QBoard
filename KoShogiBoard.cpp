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
                SetData(i, j, Piece(_initialSetup[j][i], j < 8 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
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
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

void KoShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (GetData(x, y) != std::nullopt)
    {
		_data[x][y]->IsPromoted = true;
        PieceType pieceType = None;
        switch (_data[x][y]->Type)
        {
        case Kylin:
            pieceType = DoubleKylin;
            break;
        case Phoenix:
            pieceType = DoublePhoenix;
            break;
        case Elephant:
            pieceType = DragonKing;
            break;
        case Gold:
            pieceType = FlyingStag;
            break;
        case Silver:
            pieceType = CompanyCommander;
            break;
        case Leopard:
            pieceType = ViceCommissioner;
            break;
        case Copper:
            pieceType = PoisonFlame;
            break;
        case TaoistPriest:
            pieceType = ExtensiveFog;
            break;
        case SpiritualMonk:
            pieceType = HolyLight;
            break;
        case AdvanceGuard:
            pieceType = SkywardNet;
            break;
        case MiddleTroop:
            pieceType = Prince;
            break;
        case Drum:
            pieceType = Thunderclap;
            break;
        case Flag:
            pieceType = RoamingAssault;
            break;
        case Tiger:
            pieceType = DragonHorse;
            break;
        case Queen:
            pieceType = RisingDragon;
            break;
        case DragonKing:
            pieceType = WingedTiger;
            break;
        case DragonHorse:
            pieceType = FlyingHawk;
            break;
        case RearGuard:
            pieceType = EarthwardNet;
            break;
        case FrankishCannon:
            pieceType = DivineCarriage;
            break;
        case Longbow:
            pieceType = LongbowKnight;
            break;
        case Crossbow:
            pieceType = CrossbowKnight;
            break;
        case Cannon:
            pieceType = CannonCarriage;
            break;
        case Knight:
            pieceType = KnightCaptain;
            break;
        case KnightCaptain:
            pieceType = WingedHorse;
            break;
        case Pawn:
            pieceType = VerticalMover;
            break;
        case CatSword:
            pieceType = ShieldCaptain;
            break;
        case ShieldCaptain:
            pieceType = FreeBoar;
            break;
        case Chariot:
            pieceType = Rook;
            break;
        case Rook:
            pieceType = Queen;
            break;
        case VerticalMover:
        case Vanguard:
            pieceType = FlyingOx;
            break;
        default:
            break;
        }
        if (pieceType != None)
        {
			_data[x][y]->Type = pieceType;
        }
    }
}

void KoShogiBoard::Demote(int x, int y)
{
	if (GetData(x, y) != std::nullopt)
	{
		_data[x][y]->IsPromoted = false;
		PieceType pieceType = None;
		switch (_data[x][y]->Type)
		{
		case DoubleKylin:
			pieceType = Kylin;
			break;
		case DoublePhoenix:
			pieceType = Phoenix;
			break;
		case DragonKing:
			pieceType = Elephant;
			break;
		case FlyingStag:
			pieceType = Gold;
			break;
		case CompanyCommander:
			pieceType = Silver;
			break;
		case ViceCommissioner:
			pieceType = Leopard;
			break;
		case PoisonFlame:
			pieceType = Copper;
			break;
		case ExtensiveFog:
			pieceType = TaoistPriest;
			break;
		case HolyLight:
			pieceType = SpiritualMonk;
			break;
		case SkywardNet:
			pieceType = AdvanceGuard;
			break;
		case Prince:
			pieceType = MiddleTroop;
			break;
		case Thunderclap:
			pieceType = Drum;
			break;
		case RoamingAssault:
			pieceType = Flag;
			break;
		case DragonHorse:
			pieceType = Tiger;
			break;
		case RisingDragon:
			pieceType = Queen;
			break;
		case WingedTiger:
			pieceType = DragonKing;
			break;
		case FlyingHawk:
			pieceType = DragonHorse;
			break;
		case EarthwardNet:
			pieceType = RearGuard;
			break;
		case DivineCarriage:
			pieceType = FrankishCannon;
			break;
		case LongbowKnight:
			pieceType = Longbow;
			break;
		case CrossbowKnight:
			pieceType = Crossbow;
			break;
		case CannonCarriage:
			pieceType = Cannon;
			break;
		case KnightCaptain:
			pieceType = Knight;
			break;
		case WingedHorse:
			pieceType = KnightCaptain;
			break;
		case VerticalMover:
			pieceType = Pawn;
			break;
		case ShieldCaptain:
			pieceType = CatSword;
			break;
		case FreeBoar:
			pieceType = ShieldCaptain;
			break;
		case Rook:
			pieceType = Chariot;
			break;
		case Queen:
			pieceType = Rook;
			break;
		case FlyingOx:
			pieceType = _data[x][y]->BaseType;
			break;
		default:
			break;
		}
		if (pieceType != None)
		{
			_data[x][y]->Type = pieceType;
		}
	}
}

void KoShogiBoard::Immobilize(int x, int y, Direction direction)
{
	auto sp = GetData(x, y);
	if (sp == std::nullopt) return;
	while (InBounds(x, y, direction))
	{
		CheckDirectionInc(x, y, direction);
		if (GetData(x, y) != std::nullopt)
		{
			if (sp->Colour == GetData(x, y)->Colour) break;
			_data[x][y]->CanMove = false;
			break;
		}
	}
}

void KoShogiBoard::RemoveShoot(int x, int y)
{
	const auto it = std::ranges::remove_if(_shoots, [=](const auto& p) { return p.first == x && p.second == y; }).begin();
	_shoots.erase(it, _shoots.end());
}

bool KoShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	// Gun carriage and Chariot of the Gods cannot capture a heavenly fortress by displacement.
	std::optional<Piece> sp = GetData(oldX, oldY);
    if (sp != std::nullopt && (sp->Type == CannonCarriage || sp->Type == DivineCarriage) && GetData(newX, newY) != std::nullopt && GetData(newX, newY)->Type == FreeBoar)
	{
		return false;
	}
	if (GetData(oldX, oldY) != std::nullopt && IsMovePossible(newX, newY))
	{
        auto pieces = GetEnemyPiecesAround(newX, newY, GetData(oldX, oldY)->Colour);
        if (std::ranges::any_of(pieces, [this](std::pair<int, int> t) {return GetData(t.first, t.second)->Type == PoisonFlame;}))
		{
			SetData(oldX, oldY, std::nullopt);
			if (GetData(newX, newY) != std::nullopt)
			{
				SetData(newX, newY, std::nullopt);
			}
			return true;
		}
		// Poison Flame moves
        if (GetData(oldX, oldY)->Type == PoisonFlame)
		{
			std::ranges::for_each(pieces, [&](std::pair<int, int> p) {SetData(p.first, p.second, std::nullopt);});
		}
	}
	const bool result = DaiShogiBoard::Move(oldX, oldY, newX, newY, cl);
	// If the Taoist priest is captured, the drum and banner can no longer promote, and if either or both have already promoted, then they immediately revert.
    if (result == true && GetData(newX, newY) != std::nullopt && GetData(newX, newY)->Type == TaoistPriest)
	{
		_taoistPriestCaptured = true;
        const auto raLocation = GetPieceLocation(RoamingAssault, sp->Colour == White ? Black : White);
		if (raLocation.first != -1 && raLocation.second != -1)
		{
            Demote(raLocation.first, raLocation.second);
		}
        const auto tcLocation = GetPieceLocation(Thunderclap, sp->Colour == White ? Black : White);
		if (tcLocation.first != -1 && tcLocation.second != -1)
		{
            Demote(tcLocation.first, tcLocation.second);
		}
	}
	// Whenever the immaculate light is within 5 intersections of the five-li fog, the fog reverts to a Taoist priest.
    if (result == true && sp != std::nullopt && sp->Type == ExtensiveFog)
	{
        const auto hlLocation = GetPieceLocation(HolyLight, sp->Colour == White ? Black : White);
		if (hlLocation.first != -1 && hlLocation.second != -1 && abs(hlLocation.first - newX) <= 5 && abs(hlLocation.second - newY) <= 5)
		{
            Demote(newX, newY);
		}
	}
    else if (result == true && sp != std::nullopt && sp->Type == HolyLight)
	{
        const auto efLocation = GetPieceLocation(ExtensiveFog, sp->Colour == White ? Black : White);
		if (efLocation.first != -1 && efLocation.second != -1 && abs(efLocation.first - newX) <= 5 && abs(efLocation.second - newY) <= 5)
		{
            Demote(efLocation.first, efLocation.second);
		}
	}
	// Skyward net and Earthward net immobilize all enemy pieces in its ranging directions
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (GetData(i, j) != std::nullopt)
			{
				_data[i][j]->CanMove = true;
			}
		}
	}
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			auto piece = GetData(i, j);
			if (piece != std::nullopt && (piece->Type == SkywardNet || piece->Type == EarthwardNet))
			{
				Immobilize(i, j, West);
				Immobilize(i, j, East);
				if (piece->Type == SkywardNet)
				{
					if (piece->Colour == Black)
					{
						Immobilize(i, j, NorthWest);
						Immobilize(i, j, NorthEast);
					}
					else
					{
						Immobilize(i, j, SouthWest);
						Immobilize(i, j, SouthEast);
					}
				}
				if (piece->Type == EarthwardNet)
				{
					if (piece->Colour == Black)
					{
						Immobilize(i, j, SouthWest);
						Immobilize(i, j, SouthEast);
					}
					else
					{
						Immobilize(i, j, NorthWest);
						Immobilize(i, j, NorthEast);
					}
				}
			}
		}
	}
	return result;
}

void KoShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	if (!piece->CanMove) return;
	switch (piece->Type)
	{
	case Pawn:
		// If the drum is killed, the pawns may no longer move forward.
        if (piece->Colour == Black)
		{
            if (GetPieceLocation(Drum, piece->Colour).first != -1 ||
                GetPieceLocation(Thunderclap, piece->Colour).first != -1)
			{
				CheckMove(piece, x, y + 1);
			}
			CheckMove(piece, x, y - 1);
		}
		else
		{
            if (GetPieceLocation(Drum, piece->Colour).first != -1 ||
                GetPieceLocation(Thunderclap, piece->Colour).first != -1)
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
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, South);
		}
		else
		{
			CheckDirection(piece, x, y, North);
		}
		break;
	case AdvanceGuard:
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
        getAll5StepPaths(x, y, piece->Colour);
		break;
	case PoisonFlame:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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
        if (piece->Colour == Black)
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

std::vector<std::pair<int, int>> KoShogiBoard::GetShoots(const std::optional<Piece>& piece, int x, int y)
{
	_shoots.clear();
    switch (piece->Type)
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

void KoShogiBoard::CheckPriestMove(const std::optional<Piece>& piece, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
        if (GetData(x, y) != std::nullopt && GetData(x, y)->Type != TaoistPriest && GetData(x, y)->Type != SpiritualMonk &&
            GetData(x, y)->Type != ExtensiveFog && GetData(x, y)->Type != HolyLight)
		{
		}
        else if (GetData(x, y) == std::nullopt || GetData(x, y)->Colour != piece->Colour)
		{
			_moves.emplace_back(x, y);
		}
	}
}

void KoShogiBoard::Shoot(int x, int y)
{
	if (GetData(x, y) != std::nullopt)
	{
		SetData(x, y, std::nullopt);
	}
}

void KoShogiBoard::CheckShoot(const std::optional<Piece>& piece, int x, int y)
{
    const PieceType pt = piece->Type;
	// Except for the Taoist priest, spiritual monk, five-li fog or immaculate light, any shooting pieces
	// are disabled from shooting if they are within five intersections of an enemy five-li fog.
	if (pt != TaoistPriest && pt != SpiritualMonk && pt != ExtensiveFog && pt != HolyLight)
	{
        const auto fogLocation = GetPieceLocation(ExtensiveFog, piece->Colour == White ? Black : White);
		if (fogLocation.first != -1 && fogLocation.second != -1 && (abs(fogLocation.first - x) <= 5 && abs(fogLocation.second - y) <= 5))
		{
			return;
		}
	}
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
        if (GetData(x, y) != std::nullopt && GetData(x, y)->Colour != piece->Colour)
		{
            const auto dt = GetData(x, y)->Type;
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

void KoShogiBoard::CheckShootingDirection(const std::optional<Piece>& piece, int x, int y, Direction direction, int count, bool shootOver)
{
	int i = 0;
	while (InBounds(x, y, direction) && i < count)
	{
		CheckDirectionInc(x, y, direction);
		if (GetData(x, y) != std::nullopt)
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
		if (nr < 0 || nr >= _width || nc < 0 || nc >= _width) {
			continue;
		}
        if (GetData(nr, nc) != std::nullopt && GetData(nr, nc)->Colour == pieceColour) {
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
std::vector<std::pair<int, int>> KoShogiBoard::getSinglePieceMoves(int r, int c, const std::vector<std::pair<int, int>>& offsets, const std::optional<Piece>& piece) const
{
	std::vector<std::pair<int, int>> result;
	for (auto& offset : offsets) {
		int rr = r + offset.first;
		int cc = c + offset.second;
		if (rr < 0 || rr >= _width || cc < 0 || cc >= _width) {
			continue;
		}

        if (piece->Type == ExtensiveFog || piece->Type == HolyLight)
		{
            if (GetData(rr, cc) != std::nullopt && GetData(rr, cc)->Type != TaoistPriest && GetData(rr, cc)->Type != SpiritualMonk &&
                GetData(rr, cc)->Type != ExtensiveFog && GetData(rr, cc)->Type != HolyLight) {
				continue;
			}
		}

		// The piece can land on this square if it's EMPTY or ENEMY
        if (GetData(rr, cc) != std::nullopt && GetData(rr, cc)->Colour == piece->Colour) {
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
void KoShogiBoard::getAllPiece2MoveDestinations(int startR, int startC, const std::vector<std::pair<int, int>>& offsets, const std::optional<Piece>& piece)
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

bool KoShogiBoard::IsTaoistPriestCaptured() const
{
	return _taoistPriestCaptured;
}

std::string KoShogiBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    PieceType basePieceType = GetData(x, y)->BaseType;
    switch (pieceType)
    {
    case King:
        return "K";
    case MiddleTroop:
        return "M";
    case Prince:
        return "+M";
    case Drum:
        return "U";
    case Thunderclap:
        return "+U";
    case Flag:
        return "L";
    case RoamingAssault:
        return "+L";
    case Tiger:
        return "T";
    case DragonHorse:
        return basePieceType == Tiger ? "+T" : "H";
    case Elephant:
        return "E";
    case DragonKing:
        return basePieceType == Elephant ? "+E" : "D";
    case Gold:
        return "G";
    case FlyingStag:
        return "+G";
    case Silver:
        return "S";
    case CompanyCommander:
        return "+S";
    case Leopard:
        return "F";
    case ViceCommissioner:
        return "+F";
    case Copper:
        return "C";
    case PoisonFlame:
        return "+C";
    case Lion:
        return "N";
    case Kylin:
        return "O";
    case DoubleKylin:
        return "+O";
    case Phoenix:
        return "X";
    case DoublePhoenix:
        return "+X";
    case TaoistPriest:
        return "T'";
    case SpiritualMonk:
        return "S'";
    case ExtensiveFog:
        return "+T'";
    case HolyLight:
        return "+S'";
    case AdvanceGuard:
        return "A'";
    case RearGuard:
        return "R'";
    case SkywardNet:
        return "+A'";
    case EarthwardNet:
        return "+R'";
    case Queen:
        return basePieceType == Rook ? "+R" : "Q";
    case RisingDragon:
        return "+Q";
    case WingedTiger:
        return "+D";
    case FlyingHawk:
        return "+H";
    case Bishop:
        return "B";
    case Longbow:
        return "L'";
    case LongbowKnight:
        return "+L'";
    case Crossbow:
        return "C'";
    case CrossbowKnight:
        return "+C'";
    case Cannon:
        return "I";
    case CannonCarriage:
        return "+I";
    case FrankishCannon:
        return "J";
    case DivineCarriage:
        return "+J";
    case Knight:
        return "Y";
    case KnightCaptain:
        return basePieceType == Knight ? "+Y" : "W";
    case WingedHorse:
        return "+W";
    case Pawn:
        return "P";
    case VerticalMover:
        return basePieceType == Pawn ? "+P" : "V";
    case FlyingOx:
        return "+V";
    case CatSword:
        return "Z";
    case ShieldCaptain:
        return basePieceType == CatSword ? "+Z": "U'";
    case FreeBoar:
        return "F'";
    case Chariot:
        return "A";
    case Rook:
        return basePieceType == Chariot ? "+A" : "R";
    case Vanguard:
        return "V'";
    default:
        return "";
    }
}
