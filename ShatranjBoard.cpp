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
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
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
                SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

void ShatranjBoard::Promote(int x, int y, PieceType pt)
{
    if (_data[x][y] != std::nullopt)
    {
		_data[x][y]->IsPromoted = true;
		_data[x][y]->Type = Queen;
    }
}
void ShatranjBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
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
        if (piece->Colour == Black)
		{
			if (y + 1 < _height && GetData(x, y + 1) == std::nullopt)
			{
				CheckMove(piece, x, y + 1);
			}
			if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != std::nullopt)
			{
				CheckMove(piece, x + 1, y + 1);
			}
			if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != std::nullopt)
			{
				CheckMove(piece, x - 1, y + 1);
			}
		}
		else
		{
			if (y - 1 >= 0 && GetData(x, y - 1) == std::nullopt)
			{
				CheckMove(piece, x, y - 1);
			}
			if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != std::nullopt)
			{
				CheckMove(piece, x + 1, y - 1);
			}
			if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != std::nullopt)
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

std::string ShatranjBoard::GetStringCode(int x, int y) const
{
	if (GetData(x, y) == std::nullopt) return "";
	PieceType pieceType = GetData(x, y)->Type;
	switch (pieceType)
	{
	case Knight:
		return "N";
	default:
		return Board::GetStringCode(x, y);
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
