#include "MiniShogiBoard.h"

MiniShogiBoard::MiniShogiBoard()
{
	_width = 5;
	_height = 5;
	MiniShogiBoard::Initialize();
}

MiniShogiBoard::~MiniShogiBoard()
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

void MiniShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new ShogiPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* MiniShogiBoard::Clone()
{
	MiniShogiBoard *cb = new MiniShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			Piece *p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

Piece* MiniShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted)
{
	return new ShogiPiece(pieceType, pieceColour, isPromoted);
}

void MiniShogiBoard::GetMoves(Piece *piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case King:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);
		break;
	case DragonKing:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case DragonHorse:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Rook:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case Bishop:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Gold:
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y);
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
	case Silver:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	case Pawn:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckMove(piece, x, y - 1);
		}
		break;
	default:
		break;
	}
}