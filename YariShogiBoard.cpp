#include "YariShogiBoard.h"

YariShogiBoard::YariShogiBoard()
{
    _width = 7;
    _height = 9;
    YariShogiBoard::Initialize();
}

YariShogiBoard::~YariShogiBoard()
{
}

void YariShogiBoard::Initialize()
{
    _moveCount = 0;
    _capturedPieces.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, new ShogiPiece(_initialSetup[j][i], j < 5 ? Black : White));
            }
            else
            {
                SetData(i, j, nullptr);
            }
        }
    }
}

Board* YariShogiBoard::Clone()
{
    YariShogiBoard *cb = new YariShogiBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const Piece *p = GetData(i, j);
            cb->SetData(i, j, p != nullptr ? cb->CreatePiece(p->GetType(), p->GetColour()) : nullptr);
        }
    }
    for (const auto& capturedPiece: _capturedPieces)
    {
        cb->AddCapturedPiece(capturedPiece.second, capturedPiece.first);
    }
    cb->SetMoveCount(_moveCount);
    return cb;
}

void YariShogiBoard::Promote(int x, int y, PieceType pt)
{
    Promote(GetData(x, y), pt);
}

void YariShogiBoard::Promote(Piece *piece, PieceType pt)
{
    if (piece != nullptr)
    {
        piece->IsPromoted = true;
        PieceType pieceType = None;
        switch (piece->GetType())
        {
        case YariKnight:
            pieceType = YariGold;
            break;
        case YariRook:
            pieceType = Rook;
            break;
        case YariBishop:
            pieceType = YariGold;
            break;
        case Pawn:
            pieceType = YariSilver;
            break;
        default:
            break;
        }
        if (pieceType != None)
        {
            piece->SetType(pieceType);
        }
    }
}

void YariShogiBoard::GetMoves(Piece *piece, int x, int y)
{
    _moves.clear();
    switch (piece->GetType())
    {
    case YariRook:
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, West);
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
        }
        else
        {
            CheckDirection(piece, x, y, South);
        }
        break;
    case YariGold:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case YariSilver:
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckMove(piece, x, y + 1);
            CheckMove(piece, x - 1, y + 1);
            CheckMove(piece, x + 1, y + 1);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckMove(piece, x, y - 1);
            CheckMove(piece, x - 1, y - 1);
            CheckMove(piece, x + 1, y - 1);
        }
        break;
    case YariBishop:
        CheckMove(piece, x + 1, y);
        CheckMove(piece, x - 1, y);
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
        }
        else
        {
            CheckDirection(piece, x, y, South);
        }
        break;
    case YariKnight:
        if (piece->GetColour() == Black)
        {
            CheckDirection(piece, x, y, North);
            CheckMove(piece, x - 1, y + 2);
            CheckMove(piece, x + 1, y + 2);
        }
        else
        {
            CheckDirection(piece, x, y, South);
            CheckMove(piece, x - 1, y - 2);
            CheckMove(piece, x + 1, y - 2);
        }
        break;
    default:
        ShogiBoard::GetMoves(piece, x, y);
        break;
    }
}

std::string YariShogiBoard::formatEnumCounts(const std::vector<PieceType>& enumList)
{
    static const std::unordered_map<PieceType, std::string> pieceTypeToCode = {
        {YariKnight, "R"},
        {YariRook, "B"},
        {YariBishop, "L"},
        {Pawn, "P"}
    };

    // Define the required order of pieces
    const std::vector<PieceType> order = { YariKnight, YariRook, YariBishop, Pawn };

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
