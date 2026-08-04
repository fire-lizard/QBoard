#include "TaiShogiBoard.h"

TaiShogiBoard::TaiShogiBoard()
{
	_width = 25;
	_height = 25;
	TaiShogiBoard::Initialize();
}

TaiShogiBoard::~TaiShogiBoard()
{
}

Board* TaiShogiBoard::Clone()
{
	TaiShogiBoard* cb = new TaiShogiBoard();
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

void TaiShogiBoard::Initialize()
{
	_moveCount = 0;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
                SetData(i, j, Piece(_initialSetup[j][i], j < 12 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

PieceType TaiShogiBoard::PromotesTo(PieceType pieceType) const
{
	switch (pieceType)
	{
	case Bishop:
	case BuddhistDevil:
	case Capricorn:
	case Donkey:
	case FlyingDragon:
	case Guardian:
	case HookMover:
	case Knight:
	case Rook:
	case SideDragon:
	case SideMover:
	case VerticalMover:
	case Wrestler:
	case Yaksha:
		return Gold;
	case Kylin:
		return GreatDragon;
	case Phoenix:
		return GoldenBird;
	case Lion:
		return FuriousFiend;
	case ChineseCock:
	case OldRat:
		return WizardStork;
	case DarkSpirit:
		return BuddhistSpirit;
	case Deva:
		return TeachingKing;
	case Elephant:
		return Prince;
	case LionDog:
		return GreatElephant;
	case BlindMonkey:
		return MountainWitch;
	case EasternBarbarian:
		return Lion;
	case EnchantedBadger:
		return Dove;
	case FlyingHorse:
		return Queen;
	case NeighboringKing:
		return StandardBearer;
	case NorthernBarbarian:
		return FragrantElephant;
	case OldKite:
		return Tengu;
	case RushingBird:
		return FreeDemon;
	case SouthernBarbarian:
		return WhiteElephant;
	case WaterBuffalo:
		return FreeDreamEater;
	case WesternBarbarian:
		return LionDog;
	case PoisonousSnake:
		return HookMover;
	case PrancingStag:
		return SquareMover;
	default:
		return None;
	}
}

void TaiShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
    case RamHeadSoldier:
		if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		break;
	case GoldenDeer:
		if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
		}
		break;
	case SilverHare:
		if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
		}
		else
		{
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
		}
		break;
	case VermillionSparrow:
		if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
			CheckMove(piece, x, y - 1);
			CheckDirection(piece, x, y, SouthEast, 2);
			CheckDirection(piece, x, y, SouthWest, 2);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
			CheckMove(piece, x, y + 1);
			CheckDirection(piece, x, y, NorthEast, 2);
			CheckDirection(piece, x, y, NorthWest, 2);
		}
		break;
	case TurtleSnake:
		if (piece->Colour == Black)
		{
			CheckMove(piece, x, y - 1);
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
		}
		else
		{
			CheckMove(piece, x, y + 1);
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
		}
		break;
	case Soldier:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		else
		{
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case Peacock:
		GetAllPossibleMoves(x, y, true, true);
		if (piece->Colour == Black)
		{
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
		}
		else
		{
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
		}
		break;
	case FierceEagle:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y - 2);
		break;
	case SideDragon:
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
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
	default:
		DaiDaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
