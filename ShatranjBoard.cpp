#include "ShatranjBoard.h"

ShatranjBoard::ShatranjBoard()
{
	_width = 8;
	_height = 8;
	ShatranjBoard::Initialize();
}

ShatranjBoard::~ShatranjBoard()
{
}

Board* ShatranjBoard::Clone()
{
	ShatranjBoard* cb = new ShatranjBoard();
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

void ShatranjBoard::Initialize()
{
	_moveCount = 0;
	_pgn = "";
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new ShatranjPiece(_initialSetup[j][i], j < 5 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Piece* ShatranjBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new ShatranjPiece(pieceType, pieceColour);
}

void ShatranjBoard::GetMoves(Piece* piece, int x, int y)
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
	case Queen:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
		break;
	case Rook:
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, South);
		break;
	case Bishop:
		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y - 2);
		break;
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
	case Knight:
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x - 1, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 1, y - 2);
		break;
	default:
		break;
	}
}

void ShatranjBoard::WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2, char promotion, bool capture)
{
	if (_moveCount % 2 == 0)
	{
		_pgn += std::to_string((_moveCount / 2) + 1) + ". "; // Add move number for white
	}
	if (pieceType != Pawn)
	{
		_pgn += _pieceToPGN.at(pieceType);
	}
	_pgn.push_back(static_cast<char>(x1 + 97));
	_pgn += std::to_string(_height - y1);
	if (capture)
	{
		_pgn += "x";
	}
	_pgn.push_back(static_cast<char>(x2 + 97));
	_pgn += std::to_string(y2);
	if (promotion != ' ')
	{
		_pgn += "=";
		_pgn += static_cast<char>(std::toupper(promotion));
	}
	_pgn += " ";
	_moveCount++;
}

std::string ShatranjBoard::GetPGN()
{
	return _pgn;
}