#include "ToriShogiBoard.h"

ToriShogiBoard::ToriShogiBoard()
{
    _width = 7;
    _height = 7;
    ToriShogiBoard::Initialize();
}

ToriShogiBoard::~ToriShogiBoard()
{
}

void ToriShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                if (j != 3)
                    SetData(i, j, Piece(_initialSetup[j][i], j < 3 ? Black : White));
                else
                    SetData(i, j, Piece(_initialSetup[j][i], i < 3 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
            }
        }
    }
}

Board* ToriShogiBoard::Clone()
{
    ToriShogiBoard* cb = new ToriShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
        }
    }
    for (const auto& capturedPiece : _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void ToriShogiBoard::Promote(int x, int y, PieceType pt)
{
    if (_data[x][y] != std::nullopt)
    {
        _data[x][y]->IsPromoted = true;
        switch (_data[x][y]->Type)
        {
        case Falcon:
            _data[x][y]->Type = Eagle;
            break;
        case Pawn:
            _data[x][y]->Type = Goose;
            break;
        default:
            break;
        }
    }
}

void ToriShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
    {
    case Falcon:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y);
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
    case Crane:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        break;
    case Pheasant:
        if (piece->Colour == Black)
        {
            CheckMove(piece, x, y + 2);
            CheckMove(piece, x + 1, y - 1);
            CheckMove(piece, x - 1, y - 1);
        }
        else
        {
            CheckMove(piece, x, y - 2);
            CheckMove(piece, x + 1, y + 1);
            CheckMove(piece, x - 1, y + 1);
        }
        break;
    case LeftQuail:
        if (piece->Colour == White)
        {
            CheckDirection(piece, x, y, South);
            CheckDirection(piece, x, y, NorthEast);
            CheckMove(piece, x - 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, North);
            CheckDirection(piece, x, y, SouthEast);
            CheckMove(piece, x - 1, y - 1);
        }
        break;
    case RightQuail:
        if (piece->Colour == White)
        {
            CheckDirection(piece, x, y, South);
            CheckDirection(piece, x, y, NorthWest);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, North);
            CheckDirection(piece, x, y, SouthWest);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case Eagle:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->Colour == White)
        {
            CheckDirection(piece, x, y, SouthWest);
            CheckDirection(piece, x, y, SouthEast);
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x + 1, y + 1);
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 2, y + 2);
            CheckMove(piece, x - 2, y + 2);
        }
        else
        {
            CheckDirection(piece, x, y, NorthWest);
            CheckDirection(piece, x, y, NorthEast);
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x + 1, y - 1);
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 2, y - 2);
            CheckMove(piece, x - 2, y - 2);
        }
        break;
    case Goose:
        if (piece->Colour == Black)
        {
            CheckMove(piece, x, y - 2);
            CheckMove(piece, x + 2, y + 2);
            CheckMove(piece, x - 2, y + 2);
        }
        else
        {
            CheckMove(piece, x, y + 2);
            CheckMove(piece, x + 2, y - 2);
            CheckMove(piece, x - 2, y - 2);
        }
        break;
    default:
        ShogiBoard::GetMoves(piece, x, y);
        break;
    }
}

std::string ToriShogiBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    switch (pieceType)
    {
    case King:
        return "K";
    case Falcon:
        return "F";
    case Eagle:
        return "+F";
    case Crane:
        return "C";
    case Pheasant:
        return "P";
    case LeftQuail:
        return "L";
    case RightQuail:
        return "R";
    case Pawn:
        return "S";
    case Goose:
        return "+S";
    default:
        return "";
    }
}

std::string ToriShogiBoard::formatEnumCounts(const std::vector<PieceType>& enumList)
{
    static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
        {Falcon, "F"},
        {Crane, "C"},
        {Pheasant, "P"},
        {LeftQuail, "L"},
        {RightQuail, "R"},
        {Pawn, "S"}
    };

    // Define the required order of pieces
    const std::vector<PieceType> order = { Falcon, Crane, Pheasant, LeftQuail, RightQuail, Pawn };

    // Count occurrences of each piece
    std::unordered_map<PieceType, int> counts;
    for (const auto& piece : enumList)
    {
        counts[piece]++;
    }

    std::ostringstream result;

    // Construct the output string based on the order
    for (const auto& piece : order) {
        const auto it = pieceTypeToCode.find(piece);
        if (it != pieceTypeToCode.end())
        {
            if (counts[piece] > 1) {
                result << counts[piece] << it->second; // Add count + first letter
            }
            else if (counts[piece] == 1) {
                result << it->second; // Add just the first letter
            }
        }
    }

    return result.str();
}
