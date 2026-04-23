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
    std::string Description() const;
    static std::string ToStringCode(PieceType piece);
    static std::string PieceType2Description(PieceType pieceType);
    static PieceType Description2PieceType(const std::string& description);
};
