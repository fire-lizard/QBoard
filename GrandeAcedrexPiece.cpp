#include "GrandeAcedrexPiece.h"

GrandeAcedrexPiece::GrandeAcedrexPiece(PieceType pieceType, PieceColour pieceColour) : ChessPiece(pieceType, pieceColour)
{
}

GrandeAcedrexPiece::~GrandeAcedrexPiece()
{
}

void GrandeAcedrexPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    _pieceType = pieceType;
}

std::string GrandeAcedrexPiece::StringCode()
{
    switch (_pieceType)
    {
    case King:
        return "K";
    case Aanca:
        return "A";
    case Rook:
        return "R";
    case Crocodile:
        return "C";
    case Giraffe:
        return "G";
    case Unicorn:
        return "U";
    case Lion:
        return "L";
    case Pawn:
        return "P";
    default:
        return "";
    }
}

PieceType GrandeAcedrexPiece::FromStringCode(const std::string& code)
{
    static const std::unordered_map<std::string, PieceType> codeToPieceType = {
        {"K", King},
        {"A", Aanca},
        {"R", Rook},
        {"C", Crocodile},
        {"G", Giraffe},
        {"U", Unicorn},
        {"L", Lion},
        {"P", Pawn}
    };

    const auto it = codeToPieceType.find(code);
    return it != codeToPieceType.end() ? it->second : None;
}
