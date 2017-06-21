#include "TrueChessBoard.h"

TrueChessBoard::TrueChessBoard() : ChessBoard()
{
}

TrueChessBoard::~TrueChessBoard()
{
}

void TrueChessBoard::GetMoves(Piece *piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case Pawn:
		if (piece->GetColour() == Black)
		{
			if (y + 1 < _height && _data[x][y + 1] == nullptr)
			{
				CheckMove(piece, x, y + 1);
			}
			if (y + 1 < _height && x + 1 < _width && _data[x + 1][y + 1] != nullptr)
			{
				CheckMove(piece, x + 1, y + 1);
			}
			if (y + 1 < _height && x - 1 >= 0 && _data[x - 1][y + 1] != nullptr)
			{
				CheckMove(piece, x - 1, y + 1);
			}
		}
		else
		{
			if (y - 1 >= 0 && _data[x][y - 1] == nullptr)
			{
				CheckMove(piece, x, y - 1);
			}
			if (y - 1 >= 0 && x + 1 < _width && _data[x + 1][y - 1] != nullptr)
			{
				CheckMove(piece, x + 1, y - 1);
			}
			if (y - 1 >= 0 && x - 1 >= 0 && _data[x - 1][y - 1] != nullptr)
			{
				CheckMove(piece, x - 1, y - 1);
			}
		}
		break;
	default:
		ChessBoard::GetMoves(piece, x, y);
		break;
	}
}
