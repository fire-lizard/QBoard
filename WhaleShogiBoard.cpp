#include "WhaleShogiBoard.h"

WhaleShogiBoard::WhaleShogiBoard()
{
    _width = 6;
    _height = 6;
    WhaleShogiBoard::Initialize();
}

WhaleShogiBoard::~WhaleShogiBoard()
{
}

void WhaleShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, Piece(_initialSetup[j][i], j < 3 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
            }
        }
    }
}

Board* WhaleShogiBoard::Clone()
{
    WhaleShogiBoard* cb = new WhaleShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const std::optional<Piece> p = GetData(i, j);
            cb->SetData(i, j, p != std::nullopt ? cb->CreatePiece(p->Type, p->Colour) : std::nullopt);
        }
    }
    for (const auto& capturedPiece : _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void WhaleShogiBoard::Promote(std::optional<Piece>& piece, PieceType pt)
{
}

void WhaleShogiBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
    {
    case GreyWhale:
        if (piece->Colour == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckDirection(piece, x, y, SouthEast);
            CheckDirection(piece, x, y, SouthWest);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckDirection(piece, x, y, NorthEast);
            CheckDirection(piece, x, y, NorthWest);
        }
        break;
    case Porpoise:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        break;
    case Narwhal:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->Colour == Black)
        {
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x, y + 2);
        }
        else
        {
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x, y - 2);
        }
        break;
    case Humpback:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        if (piece->Colour == Black)
        {
            CheckMove(piece, x, y - 1);
        }
        else
        {
            CheckMove(piece, x, y + 1);
        }
        break;
    case BlueWhale:
        CheckMove(piece, x, y + 1);
        CheckMove(piece, x, y - 1);
        if (piece->Colour == Black)
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
    case Pawn:
        if (piece->Colour == Black)
        {
            CheckMove(piece, x, y + 1);
            if (y == _height - 1)
            {
                CheckDirection(piece, x, y, SouthEast);
                CheckDirection(piece, x, y, SouthWest);
            }
        }
        else
        {
            CheckMove(piece, x, y - 1);
            if (y == 0)
            {
                CheckDirection(piece, x, y, NorthEast);
                CheckDirection(piece, x, y, NorthWest);
            }
        }
        break;
    default:
        ShogiBoard::GetMoves(piece, x, y);
        break;
    }
}

std::string WhaleShogiBoard::GetStringCode(int x, int y) const
{
    if (GetData(x, y) == std::nullopt) return "";
    PieceType pieceType = GetData(x, y)->Type;
    switch (pieceType)
    {
    case King:
        return "W";
    case GreyWhale:
        return "G";
    case Porpoise:
        return "P";
    case DragonKing:
        return "K";
    case Narwhal:
        return "N";
    case Humpback:
        return "H";
    case BlueWhale:
        return "B";
    case Pawn:
        return "D";
    default:
        return "";
    }
}

std::string WhaleShogiBoard::formatEnumCounts(const std::vector<PieceType>& enumList)
{
    static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
        {GreyWhale, "G"},
        {DragonKing, "K"},
        {Narwhal, "N"},
        {Humpback, "H"},
        {BlueWhale, "B"},
        {Pawn, "D"}
    };

    // Define the required order of pieces
    const std::vector<PieceType> order = { GreyWhale, DragonKing, Narwhal, Humpback, BlueWhale, Pawn };

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
