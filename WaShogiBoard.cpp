#include "WaShogiBoard.h"

WaShogiBoard::WaShogiBoard()
{
	_hasDrops = true;
	_width = 11;
	_height = 11;
	WaShogiBoard::Initialize();
}

WaShogiBoard::~WaShogiBoard()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_data[i][j] != nullptr)
			{
				delete _data[i][j];
			}
		}
	}
}

void WaShogiBoard::Initialize()
{
	_moveCount = 0;
	_capturedPieces.clear();
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new WaShogiPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* WaShogiBoard::Clone()
{
	WaShogiBoard* cb = new WaShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece* p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

Piece* WaShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new WaShogiPiece(pieceType, pieceColour);
}

void WaShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case PloddingOx:
	case BearEyes:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case LiberatedHorse:
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
	case HeavenlyHorse:
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x + 1, y - 2);
		break;
	case SwoopingOwl:
		break;
	case CloudEagle:
		break;
	case StruttingCrow:
		break;
	case FlyingFalcon:
		break;
	case FlyingCock:
		break;
	case RaidingFalcon:
		break;
	case FlyingGoose:
	case ClimbingMonkey:
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
	case BlindDog:
		break;
	case RunningRabbit:
		break;
	case TreacherousFox:
		break;
	case TenaciousFalcon:
		break;
	default:
		ShogiBoard::GetMoves(piece, x, y);
		break;
	}
}

void WaShogiBoard::SetDrops(bool hasDrops)
{
	_hasDrops = hasDrops;
}
