#include "MakaDaiDaiShogiBoard.h"

MakaDaiDaiShogiBoard::MakaDaiDaiShogiBoard()
{
	_width = 19;
	_height = 19;
	MakaDaiDaiShogiBoard::Initialize();
}

MakaDaiDaiShogiBoard::~MakaDaiDaiShogiBoard()
{
}

void MakaDaiDaiShogiBoard::Initialize()
{
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

Board* MakaDaiDaiShogiBoard::Clone()
{
	MakaDaiDaiShogiBoard* cb = new MakaDaiDaiShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? cb->CreatePiece(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

void MakaDaiDaiShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (_data[x][y] != std::nullopt)
    {
		_data[x][y]->IsPromoted = true;
        if (pt != None)
        {
			_data[x][y]->Type = pt;
            return;
        }
        PieceType pieceType = None;
        switch (pieceType)
        {
        case King:
            pieceType = Emperor;
            break;
        case Elephant:
            pieceType = King;
            break;
        case Deva:
            pieceType = TeachingKing;
            break;
        case DarkSpirit:
            pieceType = BuddhistSpirit;
            break;
        case Gold:
            pieceType = FreeGold;
            break;
        case Silver:
            pieceType = FreeSilver;
            break;
        case Copper:
            pieceType = FreeCopper;
            break;
        case Iron:
            pieceType = FreeIron;
            break;
        case Tile:
            pieceType = FreeTile;
            break;
        case Stone:
            pieceType = FreeStone;
            break;
        case GoBetween:
            pieceType = FreeGo;
            break;
        case Earth:
            pieceType = FreeEarth;
            break;
        case Tiger:
            pieceType = FreeTiger;
            break;
        case Leopard:
            pieceType = FreeLeopard;
            break;
        case CoiledSerpent:
            pieceType = FreeSerpent;
            break;
        case RecliningDragon:
            pieceType = FreeDragon;
            break;
        case OldMonkey:
            pieceType = MountainWitch;
            break;
        case ChineseCock:
            pieceType = WizardStork;
            break;
        case CatSword:
            pieceType = FreeCat;
            break;
        case Lion:
            pieceType = FuriousFiend;
            break;
        case Phoenix:
            pieceType = GoldenBird;
            break;
        case Kylin:
            pieceType = GreatDragon;
            break;
        case EvilWolf:
            pieceType = FreeWolf;
            break;
        case BlindBear:
            pieceType = FreeBear;
            break;
        case AngryBoar:
            pieceType = FreeBoar;
            break;
        case OldRat:
            pieceType = Bat;
            break;
        case Lance:
        case ReverseChariot:
        case LionDog:
        case Wrestler:
        case Guardian:
        case BuddhistDevil:
        case Yaksha:
        case FlyingDragon:
        case ViolentOx:
        case Knight:
        case Donkey:
        case Capricorn:
        case HookMover:
        case Bishop:
        case Rook:
        case VerticalMover:
        case SideMover:
        case LeftChariot:
        case RightChariot:
        case SideFlier:
        case Pawn:
            pieceType = Gold;
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

void MakaDaiDaiShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
	case Emperor:
		for (int i = 0; i < GetWidth(); i++)
		{
			for (int j = 0; j < GetHeight(); j++)
			{
				const std::optional<Piece> p = GetData(i, j);
				if (p == std::nullopt)
				{
					_moves.emplace_back(i, j);
				}
                else if (p->Colour != piece->Colour)
				{
                    if (p->Type == King || p->Type == Prince || p->Type == Emperor)
					{
						const std::vector<std::pair<int, int>> royalDefenders = GetDefenders(i, j);
						if (royalDefenders.empty())
						{
							_moves.emplace_back(i, j);
						}
					}
					else
					{
						_moves.emplace_back(i, j);
					}
				}
			}
		}
		break;
	case TeachingKing:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);

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
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x, y + 2);

		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 2);

		CheckMove(piece, x - 3, y - 3);
		CheckMove(piece, x + 3, y - 3);
		CheckMove(piece, x - 3, y);
		CheckMove(piece, x + 3, y);
		CheckMove(piece, x, y - 3);
		CheckMove(piece, x, y + 3);
		CheckMove(piece, x - 3, y + 3);
		CheckMove(piece, x + 3, y + 3);
		break;
	case BuddhistSpirit:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);

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
		break;
	case FuriousFiend:
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

		CheckMove(piece, x - 3, y - 3);
		CheckMove(piece, x + 3, y - 3);
		CheckMove(piece, x - 3, y);
		CheckMove(piece, x + 3, y);
		CheckMove(piece, x, y - 3);
		CheckMove(piece, x, y + 3);
		CheckMove(piece, x - 3, y + 3);
		CheckMove(piece, x + 3, y + 3);
		break;
	case LionDog:
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
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x, y + 2);

		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 2);

		CheckMove(piece, x - 3, y - 3);
		CheckMove(piece, x + 3, y - 3);
		CheckMove(piece, x - 3, y);
		CheckMove(piece, x + 3, y);
		CheckMove(piece, x, y - 3);
		CheckMove(piece, x, y + 3);
		CheckMove(piece, x - 3, y + 3);
		CheckMove(piece, x + 3, y + 3);
		break;
	case Capricorn:
		GetAllPossibleMoves(x, y, true);
		break;
	case HookMover:
		GetAllPossibleMoves(x, y, false);
		break;
	case Deva:
        if (piece->Colour == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x + 1, y - 1);
		}
		CheckMove(piece, x - 1, y);
		break;
	case DarkSpirit:
        if (piece->Colour == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y - 1);
		}
		CheckMove(piece, x + 1, y);
		break;
	case Tile:
        if (piece->Colour == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x, y - 1);
		}
		break;
	case Earth:
        if (piece->Colour == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		break;
	case FreeGold:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
        if (piece->Colour == White)
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
	case FreeSilver:
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
	case FreeCopper:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
        if (piece->Colour == White)
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
	case FreeIron:
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, NorthWest);
		}
		break;
	case FreeTile:
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, NorthWest);
		}
		break;
	case FreeStone:
        if (piece->Colour == White)
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
	case FreeEarth:
	case FreeGo:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case FreeTiger:
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case FreeLeopard:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		break;
	case CoiledSerpent:
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		break;
	case RecliningDragon:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		break;
	case FreeSerpent:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
        if (piece->Colour == White)
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
	case FreeDragon:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
        if (piece->Colour == White)
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
	case OldMonkey:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y - 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
		}
		break;
	case MountainWitch:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case ChineseCock:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x, y - 1);
		}
		break;
	case WizardStork:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case FreeCat:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		break;
	case GoldenBird:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, NorthEast, 3);
		CheckDirection(piece, x, y, NorthWest, 3);
		CheckDirection(piece, x, y, SouthEast, 3);
		CheckDirection(piece, x, y, SouthWest, 3);
		CheckDirection(piece, x, y, East, 2);
		CheckDirection(piece, x, y, West, 2);
		break;
	case GreatDragon:
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthEast, 3);
		CheckDirection(piece, x, y, NorthWest, 3);
		CheckDirection(piece, x, y, SouthEast, 3);
		CheckDirection(piece, x, y, SouthWest, 3);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
		break;
	case FreeWolf:
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, SouthWest);
		}
		else
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, NorthWest);
		}
		break;
	case BlindBear:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case FreeBear:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case OldRat:
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, SouthEast, 2);
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckDirection(piece, x, y, North, 2);
		}
		else
		{
			CheckDirection(piece, x, y, NorthEast, 2);
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckDirection(piece, x, y, South, 2);
		}
		break;
	case Bat:
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		else
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		break;
	case Wrestler:
		CheckDirection(piece, x, y, NorthWest, 3);
		CheckDirection(piece, x, y, NorthEast, 3);
		CheckDirection(piece, x, y, SouthWest, 3);
		CheckDirection(piece, x, y, SouthEast, 3);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		break;
	case Guardian:
		CheckDirection(piece, x, y, West, 3);
		CheckDirection(piece, x, y, North, 3);
		CheckDirection(piece, x, y, South, 3);
		CheckDirection(piece, x, y, East, 3);
        if (piece->Colour == White)
		{
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		break;
	case BuddhistDevil:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, SouthWest, 3);
			CheckDirection(piece, x, y, SouthEast, 3);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, NorthWest, 3);
			CheckDirection(piece, x, y, NorthEast, 3);
			CheckMove(piece, x, y - 1);
		}
		break;
	case Yaksha:
		CheckDirection(piece, x, y, NorthWest, 2);
		CheckDirection(piece, x, y, NorthEast, 2);
		CheckDirection(piece, x, y, SouthWest, 2);
		CheckDirection(piece, x, y, SouthEast, 2);
		CheckDirection(piece, x, y, West, 5);
		CheckDirection(piece, x, y, North, 5);
		CheckDirection(piece, x, y, South, 5);
		CheckDirection(piece, x, y, East, 5);
		break;
	case Donkey:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x - 1, y);
		break;
	case LeftChariot:
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, SouthWest, 3);
			CheckDirection(piece, x, y, NorthEast, 3);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, NorthWest);
			CheckMove(piece, x, y - 1);
		}
		break;
	case RightChariot:
        if (piece->Colour == White)
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, NorthWest);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, NorthEast, 3);
			CheckDirection(piece, x, y, SouthWest, 3);
			CheckMove(piece, x, y - 1);
		}
		break;
	case SideFlier:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}

bool MakaDaiDaiShogiBoard::TripleMove(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (x1 == x4 && y1 == y4 || std::any_of(_moves.begin(), _moves.end(), [=](std::pair<int, int> t) {return t.first == x4 && t.second == y4;}))
	{
		if (x1 != x2 || y1 != y2)
		{
			if (GetData(x2, y2) != std::nullopt)
			{
				SetData(x2, y2, std::nullopt);
			}
		}
		if (x1 != x3 || y1 != y3)
		{
			if (GetData(x3, y3) != std::nullopt)
			{
				SetData(x3, y3, std::nullopt);
			}
		}
		if (x1 != x4 || y1 != y4)
		{
			SetData(x4, y4, GetData(x1, y1));
			SetData(x1, y1, std::nullopt);
		}
		return true;
	}
	return false;
}

std::vector<std::pair<int, int>> MakaDaiDaiShogiBoard::GetRay(int startR, int startC, int dr, int dc, int n, PieceColour pieceColour) const
{
	std::vector<std::pair<int, int>> result;
	int r = startR;
	int c = startC;

	while (true) {
		r += dr;
		c += dc;
		if (r < 0 || r >= n || c < 0 || c >= n) {
			break;
		}
		const std::optional<Piece> d = GetData(r, c);
        if (d != std::nullopt && d->Colour == pieceColour) {
			break;
		}

		result.emplace_back(r, c);

        if (d != std::nullopt && d->Colour != pieceColour) {
			break;
		}
	}
	return result;
}

void MakaDaiDaiShogiBoard::GetAllPossibleMoves(int startR, int startC, bool diagonal)
{
	std::vector<std::pair<int, int>> directions;
	if (diagonal)
	{
		directions.emplace_back(-1, -1);
		directions.emplace_back(-1, +1);
		directions.emplace_back(+1, -1);
		directions.emplace_back(+1, +1);
	}
	else
	{
		directions.emplace_back(+0, -1);
		directions.emplace_back(+0, +1);
		directions.emplace_back(-1, +0);
		directions.emplace_back(+1, +0);
	}

	std::set<std::pair<int, int>> reachable;

	// We consider up to two diagonal segments:
	//   (Segment1) in direction d1
	//   (Segment2) in direction d2 (which may be the same as d1 or different)

    const PieceColour pieceColour = GetData(startR, startC) != std::nullopt ? GetData(startR, startC)->Colour : White;

	for (const auto& d1 : directions) {
		constexpr int BOARD_SIZE = 19;
		// All squares we can reach in the first segment (in direction d1).
		auto firstSegment = GetRay(startR, startC, d1.first, d1.second, BOARD_SIZE, pieceColour);

		{
			for (const auto& d2 : directions) {
				auto secondSegment = GetRay(startR, startC, d2.first, d2.second, BOARD_SIZE, pieceColour);
				for (auto& sq2 : secondSegment) {
					reachable.insert(sq2);
				}
			}
		}

		for (const auto& sq1 : firstSegment) {
			int r1 = sq1.first;
			int c1 = sq1.second;

			reachable.insert({ r1, c1 });

			if (GetData(r1, c1) != std::nullopt) {
				continue;  // skip second segment
			}

			for (const auto& d2 : directions) {
				auto secondSegment = GetRay(r1, c1, d2.first, d2.second, BOARD_SIZE, pieceColour);
				for (auto& sq2 : secondSegment) {
					reachable.insert(sq2);
				}
			}
		}
	}

	_moves.insert(_moves.end(), reachable.begin(), reachable.end());
}
