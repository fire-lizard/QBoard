#include "MakrukBoard.h"

MakrukBoard::MakrukBoard()
{
	_width = 8;
	_height = 8;
	MakrukBoard::Initialize();
}

MakrukBoard::~MakrukBoard()
{
}

Board* MakrukBoard::Clone()
{
	MakrukBoard* cb = new MakrukBoard();
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

void MakrukBoard::Initialize()
{
	_moveCount = 0;
	_pgn = "";
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new MakrukPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Piece* MakrukBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new MakrukPiece(pieceType, pieceColour);
}

void MakrukBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
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
	default:
		ShatranjBoard::GetMoves(piece, x, y);
		break;
	}
}
