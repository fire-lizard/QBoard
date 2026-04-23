#pragma once
#include "ChessPiece.h"

class GrandeAcedrexPiece : public ChessPiece
{
public:
    GrandeAcedrexPiece();
    GrandeAcedrexPiece(PieceType pieceType, PieceColour pieceColour);
    ~GrandeAcedrexPiece() override;
    void Promote(PieceType pieceType = None) override;
    std::string StringCode() override;
    std::string GetImageFileName() const override;
    static PieceType FromStringCode(const std::string& code);
    static std::string PieceType2Description(PieceType pieceType);
    static PieceType Description2PieceType(const std::string& description);
};
