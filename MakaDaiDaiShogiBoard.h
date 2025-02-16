#pragma once
#include "Common.h"
#include "DaiShogiBoard.h"
#include "MakaDaiDaiShogiPiece.h"

class MakaDaiDaiShogiBoard : public DaiShogiBoard
{
public:
	MakaDaiDaiShogiBoard();
	~MakaDaiDaiShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;

protected:

private:

	PieceType _initialSetup[19][19] = {
	{Lance, Earth, Stone, Tile, Iron, Copper, Silver, Gold, Deva, King, DarkSpirit, Gold, Silver, Copper, Iron, Tile, Stone, Earth, Lance},
	{ReverseChariot, None, CatSword, None, ChineseCock, None, CoiledSerpent, Leopard, Tiger, Elephant, Tiger, Leopard, CoiledSerpent, None, ChineseCock, None, CatSword, None, ReverseChariot},
	{None, OldRat, None, AngryBoar, None, BlindBear, None, EvilWolf, Kylin, Lion, Phoenix, EvilWolf, None, BlindBear, None, AngryBoar, None, OldRat, None},
	{Donkey, None, Knight, None, ViolentOx, None, FlyingDragon, BuddhistSpirit, Wrestler, LionDog, Guardian, Yaksha, FlyingDragon, None, ViolentOx, None, Knight, None, Donkey},
	{Rook, RightChariot, SideMover, SideFlier, VerticalMover, Bishop, DragonHorse, DragonKing, Capricorn, King, HookMover, DragonKing, DragonHorse, Bishop, VerticalMover, SideFlier, SideMover, LeftChariot, Rook},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, None, None, GoBetween, None, None, None, None, None, None, None, GoBetween, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, GoBetween, None, None, None, None, None, None, None, GoBetween, None, None, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{Rook, LeftChariot, SideMover, SideFlier, VerticalMover, Bishop, DragonHorse, DragonKing, Capricorn, King, HookMover, DragonKing, DragonHorse, Bishop, VerticalMover, SideFlier, SideMover, RightChariot, Rook},
	{Donkey, None, Knight, None, ViolentOx, None, FlyingDragon, BuddhistSpirit, Wrestler, LionDog, Guardian, Yaksha, FlyingDragon, None, ViolentOx, None, Knight, None, Donkey},
	{None, OldRat, None, AngryBoar, None, BlindBear, None, EvilWolf, Kylin, Lion, Phoenix, EvilWolf, None, BlindBear, None, AngryBoar, None, OldRat, None},
	{ReverseChariot, None, CatSword, None, ChineseCock, None, CoiledSerpent, Leopard, Tiger, Elephant, Tiger, Leopard, CoiledSerpent, None, ChineseCock, None, CatSword, None, ReverseChariot},
	{Lance, Earth, Stone, Tile, Iron, Copper, Silver, Gold, Deva, King, DarkSpirit, Gold, Silver, Copper, Iron, Tile, Stone, Earth, Lance}
	};
};
