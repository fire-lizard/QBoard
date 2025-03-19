#pragma once
#include "Common.h"
#include "ChuShogiBoard.h"
#include "DaiShogiPiece.h"

class DaiShogiBoard : public ChuShogiBoard
{
public:
	DaiShogiBoard();
	~DaiShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;
	void CheckLionDirection(const Piece* piece, int x, int y, Direction direction, int count);

protected:
	std::vector<std::pair<int, int>> GetEnemyPiecesAround(int x, int y, PieceColour pieceColour) const;

private:

	PieceType _initialSetup[15][15] = {
	{Lance, Knight, Stone, Iron, Copper, Silver, Gold, King, Gold, Silver, Copper, Iron, Stone, Knight, Lance},
	{ReverseChariot, None, CatSword, None, Leopard, None, Tiger, Elephant, Tiger, None, Leopard, None, CatSword, None, ReverseChariot},
	{None, ViolentOx, None, AngryBoar, None, EvilWolf, Phoenix, Lion, Kylin, EvilWolf, None, AngryBoar, None, ViolentOx, None},
	{Rook, FlyingDragon, SideMover, VerticalMover, Bishop, DragonHorse, DragonKing, Queen, DragonKing, DragonHorse, Bishop, VerticalMover, SideMover, FlyingDragon, Rook},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, None, GoBetween, None, None, None, None, None, GoBetween, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, GoBetween, None, None, None, None, None, GoBetween, None, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{Rook, FlyingDragon, SideMover, VerticalMover, Bishop, DragonHorse, DragonKing, Queen, DragonKing, DragonHorse, Bishop, VerticalMover, SideMover, FlyingDragon, Rook},
	{None, ViolentOx, None, AngryBoar, None, EvilWolf, Kylin, Lion, Phoenix, EvilWolf, None, AngryBoar, None, ViolentOx, None},
	{ReverseChariot, None, CatSword, None, Leopard, None, Tiger, Elephant, Tiger, None, Leopard, None, CatSword, None, ReverseChariot},
	{Lance, Knight, Stone, Iron, Copper, Silver, Gold, King, Gold, Silver, Copper, Iron, Stone, Knight, Lance}
	};
};

