#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	_width = 8;
	_height = 8;
	ChessBoard::Initialize();
}

ChessBoard::~ChessBoard()
{
}

Board* ChessBoard::Clone()
{
	ChessBoard *cb = new ChessBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const Piece *p = GetData(i, j);
			cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
		}
	}
	return cb;
}

void ChessBoard::Initialize()
{
	_moveCount = 0;
	_pgn = "";
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new ChessPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Piece* ChessBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new ChessPiece(pieceType, pieceColour);
}

void ChessBoard::GetMoves(Piece *piece, int x, int y)
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
		// Check castling
		if (!dynamic_cast<ChessPiece*>(piece)->HasMoved())
		{
			if (_data[0][y] != nullptr)
			{
				const ChessPiece* cp = dynamic_cast<ChessPiece*>(_data[0][y]);
				if (!cp->HasMoved() && cp->GetType() == Rook && _data[1][y] == nullptr && _data[2][y] == nullptr && _data[3][y] == nullptr)
				{
					_moves.emplace_back(0, y);
				}
			}
			if (_data[7][y] != nullptr)
			{
				const ChessPiece* cp = dynamic_cast<ChessPiece*>(_data[7][y]);
				if (!cp->HasMoved() && cp->GetType() == Rook && _data[5][y] == nullptr && _data[6][y] == nullptr)
				{
					_moves.emplace_back(7, y);
				}
			}
		}
		break;
	case Queen:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Bishop:
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, NorthWest);
		break;
	case Pawn:
		if (piece->GetColour() == Black)
		{
			if (y == 1 && _data[x][y + 1] == nullptr && _data[x][y + 2] == nullptr)
			{
				CheckMove(piece, x, y + 2);
			}
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
			if (y == 6 && _data[x][y - 1] == nullptr && _data[x][y - 2] == nullptr)
			{
				CheckMove(piece, x, y - 2);
			}
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
		ShatranjBoard::GetMoves(piece, x, y);
		break;
	}
}

bool ChessBoard::Move(int oldX, int oldY, int newX, int newY)
{
	const bool result = Board::Move(oldX, oldY, newX, newY);
	if (result)
	{
		dynamic_cast<ChessPiece*>(_data[newX][newY])->Move();
	}
	return result;
}

void ChessBoard::WriteMove(const std::string& moveStr)
{
	if (_moveCount % 2 == 0)
	{
		 _pgn += std::to_string((_moveCount / 2) + 1) + ". "; // Add move number for white
	}
	_pgn += moveStr;
	_pgn += " ";
	_moveCount++;
}
