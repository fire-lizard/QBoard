#pragma once
#include "Common.h"
#include "DaiShogiBoard.h"
#include "KoShogiPiece.h"

class KoShogiBoard : public DaiShogiBoard
{
public:
	KoShogiBoard();
	~KoShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;

protected:

private:

	PieceType _initialSetup[19][19] = {
	{AdvanceGuard, TaoistPriest, Copper, Leopard, Silver, Gold, Wrestler, Elephant, Phoenix, King, Kylin, Elephant, Wrestler, Gold, Silver, Leopard, Copper, SpiritualMonk, AdvanceGuard},
	{RearGuard, DragonHorse, None, DragonKing, None, Queen, None, Tiger, Banner, MiddleTroop, Drum, Tiger, None, Queen, None, DragonKing, None, DragonHorse, RearGuard},
	{Bishop, Cannon, Crossbow, Longbow, Bishop, Cannon, Crossbow, Longbow, Bishop, FrankishCannon, Bishop, Longbow, Crossbow, Cannon, Bishop, Longbow, Crossbow, Cannon, Bishop},
	{Cavalry, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Cavalry},
	{None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None},
	{Rook, ShieldUnit, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldUnit, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldUnit, Rook},
	{None, None, None, None, None, None, None, None, None, Vanguard, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, Vanguard, None, None, None, None, None, None, None, None, None},
	{Rook, ShieldUnit, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldUnit, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldUnit, Rook},
	{None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None},
	{Cavalry, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Cavalry},
	{Bishop, Cannon, Crossbow, Longbow, Bishop, Cannon, Crossbow, Longbow, Bishop, FrankishCannon, Bishop, Longbow, Crossbow, Cannon, Bishop, Longbow, Crossbow, Cannon, Bishop},
	{RearGuard, DragonHorse, None, DragonKing, None, Queen, None, Tiger, Drum, MiddleTroop, Banner, Tiger, None, Queen, None, DragonKing, None, DragonHorse, RearGuard},
	{AdvanceGuard, SpiritualMonk, Copper, Leopard, Silver, Gold, Wrestler, Elephant, Kylin, King, Phoenix, Elephant, Wrestler, Gold, Silver, Leopard, Copper, TaoistPriest, AdvanceGuard},
	};
};

