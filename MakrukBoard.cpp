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
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
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
                SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

void MakrukBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
    switch (piece->Type)
	{
	case Silver:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
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

void MakrukBoard::WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2, char promotion, bool capture)
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

std::string MakrukBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    switch (pieceType)
    {
    case Queen:
        return "M";
    case Silver:
        return "S";
    default:
        return ShatranjBoard::GetStringCode(x, y);
    }
}
