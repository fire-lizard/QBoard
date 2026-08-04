#include "DaiDaiShogiBoard.h"

DaiDaiShogiBoard::DaiDaiShogiBoard()
{
	_width = 17;
	_height = 17;
	DaiDaiShogiBoard::Initialize();
}

DaiDaiShogiBoard::~DaiDaiShogiBoard()
{
}

void DaiDaiShogiBoard::Initialize()
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

Board* DaiDaiShogiBoard::Clone()
{
	DaiDaiShogiBoard* cb = new DaiDaiShogiBoard();
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

PieceType DaiDaiShogiBoard::PromotesTo(PieceType pieceType) const
{
	switch (pieceType)
	{
	case BlindMonkey:
		return MountainWitch;
	case Kylin:
		return GreatDragon;
	case Phoenix:
		return GoldenBird;
	case Lion:
		return FuriousFiend;
	case WesternBarbarian:
		return LionDog;
	case CatSword:
		return DragonHorse;
	case EasternBarbarian:
		return Lion;
	case EnchantedBadger:
		return Dove;
	case EnchantedFox:
		return Yaksha;
	case FlyingDragon:
		return DragonKing;
	case FlyingHorse:
		return Queen;
	case LionDog:
		return GreatElephant;
	case NeighboringKing:
		return StandardBearer;
	case NorthernBarbarian:
		return FragrantElephant;
	case OldKite:
		return Tengu;
	case OldRat:
		return WizardStork;
	case PoisonousSnake:
		return HookMover;
	case PrancingStag:
		return SquareMover;
	case RushingBird:
		return FreeDemon;
	case SouthernBarbarian:
		return WhiteElephant;
	case WaterBuffalo:
		return FreeDreamEater;
	default:
		return None;
	}
}

void DaiDaiShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
	case Tengu:
		GetAllPossibleMoves(x, y, true, false);

		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		break;
	case GreatElephant:
		CheckDirection(piece, x, y, North, 3);
		CheckDirection(piece, x, y, South, 3);
		CheckDirection(piece, x, y, West, 5);
		CheckDirection(piece, x, y, East, 5);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest, 3);
			CheckDirection(piece, x, y, NorthEast, 3);
			CheckDirection(piece, x, y, SouthWest, 5);
			CheckDirection(piece, x, y, SouthEast, 5);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest, 3);
			CheckDirection(piece, x, y, SouthEast, 3);
			CheckDirection(piece, x, y, NorthWest, 5);
			CheckDirection(piece, x, y, NorthEast, 5);
		}
		break;
	case OldKite:
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x + 1, y + 1);
			CheckMove(piece, x - 1, y + 1);
		}
		else
		{
			CheckMove(piece, x + 1, y - 1);
			CheckMove(piece, x - 1, y - 1);
		}
		break;
	case PoisonousSnake:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 2);
			CheckMove(piece, x + 2, y - 2);
			CheckMove(piece, x - 2, y - 2);
		}
		else
		{
			CheckMove(piece, x, y - 2);
			CheckMove(piece, x + 2, y + 2);
			CheckMove(piece, x - 2, y + 2);
		}
		break;
	case WesternBarbarian:
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y + 1);
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
	case EasternBarbarian:
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
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
	case NorthernBarbarian:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthEast, 2);
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		else
		{
			CheckDirection(piece, x, y, SouthEast, 2);
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		break;
	case SouthernBarbarian:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, SouthEast, 2);
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, NorthEast, 2);
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case FragrantElephant:
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckDirection(piece, x, y, SouthEast, 2);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckDirection(piece, x, y, NorthEast, 2);
		}
		break;
	case WhiteElephant:
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckDirection(piece, x, y, NorthEast, 2);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckDirection(piece, x, y, SouthEast, 2);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case StandardBearer:
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
			CheckDirection(piece, x, y, South, 2);
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckDirection(piece, x, y, SouthEast, 2);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
			CheckDirection(piece, x, y, North, 2);
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckDirection(piece, x, y, NorthEast, 2);
		}
		break;
	case FlyingHorse:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckDirection(piece, x, y, NorthEast, 2);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckDirection(piece, x, y, SouthEast, 2);
		}
		break;
	case EnchantedBadger:
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, North, 2);
		}
		else
		{
			CheckDirection(piece, x, y, South, 2);
		}
		break;
	case EnchantedFox:
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, South, 2);
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckDirection(piece, x, y, NorthEast, 2);
		}
		else
		{
			CheckDirection(piece, x, y, North, 2);
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckDirection(piece, x, y, SouthEast, 2);
		}
		break;
	case PrancingStag:
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case WhiteTiger:
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, SouthEast);
			CheckMove(piece, x - 1, y - 1);
		}
		break;
	case BlueDragon:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthEast);
			CheckMove(piece, x - 1, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case ViolentBear:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthEast, 2);
			CheckDirection(piece, x, y, NorthWest, 2);
		}
		else
		{
			CheckDirection(piece, x, y, SouthEast, 2);
			CheckDirection(piece, x, y, SouthWest, 2);
		}
		break;
	case SavageTiger:
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
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
	case Wood:
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, NorthWest, 2);
			CheckDirection(piece, x, y, NorthEast, 2);
		}
		else
		{
			CheckDirection(piece, x, y, SouthWest, 2);
			CheckDirection(piece, x, y, SouthEast, 2);
		}
		break;
	case FreeDreamEater:
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, West, 5);
		CheckDirection(piece, x, y, East, 5);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		break;
	case FreeDemon:
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, North, 5);
		CheckDirection(piece, x, y, South, 5);
		break;
	case RushingBird:
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
        if (piece->Colour == Black)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case NeighboringKing:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case BlindMonkey:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case Dove:
		CheckDirection(piece, x, y, NorthWest, 5);
		CheckDirection(piece, x, y, SouthWest, 5);
		CheckDirection(piece, x, y, NorthEast, 5);
		CheckDirection(piece, x, y, SouthEast, 5);

		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
		CheckDirection(piece, x, y, East, 2);
		CheckDirection(piece, x, y, West, 2);
		break;
	case RacingChariot:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
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
	case SquareMover:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
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
	case HowlingDog:
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
	case LeftGeneral:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x + 1, y);
		}
		else
		{
			CheckMove(piece, x - 1, y);
		}
		break;
	case RightGeneral :
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
		{
			CheckMove(piece, x - 1, y);
		}
		else
		{
			CheckMove(piece, x + 1, y);
		}
		break;
	default:
		MakaDaiDaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
