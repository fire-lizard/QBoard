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
	_halfMoveCount = 0;
	_pgn = "";
	_wkc = true;
	_wqc = true;
	_bkc = true;
	_bqc = true;
	_ep = "-";
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

std::string ChessBoard::GetCastling()
{
	std::string str;
	if (_wkc) str += "K";
	if (_wqc) str += "Q";
	if (_bkc) str += "k";
	if (_bqc) str += "q";
	if (str == "") str += "-";
	return str;
}

std::string ChessBoard::GetEnPassant()
{
	return _ep;
}

void ChessBoard::SetCastling(std::string val)
{
	_wkc = false;
	_wqc = false;
	_bkc = false;
	_bqc = false;
	for (size_t index = 0; index < val.size(); index++)
	{
		if (val[index] == 'K') _wkc = true;
		if (val[index] == 'Q') _wqc = true;
		if (val[index] == 'k') _bkc = true;
		if (val[index] == 'q') _bqc = true;
	}
}

void ChessBoard::SetEnPassant(std::string val)
{
	_ep = val;
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
			// En passant
			if (_ep != "-")
			{
				int letter = _ep[0] - 97;
				int number = _ep[1] - 48;
				if (abs(x - letter) == 1 && y == number + 1)
				{
					CheckMove(piece, letter, number + 2);
				}
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
			// En passant
			if (_ep != "-")
			{
				int letter = _ep[0] - 97;
				int number = _ep[1] - 48;
				if (abs(x - letter) == 1 && y == number)
				{
					CheckMove(piece, letter, number - 1);
				}
			}
		}
		break;
	default:
		ShatranjBoard::GetMoves(piece, x, y);
		break;
	}
}

bool ChessBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	PieceType pieceType = _data[oldX][oldY]->GetType();
	PieceColour pieceColour = _data[oldX][oldY]->GetColour();
	PieceType destPieceType = _data[newX][newY] != nullptr ? _data[newX][newY]->GetType() : None;
	const bool result = Board::Move(oldX, oldY, newX, newY, cl);
	if (result)
	{
		dynamic_cast<ChessPiece*>(_data[newX][newY])->Move();
		// Castling
		if (pieceType == Rook)
		{
			if (oldX == 0 && oldY == _height - 1)
			{
				_wqc = false;
			}
			else if (oldX == _width - 1 && oldY == _height - 1)
			{
				_wkc = false;
			}
			else if (oldX == 0 && oldY == 0)
			{
				_bqc = false;
			}
			else if (oldX == _width - 1 && oldY == 0)
			{
				_bkc = false;
			}
		}
		else if (pieceType == King)
		{
			if (pieceColour == White)
			{
				_wqc = false;
				_wkc = false;
			}
			else
			{
				_bqc = false;
				_bkc = false;
			}
		}
		if (destPieceType == Rook)
		{
			if (newX == 0 && newY == _height - 1)
			{
				_wqc = false;
			}
			else if (newX == _width - 1 && newY == _height - 1)
			{
				_wkc = false;
			}
			else if (newX == 0 && newY == 0)
			{
				_bqc = false;
			}
			else if (newX == _width - 1 && newY == 0)
			{
				_bkc = false;
			}
		}
		// En passant
		if (pieceType == Pawn && abs(oldY - newY) == 2)
		{
			_ep = "";
			char letter = newX + 97;
			_ep.push_back(letter);
			_ep.append(oldY == 5 ? "6" : "3");
		}
		else if (pieceType == Pawn && _ep != "-")
		{
			char letter = newX + 97;
			int number = _ep[1] - 48;
			if (letter == _ep[0] &&	((pieceColour == White && newY == number - 1) || (pieceColour == Black && newY == number + 2)))
			{
				Piece* p = pieceColour == White ? _data[newX][number] : _data[newX][number + 1];
				if (p != nullptr && p->GetType() == Pawn && p->GetColour() != pieceColour)
				{
					delete p;
					if (pieceColour == White)
					{
						_data[newX][number] = nullptr;
					}
					else
					{
						_data[newX][number + 1] = nullptr;
					}
				}
			}
			_ep = "-";
		}
		else
		{
			_ep = "-";
		}
		if (pieceType == Pawn || destPieceType != None)
		{
			_halfMoveCount = 0;
		}
		else
		{
			_halfMoveCount++;
		}
	}
	return result;
}

int ChessBoard::HalfMoveCount()
{
	return _halfMoveCount;
}

void ChessBoard::WriteMove(const std::string& moveStr)
{
	if (moveStr == "O-O")
	{
		if (_moveCount % 2 == 0)
		{
			_wkc = false;
		}
		else
		{
			_bkc = false;
		}
	}
	else if (moveStr == "O-O-O")
	{
		if (_moveCount % 2 == 0)
		{
			_wqc = false;
		}
		else
		{
			_bqc = false;
		}
	}
	if (_moveCount % 2 == 0)
	{
		 _pgn += std::to_string((_moveCount / 2) + 1) + ". "; // Add move number for white
	}
	_pgn += moveStr;
	_pgn += " ";
	_moveCount++;
}
