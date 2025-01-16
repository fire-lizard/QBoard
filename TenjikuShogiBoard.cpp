#include "TenjikuShogiBoard.h"

TenjikuShogiBoard::TenjikuShogiBoard()
{
	_width = 16;
	_height = 16;
	TenjikuShogiBoard::Initialize();
}

TenjikuShogiBoard::~TenjikuShogiBoard()
{
}

void TenjikuShogiBoard::Initialize()
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			if (_initialSetup[j][i] != None)
			{
				_data[i][j] = new TenjikuShogiPiece(_initialSetup[j][i], j < 7 ? Black : White);
			}
			else
			{
				_data[i][j] = nullptr;
			}
		}
	}
}

Board* TenjikuShogiBoard::Clone()
{
	TenjikuShogiBoard* cb = new TenjikuShogiBoard();
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

Piece* TenjikuShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new TenjikuShogiPiece(pieceType, pieceColour);
}

void TenjikuShogiBoard::CheckJump(const Piece* piece, int x, int y, Direction direction)
{
	while (CheckDirectionAux(x, y, direction))
	{
		CheckDirectionInc(x, y, direction);
		CheckMove(piece, x, y);
		if (_data[x][y] != nullptr)
		{
			PieceType pieceType = _data[x][y]->GetType();
			if (pieceType == King)
			{
				break;
			}
			else if (piece->GetType() == pieceType || pieceType == GreatGeneral)
			{
				break;
			}
			else if (std::find(std::begin(_jumpingPieces), std::end(_jumpingPieces), pieceType) != std::end(_jumpingPieces))
			{
				break;
			}
		}
	}
}

void TenjikuShogiBoard::GetMoves(Piece* piece, int x, int y)
{
	_moves.clear();
	switch (piece->GetType())
	{
	case GreatGeneral:
		CheckJump(piece, x, y, SouthWest);
		CheckJump(piece, x, y, SouthEast);
		CheckJump(piece, x, y, NorthWest);
		CheckJump(piece, x, y, NorthEast);
		CheckJump(piece, x, y, West);
		CheckJump(piece, x, y, East);
		CheckJump(piece, x, y, North);
		CheckJump(piece, x, y, South);
		break;
	case BishopGeneral:
		CheckJump(piece, x, y, SouthWest);
		CheckJump(piece, x, y, SouthEast);
		CheckJump(piece, x, y, NorthWest);
		CheckJump(piece, x, y, NorthEast);
		break;
	case RookGeneral:
		CheckJump(piece, x, y, West);
		CheckJump(piece, x, y, East);
		CheckJump(piece, x, y, North);
		CheckJump(piece, x, y, South);
		break;
	case MultiGeneral:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckDirection(piece, x, y, SouthWest);
			CheckDirection(piece, x, y, SouthEast);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckDirection(piece, x, y, NorthWest);
			CheckDirection(piece, x, y, NorthEast);
		}
		break;
	case Dog:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 1);
			CheckMove(piece, x - 1, y + 1);
			CheckMove(piece, x + 1, y + 1);
		}
		else
		{
			CheckMove(piece, x, y + 1);
			CheckMove(piece, x - 1, y - 1);
			CheckMove(piece, x + 1, y - 1);
		}
		break;
	case SideSoldier:
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y + 1);
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x, y - 2);
		}
		else
		{
			CheckMove(piece, x, y + 2);
		}
		break;
	case VerticalSoldier:
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y + 1);
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
			CheckMove(piece, x, y + 1);
		}
		else
		{
			CheckDirection(piece, x, y, South);
			CheckMove(piece, x, y - 1);
		}
		break;
	case ChariotSoldier:
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, North);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 2, y);
		break;
	case WaterBuffalo:
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, East);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x, y - 2);
		break;
	case LionHawk:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x, y + 1);
		CheckMove(piece, x, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
		CheckMove(piece, x - 1, y - 1);

		CheckMove(piece, x + 2, y + 2);
		CheckMove(piece, x + 2, y + 1);
		CheckMove(piece, x + 2, y);
		CheckMove(piece, x + 2, y - 1);
		CheckMove(piece, x + 2, y - 2);
		CheckMove(piece, x + 1, y + 2);
		CheckMove(piece, x, y + 2);
		CheckMove(piece, x - 1, y + 2);

		CheckMove(piece, x - 1, y - 2);
		CheckMove(piece, x, y - 2);
		CheckMove(piece, x + 1, y - 2);
		CheckMove(piece, x - 2, y + 2);
		CheckMove(piece, x - 2, y + 1);
		CheckMove(piece, x - 2, y);
		CheckMove(piece, x - 2, y - 1);
		CheckMove(piece, x - 2, y - 2);

		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, NorthWest);
		CheckDirection(piece, x, y, NorthEast);
		break;
	/*case ViceGeneral:
		return "ViceGeneral" + colour + ".png";
	case FreeEagle:
		return "FreeEagle" + colour + ".png";
	case HeavenlyTetrarch:
		return "Heaven" + colour + ".png";
	case FireDemon:
		return "FireDemon" + colour + ".png";*/
	default:
		DaiShogiBoard::GetMoves(piece, x, y);
		break;
	}
}
