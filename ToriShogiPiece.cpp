#include "ToriShogiPiece.h"

ToriShogiPiece::ToriShogiPiece(PieceType pieceType, PieceColour pieceColour) : KanjiPiece(pieceType, pieceColour)
{
}

ToriShogiPiece::~ToriShogiPiece()
{
}

void ToriShogiPiece::Promote(PieceType pieceType)
{
    _isPromoted = true;
    switch (_pieceType)
    {
    case Falcon:
        _pieceType = Eagle;
        break;
    case Pawn:
        _pieceType = Goose;
        break;
    default:
        break;
    }
}

std::string ToriShogiPiece::StringCode()
{
    switch (_pieceType)
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
