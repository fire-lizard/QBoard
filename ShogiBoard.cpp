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
	_ki2 = "";
	_capturedPieces.clear();
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

Board* ShogiBoard::Clone()
{
	ShogiBoard *cb = new ShogiBoard();
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
		}
	}
	for (const auto& capturedPiece: _capturedPieces)
	{
		cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
	}
	cb->SetMoveCount(_moveCount);
	return cb;
}

void ShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (GetData(x, y) != std::nullopt)
    {
		_data[x][y]->IsPromoted = true;
        PieceType pieceType = None;
        switch (_data[x][y]->Type)
        {
        case Rook:
            pieceType = DragonKing;
            break;
        case Bishop:
            pieceType = DragonHorse;
            break;
        case Elephant:
            pieceType = Prince;
            break;
        case Lance:
            pieceType = PromotedLance;
            break;
        case Silver:
            pieceType = PromotedSilver;
            break;
        case Knight:
            pieceType = PromotedKnight;
            break;
        case Pawn:
            pieceType = Tokin;
            break;
        default:
            break;
        }
        if (pieceType != None)
        {
			_data[x][y]->Type = pieceType;
        }
    }
}

bool ShogiBoard::Move(int oldX, int oldY, int newX, int newY, bool cl)
{
	if (GetData(oldX, oldY) != std::nullopt)
	{
		PieceColour pieceColour = GetData(oldX, oldY)->Colour;
		PieceType pt = GetData(newX, newY) != std::nullopt && GetData(newX, newY)->Colour != GetData(oldX, oldY)->Colour ? GetData(newX, newY)->BaseType : None;
		const bool result = ChuShogiBoard::Move(oldX, oldY, newX, newY, cl);
		if (result && pt != None && pt != Porpoise)
		{
			_capturedPieces.emplace_back(pieceColour, pt);
		}
		else if (result && pt == Porpoise)
		{
			_capturedPieces.emplace_back(pieceColour, DragonKing);
		}
		return result;
	}
	return false;
}

std::string ShogiBoard::GetStringCode(int x, int y) const
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
	if (y1 == '*' || y1 == '@')
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
	_csa += y1 == '*' ? "00" : std::to_string(_width - x1) + std::to_string(y1);
	_csa += std::to_string(_width - x2);
	_csa += std::to_string(y2);
    _csa += _pieceToCSA.at(promotion != '+' || GetData(x2, y2) == std::nullopt ? pieceType : GetData(x2, y2)->Type);
	_csa += ",T1\n";
	// KIF
	_kif += "  " + std::to_string(_moveCount) + " "; // Add move number
    if (x2 == _oldX2 && y2 == _oldY2)
    {
        _kif += _sameCoordStr;
        _kif += " ";
    }
    else
    {
        _kif += std::to_string(_width - x2);
        _kif += _numberToKanji.at(y2);
    }
	_kif += _pieceToKIF.at(pieceType);
	if (promotion == '+')
	{
		_kif += _promotionStr;
	}
	_kif += y1 == '*' ? _dropStr : "(" + std::to_string(_width - x1) + std::to_string(y1) + ")";
	_kif += "          (00:00 / 00:00:00)\n";
	// KI2
	_ki2 += (_moveCount + 1) % 2 == 0 ? _senteStr : _goteStr;
	_ki2 += y1 == '*' ? _dropStr : std::to_string(_width - x1);
	_ki2 += x2 == _oldX2 && y2 == _oldY2 ? _sameCoordStr : "";
    _ki2 += x2 == _oldX2 && y2 == _oldY2 ? " " : _numberToKanji.at(y2);
	_ki2 += _pieceToKIF.at(pieceType);
	if (promotion == '+')
	{
		_ki2 += _promotionStr;
	}
	_ki2 += promotion == '+' ? "   " : "    ";
	_ki2 += _moveCount % 6 == 0 ? "\n" : "";
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

std::string ShogiBoard::GetKI2()
{
	return _ki2;
}
