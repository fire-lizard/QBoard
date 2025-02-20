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

void KoShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Pawn:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
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
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
