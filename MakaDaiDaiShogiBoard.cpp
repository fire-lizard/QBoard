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
				_data[i][j] = new MakaDaiDaiShogiPiece(_initialSetup[j][i], j < 8 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
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
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

Piece* MakaDaiDaiShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new MakaDaiDaiShogiPiece(pieceType, pieceColour);
}

void MakaDaiDaiShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Emperor:
		break;
	case TeachingKing:
		break;
	case BuddhistSpirit:
		break;
	case FuriousFiend:
		break;
	case LionDog:
		break;
	case Capricorn:
		break;
	case HookMover:
		break;
	case Deva:
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
	case RecliningDragon:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
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
	case FreeSerpent:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, South);
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == Black)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
		if (piece->GetColour() == White)
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
