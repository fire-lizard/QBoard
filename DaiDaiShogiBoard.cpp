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
				_data[i][j] = new DaiDaiShogiPiece(_initialSetup[j][i], j < 8 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
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
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

Piece* DaiDaiShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new DaiDaiShogiPiece(pieceType, pieceColour);
}

void DaiDaiShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Tengu:
		GetAllPossibleMoves(x, y, true);

		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		break;
	case OldKite:
		break;
	case PoisonousSnake:
		break;
	case GreatElephant:
		break;
	case WesternBarbarian:
		break;
	case EasternBarbarian:
		break;
	case NorthernBarbarian:
		break;
	case SouthernBarbarian:
		break;
	case FragrantElephant:
		break;
	case WhiteElephant:
		break;
	case StandardBearer:
		break;
	case FlyingHorse:
		break;
	case EnchantedBadger:
		break;
	case EnchantedFox:
		break;
	case PrancingStag:
		break;
	case WhiteTiger:
		break;
	case BlueDragon:
		break;
	case ViolentBear:
		break;
	case SavageTiger:
		break;
	case Wood:
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
		if (piece->GetColour() == Black)
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
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
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
		if (piece->GetColour() == Black)
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
	case HowlingDog:
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
	case LeftGeneral:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		if (piece->GetColour() == Black)
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
		if (piece->GetColour() == Black)
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
