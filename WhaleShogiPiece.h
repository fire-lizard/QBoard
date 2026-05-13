#pragma once
#include "unordered_map"
#include "Piece.h"

class WhaleShogiPiece : public Piece
{
public:
    WhaleShogiPiece(PieceType pieceType, PieceColour pieceColour);
    ~WhaleShogiPiece() override;
    void Promote(PieceType pieceType = None) override;
    std::string StringCode() override;
    static PieceType FromStringCode(const std::string& code);
    static std::string PieceType2Description(PieceType pieceType);
    static PieceType Description2PieceType(const std::string& description);
};
