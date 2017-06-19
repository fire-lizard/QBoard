#ifndef CHUSHOGIPIECE_H
#define CHUSHOGIPIECE_H
#include "Piece.h"
#include "Common.h"

class ChuShogiPiece : public Piece
{
public:
	ChuShogiPiece(PieceType pieceType, PieceColour pieceColour, bool isPromoted = false);
	virtual ~ChuShogiPiece();
	void Promote(PieceType pieceType = None) override;
	string StringCode() override;

protected:

private:
};

#endif // CHUSHOGIPIECE_H
