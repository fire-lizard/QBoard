#include "ShatarBoard.h"

ShatarBoard::ShatarBoard()
{
    _width = 8;
    _height = 8;
    ShatranjBoard::Initialize();
}

ShatarBoard::~ShatarBoard()
{
}

Board* ShatarBoard::Clone()
{
    ShatarBoard *sb = new ShatarBoard();
    for (int i = 0; i < GetWidth(); i++)
    {
        for (int j = 0; j < GetHeight(); j++)
        {
            const std::optional<Piece> p = GetData(i, j);
            sb->SetData(i, j, p != std::nullopt ? std::make_optional<Piece>(p->Type, p->Colour) : std::nullopt);
        }
    }
    sb->SetMoveCount(_moveCount);
    return sb;
}

void ShatarBoard::Initialize()
{
    _moveCount = 0;
    _pgn = "";
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_initialSetup[j][i] != None)
            {
                SetData(i, j, Piece(_initialSetup[j][i], j < 4 ? Black : White));
            }
            else
            {
                SetData(i, j, std::nullopt);
            }
        }
    }
}

void ShatarBoard::SetEvalMode(bool evalMode)
{
    _evalMode = evalMode;
}

bool ShatarBoard::IsCheckmate(int oldX, int oldY, int newX, int newY)
{
    ShatarBoard *sb = dynamic_cast<ShatarBoard*>(Clone());
    sb->SetEvalMode(true);
    auto playerMoves = sb->GetAllMoves(GetData(newX, newY)->Colour == White ? Black : White);
    auto opponentMoves = sb->GetAllMoves(GetData(newX, newY)->Colour);
    auto cnt = opponentMoves.size();
	for (auto& opponentMove : opponentMoves)
    {
        if (std::get<0>(opponentMove) == newX && std::get<1>(opponentMove) == newY)
        {
            for (auto& playerMove : playerMoves)
            {
                if (std::get<2>(playerMove) == std::get<2>(opponentMove) && std::get<3>(playerMove) == std::get<3>(opponentMove))
                {
                    cnt--;
                }
            }
        }
        else if (std::get<2>(opponentMove) == oldX && std::get<3>(opponentMove) == oldY)
        {
            return false;
        }
        else
        {
            cnt--;
        }
    }
    delete sb;
    return cnt <= 0;
}

void ShatarBoard::CheckKnightMove(const std::optional<Piece>& piece, int x, int y)
{
    CheckMove(piece, x, y);
	std::vector<std::pair<int, int>> knightMoves;
    knightMoves.emplace_back(x + 1, y + 2);
    knightMoves.emplace_back(x - 1, y + 2);
    knightMoves.emplace_back(x + 2, y + 1);
    knightMoves.emplace_back(x + 2, y - 1);
    knightMoves.emplace_back(x - 2, y + 1);
    knightMoves.emplace_back(x - 2, y - 1);
    knightMoves.emplace_back(x + 1, y - 2);
    knightMoves.emplace_back(x - 1, y - 2);
    for (auto& knightMove : knightMoves)
    {
        auto destPiece = GetData(knightMove.first, knightMove.second);
        if (destPiece != std::nullopt && destPiece->Colour != piece->Colour && destPiece->Type == King && IsCheckmate(x, y, knightMove.first, knightMove.second))
        {
            RemoveMove(x, y);
            break;
        }
    }
}

void ShatarBoard::GetMoves(const std::optional<Piece>& piece, int x, int y)
{
    _moves.clear();
    switch (piece->Type)
    {
    case Queen:
        CheckMove(piece, x + 1, y + 1);
        CheckMove(piece, x + 1, y - 1);
        CheckMove(piece, x - 1, y + 1);
        CheckMove(piece, x - 1, y - 1);
        CheckDirection(piece, x, y, North);
        CheckDirection(piece, x, y, East);
        CheckDirection(piece, x, y, West);
        CheckDirection(piece, x, y, South);
        break;
    case Bishop:
        CheckDirection(piece, x, y, NorthEast);
        CheckDirection(piece, x, y, NorthWest);
        CheckDirection(piece, x, y, SouthEast);
        CheckDirection(piece, x, y, SouthWest);
        break;
    case Knight:
        // Knight cannot be checkmate
        if (!_evalMode)
        {
            CheckKnightMove(piece, x + 1, y + 2);
            CheckKnightMove(piece, x - 1, y + 2);
            CheckKnightMove(piece, x + 2, y + 1);
            CheckKnightMove(piece, x + 2, y - 1);
            CheckKnightMove(piece, x - 2, y + 1);
            CheckKnightMove(piece, x - 2, y - 1);
            CheckKnightMove(piece, x + 1, y - 2);
            CheckKnightMove(piece, x - 1, y - 2);
        }
        else ShatranjBoard::GetMoves(piece, x, y);
		break;
    case Pawn:
        if (piece->Colour == Black)
        {
            if (y + 1 < _height && GetData(x, y + 1) == std::nullopt)
            {
                CheckMove(piece, x, y + 1);
            }
            if (y + 1 < _height && x + 1 < _width && GetData(x + 1, y + 1) != std::nullopt)
            {
                CheckMove(piece, x + 1, y + 1);
            }
            if (y + 1 < _height && x - 1 >= 0 && GetData(x - 1, y + 1) != std::nullopt)
            {
                CheckMove(piece, x - 1, y + 1);
            }
        }
        else
        {
            if (y - 1 >= 0 && GetData(x, y - 1) == std::nullopt)
            {
                CheckMove(piece, x, y - 1);
            }
            if (y - 1 >= 0 && x + 1 < _width && GetData(x + 1, y - 1) != std::nullopt)
            {
                CheckMove(piece, x + 1, y - 1);
            }
            if (y - 1 >= 0 && x - 1 >= 0 && GetData(x - 1, y - 1) != std::nullopt)
            {
                CheckMove(piece, x - 1, y - 1);
            }
        }
        break;
    default:
        ShatranjBoard::GetMoves(piece, x, y);
        break;
    }
}
