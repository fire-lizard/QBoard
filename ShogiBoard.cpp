#include "ShogiBoard.h"

ShogiBoard::ShogiBoard()
{
	_hasDrops = true;
	_width = 9;
	_height = 9;
	ShogiBoard::Initialize();
}

ShogiBoard::~ShogiBoard()
{
}

void ShogiBoard::Initialize()
{
	_moveCount = 0;
	_psn = "";
	_csa = "";
	_kif = "";
	_capturedPieces.clear();
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

Board* ShogiBoard::Clone()
{
	ShogiBoard *cb = new ShogiBoard();
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

Piece* ShogiBoard::CreatePiece(PieceType pieceType, PieceColour pieceColour)
{
	return new ShogiPiece(pieceType, pieceColour);
}

void ShogiBoard::GetMoves(Piece *piece, int x, int y)
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
		CheckDirection(piece, x, y, North);
		CheckDirection(piece, x, y, NorthEast);
		CheckDirection(piece, x, y, East);
		CheckDirection(piece, x, y, SouthEast);
		CheckDirection(piece, x, y, South);
		CheckDirection(piece, x, y, SouthWest);
		CheckDirection(piece, x, y, West);
		CheckDirection(piece, x, y, NorthWest);
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
	case Lance:
		if (piece->GetColour() == Black)
		{
			CheckDirection(piece, x, y, North);
		}
		else
		{
			CheckDirection(piece, x, y, South);
		}
		break;
	case Gold:
	case Tokin:
	case PromotedLance:
	case PromotedKnight:
	case PromotedSilver:
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
	case Knight:
		if (piece->GetColour() == Black)
		{
			CheckMove(piece, x - 1, y + 2);
			CheckMove(piece, x + 1, y + 2);
		}
		else
		{
			CheckMove(piece, x - 1, y - 2);
			CheckMove(piece, x + 1, y - 2);
		}
		break;
	case Elephant:
		CheckMove(piece, x + 1, y + 1);
		CheckMove(piece, x + 1, y);
		CheckMove(piece, x + 1, y - 1);
		CheckMove(piece, x - 1, y + 1);
		CheckMove(piece, x - 1, y);
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
		break;
	}
}

void ShogiBoard::SetDrops(bool hasDrops)
{
	_hasDrops = hasDrops;
	if (_hasDrops)
	{
		_initialSetup[1][4] = None;
		_initialSetup[7][4] = None;
	}
	else
	{
		_initialSetup[1][4] = Elephant;
		_initialSetup[7][4] = Elephant;
	}
}

void ShogiBoard::WriteMove(PieceType pieceType, int x1, int y1, int x2, int y2, char promotion, bool capture)
{
	// PSN
	_moveCount++;
	_psn += std::to_string(_moveCount) + ".";
	if (y1 == '*')
	{
		_psn.push_back(static_cast<char>(x1));
		_psn.push_back(static_cast<char>(y1));
		_psn += std::to_string(_width - x2);
		_psn.push_back(static_cast<char>(y2 + 97));
	}
	else
	{
		_psn += _pieceToPSN.at(pieceType);
		_psn += std::to_string(_width - x1);
		_psn.push_back(static_cast<char>(y1 + 97));
		_psn += capture ? "x" : "-";
		_psn += std::to_string(_width - x2);
		_psn.push_back(static_cast<char>(y2 + 97));
		_psn += promotion;
	}
	_psn += "          (00:00 / 00:00:00)\n";
	// CSA
	_csa += (_moveCount + 1) % 2 == 0 ? "+" : "-";
	_csa += y1 == '*' ? "00" : std::to_string(_width - x1) + std::to_string(y1 + 1);
	_csa += std::to_string(_width - x2);
	_csa += std::to_string(y2 + 1);
	_csa += _pieceToCSA.at(promotion != '+' ? pieceType : _data[x2][y2]->GetType());
	_csa += ",T1\n";
	// KIF
	_kif += "  " + std::to_string(_moveCount) + " "; // Add move number
	_kif += x2 == _oldX2 && y2 == _oldY2 ? _sameCoordStr : std::to_string(_width - x2);
	_kif += x2 == _oldX2 && y2 == _oldY2 ? " " : _numberToKanji.at(y2 + 1);
	_kif += _pieceToKIF.at(pieceType);
	if (promotion == '+')
	{
		_kif += _promotionStr;
	}
	_kif += y1 == '*' ? _dropStr : "(" + std::to_string(_width - x1) + std::to_string(y1 + 1) + ")";
	_kif += "          (00:00 / 00:00:00)\n";
	_oldX2 = y1 != '*' ? x2 : _oldX2;
	_oldY2 = y1 != '*' ? y2 : _oldX2;
}

std::string ShogiBoard::GetPSN()
{
	return _psn;
}

std::string ShogiBoard::GetCSA()
{
	return _csa;
}

std::string ShogiBoard::GetKIF()
{
	return _kif;
}
