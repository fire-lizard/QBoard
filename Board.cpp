#include "Board.h"

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
			if (GetData(i, j) != std::nullopt)
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

std::vector<std::pair<int, int>> Board::Moves() const
{
	return _moves;
}

std::optional<Piece> Board::GetData(int x, int y) const
{
    if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
    {
        return _data[x][y];
    }
    return std::nullopt;
}

void Board::SetData(int x, int y, const std::optional<Piece>& p)
{
    if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
    {
        _data[x][y]= p;
    }
}

int Board::MoveCount() const
{
	return (_moveCount / 2) + 1;
}

void Board::SetMoveCount(int moveCount)
{
	_moveCount = moveCount;
}

std::string Board::GetFEN() const
{
	std::string fen;
	int emptySquares = 0;
	for (int j = 0; j < _height; j++)
	{
		for (int i = 0; i < _width; i++)
		{
			if (GetData(i, j) != std::nullopt)
			{
				if (emptySquares > 0)
				{
					fen.append(std::to_string(emptySquares));
					emptySquares = 0;
				}
				std::string sc = GetStringCode(i, j);
                if (GetData(i, j)->Colour == Black)
				{
					std::ranges::transform(sc, sc.begin(), [](const char v) { return static_cast<char>(std::tolower(v)); });
				}
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

void Board::CheckMove(const std::optional<Piece>& piece, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= _width - 1 && y <= _height - 1)
	{
        if (GetData(x, y) == std::nullopt || GetData(x, y)->Colour != piece->Colour)
		{
			_moves.emplace_back(x, y);
		}
	}
}

void Board::CheckDirection(const std::optional<Piece>& piece, int x, int y, Direction direction)
{
	while (InBounds(x, y, direction))
	{
		CheckDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
		if (GetData(x, y) != std::nullopt)
		{
			break;
		}
	}
}

void Board::CheckDirection(const std::optional<Piece>& piece, int x, int y, Direction direction, int count)
{
	int i = 0;
	while (InBounds(x, y, direction) && i < count)
	{
		CheckDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
		if (GetData(x, y) != std::nullopt)
		{
			break;
		}
		i++;
	}
}

bool Board::InBounds(int x, int y, Direction direction) const
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

bool Board::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	if (std::ranges::any_of(_moves, [=](std::pair<int, int> t) {return t.first == newX && t.second == newY;}) || !cl)
	{
		SetData(newX, newY, GetData(oldX, oldY));
		SetData(oldX, oldY, std::nullopt);
		return true;
	}
	return false;
}

void Board::RemoveMove(int x, int y)
{
	const auto it = std::ranges::remove_if(_moves, [=](const auto& p) { return p.first == x && p.second == y; }).begin();
	_moves.erase(it, _moves.end());
}

void Board::RemoveMoves()
{
	_moves.clear();
}

std::vector<std::tuple<int, int, int, int>> Board::GetAllMoves(PieceColour pieceColour)
{
	std::vector<std::tuple<int, int, int, int>> result;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
            if (GetData(i, j) != std::nullopt && GetData(i, j)->Colour == pieceColour)
			{
				GetMoves(GetData(i, j), i, j);
				std::ranges::for_each(_moves, [&](std::pair<int, int> p) {result.emplace_back(i, j, p.first, p.second);});
			}
		}
	}
	return result;
}

bool Board::CheckPosition(int x, int y) const
{
	return y < _height && y >= 0 && x < _width && x >= 0;
}

std::pair<int, int> Board::FindNearestPiece(int x, int y, Direction direction) const
{
    while (InBounds(x, y, direction))
    {
        CheckDirectionInc(x, y, direction);
        if (GetData(x, y) != std::nullopt)
        {
            return {x, y};
        }
    }
    return {-1, -1};
}

bool Board::HasPiece(PieceType pieceType, PieceColour pieceColour) const
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
            if (GetData(i, j) != std::nullopt && GetData(i, j)->Type == pieceType && GetData(i, j)->Colour == pieceColour)
			{
				return true;
			}
		}
	}
	return false;
}

std::pair<int, int> Board::GetPieceLocation(PieceType pieceType, PieceColour pieceColour) const
{
    int kx = -1, ky = -1;
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const std::optional<Piece> p = GetData(i, j);
            if (p != std::nullopt && p->BaseType == pieceType && p->Colour == pieceColour)
            {
                kx = i;
                ky = j;
                break;
            }
        }
        if (kx > -1 && ky > -1)
            break;
    }
    return { kx, ky };
}

std::vector<std::pair<int, int>> Board::GetAttackers(int x, int y)
{
	std::vector<std::pair<int, int>> vec;
	if (GetData(x, y) != std::nullopt)
	{
        const PieceColour pieceColour = GetData(x, y)->Colour;
		Board* board = this->Clone();
		board->SetData(x, y, std::nullopt);
		const auto opponentMoves = board->GetAllMoves(pieceColour == White ? Black : White);
		for (auto tpl : opponentMoves)
		{
			if (std::get<2>(tpl) == x && std::get<3>(tpl) == y)
			{
				vec.emplace_back(std::get<0>(tpl), std::get<1>(tpl));
			}
		}
		delete board;
	}
	return vec;
}

std::vector<std::pair<int, int>> Board::GetDefenders(int x, int y)
{
	std::vector<std::pair<int, int>> vec;
	if (GetData(x, y) != std::nullopt)
	{
        const PieceColour pieceColour = GetData(x, y)->Colour;
		Board* board = this->Clone();
		board->SetData(x, y, std::nullopt);
		const auto playerMoves = board->GetAllMoves(pieceColour);
		for (auto tpl : playerMoves)
		{
			if (std::get<2>(tpl) == x && std::get<3>(tpl) == y)
			{
				vec.emplace_back(std::get<0>(tpl), std::get<1>(tpl));
			}
		}
		delete board;
	}
	return vec;
}

bool Board::IsMovePossible(int x, int y)
{
	return std::ranges::any_of(_moves, [=](std::pair<int, int> t) {return t.first == x && t.second == y;});
}

bool Board::operator == (const std::string& fen) const
{
	return this->GetFEN() == fen;
}

bool Board::operator != (const std::string& fen) const
{
	return this->GetFEN() != fen;
}

std::string Board::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    PieceType basePieceType = GetData(x, y)->BaseType;
    switch (pieceType)
    {
    case King:
        return "K";
    case Prince:
        return "+E";
    case Lion:
        if (basePieceType == Kylin) return "+O"; else if (basePieceType == EasternBarbarian) return "+C'"; else return "N";
    case Queen:
        if (basePieceType == Phoenix) return "+X"; else if (basePieceType == FlyingHorse) return "+A~"; else return "Q";
    case DragonKing:
        if (basePieceType == Rook) return "+R"; else if (basePieceType == FlyingDragon) return "+F'"; else return "D";
    case DragonHorse:
        if (basePieceType == Bishop) return "+B"; else if (basePieceType == CatSword) return "+Z"; else return "H";
    case Rook:
        return basePieceType == Gold ? "+G": "R";
    case Bishop:
        return basePieceType == Leopard ? "+F" : "B";
    case VerticalMover:
        return basePieceType == Silver ? "+S" : "V";
    case SideMover:
        return basePieceType == Copper ? "+C" : "M";
    case ReverseChariot:
        return "A";
    case Lance:
        return "L";
    case Kylin:
        return "O";
    case Phoenix:
        return "X";
    case Elephant:
        return basePieceType == GoBetween ? "+I" : "E";
    case Tiger:
        return "T";
    case Silver:
        return "S";
    case Copper:
        return "C";
    case Leopard:
        return "F";
    case GoBetween:
        return "I";
    case Pawn:
        return "P";
    case Tokin:
        return "+P";
    case Eagle:
        return basePieceType == DragonKing ? "+D": "E!";
    case Unicorn:
        return basePieceType == DragonHorse ? "+H": "F!";
    case FlyingOx:
        return "+V";
    case FreeBoar:
        return basePieceType == AngryBoar ? "+A" : "+M";
    case FlyingStag:
        return "+T";
    case WhiteHorse:
        return "+L";
    case Whale:
        return "+A";
    case Iron:
        return "J";
    case Stone:
        return "U";
    case AngryBoar:
        return "A'";
    case ViolentOx:
        return "V'";
    case FlyingDragon:
        return "F'";
    case EvilWolf:
        return "W";
    case CatSword:
        return "Z";
    case Knight:
        return "Y";
    case WaterBuffalo:
        return basePieceType == SideSoldier ? "+S'" : "W!";
    case Emperor:
        return "+K";
    case Deva:
        return "A!";
    case DarkSpirit:
        return "G!";
    case TeachingKing:
        return "+A!";
    case BuddhistSpirit:
        return "+G!";
    case FreeGold:
        return "+G";
    case FreeSilver:
        return "+S";
    case FreeCopper:
        return "+C";
    case FreeIron:
        return "+J";
    case FreeTile:
        return "+T'";
    case FreeStone:
        return "+U";
    case FreeEarth:
        return "+E'";
    case FreeGo:
        return "+I";
    case FreeTiger:
        return "+T";
    case FreeLeopard:
        return "+F";
    case CoiledSerpent:
        return "I!";
    case RecliningDragon:
        return "J!";
    case FreeSerpent:
        return "+I!";
    case FreeDragon:
        return "+J!";
    case OldMonkey:
        return "M!";
    case MountainWitch:
        return "+M!";
    case ChineseCock:
        return "K!";
    case WizardStork:
        return "+K!";
    case FreeCat:
        return "+Z";
    case FuriousFiend:
        return "+N";
    case FreeWolf:
        return "+W";
    case BlindBear:
        return "L!";
    case FreeBear:
        return "+L!";
    case OldRat:
        return "O!";
    case Bat:
        return "+O!";
    case Wrestler:
        return "P!";
    case Guardian:
        return "R!";
    case BuddhistDevil:
        return "S!";
    case Donkey:
        return "U!";
    case Capricorn:
        return "X!";
    case LeftChariot:
        return "L'";
    case RightChariot:
        return "R'";
    case SideFlier:
        return "Z!";
    case Tile:
        return "T'";
    case Earth:
        return "E'";
    case Tengu:
        return basePieceType == OldKite ? "+K'" : "J'";
    case Yaksha:
        return basePieceType == EnchantedFox ? "+F~" : "T!";
    case HookMover:
        return basePieceType == PoisonousSnake ? "+M'" : "Y!";
    case OldKite:
        return "K'";
    case PoisonousSnake:
        return "M'";
    case GreatElephant:
        return "+N!";
    case LionDog:
        return basePieceType == WesternBarbarian ? "+B'" : "N!";
    case WesternBarbarian:
        return "B'";
    case EasternBarbarian:
        return "C'";
    case SouthernBarbarian:
        return "G'";
    case NorthernBarbarian:
        return "H'";
    case FragrantElephant:
        return basePieceType == NorthernBarbarian ? "+H'" : "N'";
    case WhiteElephant:
        return basePieceType == SouthernBarbarian ? "+G'" : "O'";
    case FreeDreamEater:
        return basePieceType == WaterBuffalo ? "+W!": "P'";
    case FreeDemon:
        return basePieceType == RushingBird ? "+X'" : "U'";
    case RushingBird:
        return "X'";
    case StandardBearer:
        return basePieceType == NeighboringKing ? "+B~" : "Y'";
    case FlyingHorse:
        return "A~";
    case NeighboringKing:
        return "B~";
    case BlindMonkey:
        return "C~";
    case Dove:
        return basePieceType == EnchantedBadger ? "+E~" : "D~";
    case EnchantedBadger:
        return "E~";
    case EnchantedFox:
        return "F~";
    case RacingChariot:
        return "G~";
    case SquareMover:
        return basePieceType == PrancingStag ? "+I~" : "H~";
    case PrancingStag:
        return "I~";
    case WhiteTiger:
        return "J~";
    case BlueDragon:
        return "K~";
    case HowlingDog:
        return "M~";
    case ViolentBear:
        return "N~";
    case LeftGeneral:
        return "L~";
    case RightGeneral:
        return "R~";
    case SavageTiger:
        return "O~";
    case Wood:
        return "W'";
    case GoldenBird:
        return basePieceType == Phoenix ? "+X" : "P~";
    case GreatDragon:
        return basePieceType == Kylin ? "+O" : "Q~";
    case PromotedLance:
        return "+L";
    case PromotedKnight:
        return "+N";
    case PromotedSilver:
        return "+S";
    case Dog:
        return "D'";
    case MultiGeneral:
        return "+D'";
    case ViceGeneral:
        return basePieceType == BishopGeneral ? "+B!" : "V!";
    case GreatGeneral:
        return basePieceType == RookGeneral ? "+R!" : "Q!";
    case BishopGeneral:
        return basePieceType == Unicorn ? "+F!" : "B!";
    case RookGeneral:
        return basePieceType == Eagle ? "+E!" : "R!";
    case FreeEagle:
        return basePieceType == Queen ? "+Q" : "Q'";
    case LionHawk:
        return basePieceType == Lion ? "+N" : "H!";
    case SideSoldier:
        return basePieceType == Knight ? "+Y" : "S'";
    case VerticalSoldier:
        return basePieceType == Iron ? "+J" : "V'";
    case ChariotSoldier:
        return basePieceType == VerticalSoldier ? "+V'" : "C!";
    case HeavenlyTetrarch:
        return "+C!";
    case FireDemon:
        return basePieceType == WaterBuffalo ? "+W!" : "D!";
    case Gold:
        switch (basePieceType)
        {
        case Iron:
            return "+J";
        case Stone:
            return "+U";
        case AngryBoar:
            return "+A'";
        case ViolentOx:
            return "+V'";
        case FlyingDragon:
            return "+F'";
        case EvilWolf:
            return "+W";
        case CatSword:
            return "+Z";
        case Knight:
            return "+Y";
        case Lance:
            return "+L";
        case ReverseChariot:
            return "+A";
        case LionDog:
            return "+N!";
        case Wrestler:
            return "+P!";
        case Guardian:
            return "+R!";
        case BuddhistDevil:
            return "+S!";
        case Yaksha:
            return "+T!";
        case Donkey:
            return "+U!";
        case Capricorn:
            return "+X!";
        case HookMover:
            return "+Y!";
        case Bishop:
            return "+B";
        case Rook:
            return "+R";
        case VerticalMover:
            return "+V";
        case SideMover:
            return "+M";
        case LeftChariot:
            return "+L'";
        case RightChariot:
            return "+R'";
        case SideFlier:
            return "+Z!";
        case Pawn:
            return "+P";
        default:
            return "G";
        }
    case Archbishop:
        return "A";
    case Chancellor:
        return "C";
    case YariKnight:
        return "N";
    case YariRook:
        return "Y";
    case YariBishop:
        return "B";
    case YariGold:
        return "G";
    case YariSilver:
        return "S";
    default:
        return "";
    }
}
