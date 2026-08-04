#include "CylinderChessBoard.h"

CylinderChessBoard::CylinderChessBoard()
{
	_width = 8;
	_height = 8;
	CylinderChessBoard::Initialize();
}

CylinderChessBoard::~CylinderChessBoard()
{
}

Board* CylinderChessBoard::Clone()
{
	CylinderChessBoard* cb = new CylinderChessBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
			cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	cb->SetMoveCount(_moveCount);
	cb->SetHalfMoveCount(_halfMoveCount);
	cb->SetCastling(GetCastling());
	cb->SetEnPassant(_ep);
	return cb;
}

void CylinderChessBoard::Initialize()
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
				SetData(i, j, Piece(_initialSetup[j][i], j < 5 ? Black : White));
			}
			else
			{
				SetData(i, j, std::nullopt);
			}
		}
	}
}

// The a and h files are adjacent, so a file is only ever meaningful modulo the board width.
int CylinderChessBoard::Wrap(int x) const
{
	return ((x % _width) + _width) % _width;
}

void CylinderChessBoard::CheckWrappedMove(const std::optional<Piece>& piece, int x, int y)
{
	CheckMove(piece, Wrap(x), y);
}

void CylinderChessBoard::CheckWrappedDirection(const std::optional<Piece>& piece, int x, int y, Direction direction)
{
	const int fromX = x;
	const int fromY = y;
	while (true)
	{
		CheckDirectionInc(x, y, direction);
		if (y < 0 || y > _height - 1) break;    // ranks do not wrap, only files do
		x = Wrap(x);
		if (x == fromX && y == fromY) break;    // a full lap ends on the piece's own square
		if (!IsMovePossible(x, y))              // opposite directions meet on the far side of the cylinder
		{
			CheckMove(piece, x, y);
		}
		if (GetData(x, y) != std::nullopt) break;
	}
}

// En passant across the seam: a pawn on the a file can be captured by one on the h file and back.
bool CylinderChessBoard::EnemyPawnsAround(int x, int y) const
{
	const std::optional<Piece> fp = GetData(Wrap(x - 1), y);
	const std::optional<Piece> sp = GetData(Wrap(x + 1), y);
	const PieceColour pieceColour = y == 3 ? White : Black;
	const bool fpa = (fp != std::nullopt) && (fp->Type == Pawn) && (fp->Colour == pieceColour);
	const bool spa = (sp != std::nullopt) && (sp->Type == Pawn) && (sp->Colour == pieceColour);
	return fpa || spa;
}

void CylinderChessBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
	_moves.clear();
	switch (piece->Type)
	{
	case King:
		ChessBoard::GetMoves(piece, x, y);      // the ordinary king moves, and castling
		if (x == 0 || x == _width - 1)          // only the outer files gain neighbours across the seam
		{
			const int wx = x == 0 ? _width - 1 : 0;
			CheckMove(piece, wx, y + 1);
			CheckMove(piece, wx, y);
			CheckMove(piece, wx, y - 1);
		}
		break;
	case Queen:
		CheckWrappedDirection(piece, x, y, North);
		CheckWrappedDirection(piece, x, y, NorthEast);
		CheckWrappedDirection(piece, x, y, East);
		CheckWrappedDirection(piece, x, y, SouthEast);
		CheckWrappedDirection(piece, x, y, South);
		CheckWrappedDirection(piece, x, y, SouthWest);
		CheckWrappedDirection(piece, x, y, West);
		CheckWrappedDirection(piece, x, y, NorthWest);
		break;
	case Rook:
		CheckWrappedDirection(piece, x, y, North);
		CheckWrappedDirection(piece, x, y, East);
		CheckWrappedDirection(piece, x, y, South);
		CheckWrappedDirection(piece, x, y, West);
		break;
	case Bishop:
		CheckWrappedDirection(piece, x, y, NorthEast);
		CheckWrappedDirection(piece, x, y, SouthEast);
		CheckWrappedDirection(piece, x, y, SouthWest);
		CheckWrappedDirection(piece, x, y, NorthWest);
		break;
	case Knight:
		CheckWrappedMove(piece, x + 1, y + 2);
		CheckWrappedMove(piece, x - 1, y + 2);
		CheckWrappedMove(piece, x + 2, y + 1);
		CheckWrappedMove(piece, x + 2, y - 1);
		CheckWrappedMove(piece, x - 2, y + 1);
		CheckWrappedMove(piece, x - 2, y - 1);
		CheckWrappedMove(piece, x + 1, y - 2);
		CheckWrappedMove(piece, x - 1, y - 2);
		break;
	case Pawn:
		{
			const int dy = piece->Colour == Black ? 1 : -1;
			const int startY = piece->Colour == Black ? 1 : _height - 2;
			if (y == startY && GetData(x, y + dy) == std::nullopt && GetData(x, y + dy * 2) == std::nullopt)
			{
				CheckMove(piece, x, y + dy * 2);
			}
			if (y + dy >= 0 && y + dy <= _height - 1)
			{
				if (GetData(x, y + dy) == std::nullopt)
				{
					CheckMove(piece, x, y + dy);
				}
				// Captures cross the seam: a pawn on the a file takes on the h file
				for (const int cx : { Wrap(x - 1), Wrap(x + 1) })
				{
					if (GetData(cx, y + dy) != std::nullopt)
					{
						CheckMove(piece, cx, y + dy);
					}
				}
			}
			// En passant: the inherited check only asks for adjacent files, and across the seam they
			// are adjacent, so hand it a file that says so
			if (_ep != "-")
			{
				const int letter = _ep[0] - 97;
				const bool adjacent = Wrap(x - letter) == 1 || Wrap(letter - x) == 1;
				GetEnPassantMoves(piece.value(), adjacent ? letter + 1 : x, y);
			}
		}
		break;
	default:
		ChessBoard::GetMoves(piece, x, y);
		break;
	}
}
