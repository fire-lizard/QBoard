#include "DaiShogiBoard.h"

DaiShogiBoard::DaiShogiBoard()
{
	_width = 15;
	_height = 15;
	DaiShogiBoard::Initialize();
}

DaiShogiBoard::~DaiShogiBoard()
{
}

void DaiShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new DaiShogiPiece(_initialSetup[j][i], j < 7 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* DaiShogiBoard::Clone()
{
	DaiShogiBoard* cb = new DaiShogiBoard();
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

Piece* DaiShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new DaiShogiPiece(pieceType, pieceColour);
}

void DaiShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Knight:
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
	case ViolentOx:
		CheckDirection(piece, x, y, South, 2);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, West, 2);
		CheckDirection(piece, x, y, East, 2);
		break;
	case FlyingDragon:
		CheckDirection(piece, x, y, SouthWest, 2);
		CheckDirection(piece, x, y, NorthWest, 2);
		CheckDirection(piece, x, y, SouthEast, 2);
		CheckDirection(piece, x, y, NorthEast, 2);
		break;
	case AngryBoar:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		break;
	case CatSword:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case EvilWolf:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x - 1, y);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case Iron:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case Stone:
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
	case WaterBuffalo:
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, North, 2);
		CheckDirection(piece, x, y, South, 2);
		break;
	default:
		ChuShogiBoard::GetMoves(piece, x, y);
		break;
	}
}

void DaiShogiBoard::CheckLionDirection(const Piece* piece, int x, int y, Direction direction, int count)
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
