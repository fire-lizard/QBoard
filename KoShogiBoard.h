#pragma once
#include <queue>
#include <set>
#include "Common.h"
#include "TenjikuShogiBoard.h"
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
	bool Move(int oldX, int oldY, int newX, int newY, bool cl = true) override;
	void GetShoots(const Piece* piece, int x, int y);
	std::vector<std::pair<int, int>> Shoots() const;
	void Shoot(int x, int y);

private:
	void CheckShoot(const Piece* piece, int x, int y);
	void CheckShootingDirection(const Piece* piece, int x, int y, Direction direction, int count, bool shootOver);
	void GetPossibleMoves(int x, int y);
	void getAll5StepPaths(int startR, int startC, PieceColour pieceColour);
	void dfsFiveSteps(int r, int c, int step, PieceColour pieceColour, std::vector<std::pair<int, int>>& currentPath);

	std::vector<std::pair<int, int>> _shoots;

	PieceType _initialSetup[19][19] = {
	{AdvanceGuard, TaoistPriest, Copper, Leopard, Silver, Gold, Lion, Elephant, Phoenix, King, Kylin, Elephant, Lion, Gold, Silver, Leopard, Copper, SpiritualMonk, AdvanceGuard},
	{RearGuard, DragonHorse, None, DragonKing, None, Queen, None, Tiger, Flag, MiddleTroop, Drum, Tiger, None, Queen, None, DragonKing, None, DragonHorse, RearGuard},
	{Bishop, Cannon, Crossbow, Longbow, Bishop, Cannon, Crossbow, Longbow, Bishop, FrankishCannon, Bishop, Longbow, Crossbow, Cannon, Bishop, Longbow, Crossbow, Cannon, Bishop},
	{KnightCaptain, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, KnightCaptain},
	{None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None},
	{Rook, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Rook},
	{None, None, None, None, None, None, None, None, None, Vanguard, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, Vanguard, None, None, None, None, None, None, None, None, None},
	{Rook, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Chariot, CatSword, Chariot, CatSword, Chariot, CatSword, Chariot, ShieldCaptain, Rook},
	{None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None, Pawn, None, Pawn, None, Pawn, None, VerticalMover, None},
	{KnightCaptain, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, Knight, None, KnightCaptain},
	{Bishop, Cannon, Crossbow, Longbow, Bishop, Cannon, Crossbow, Longbow, Bishop, FrankishCannon, Bishop, Longbow, Crossbow, Cannon, Bishop, Longbow, Crossbow, Cannon, Bishop},
	{RearGuard, DragonHorse, None, DragonKing, None, Queen, None, Tiger, Drum, MiddleTroop, Flag, Tiger, None, Queen, None, DragonKing, None, DragonHorse, RearGuard},
	{AdvanceGuard, SpiritualMonk, Copper, Leopard, Silver, Gold, Lion, Elephant, Kylin, King, Phoenix, Elephant, Lion, Gold, Silver, Leopard, Copper, TaoistPriest, AdvanceGuard},
	};
};

