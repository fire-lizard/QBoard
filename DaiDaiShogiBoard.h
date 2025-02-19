#pragma once
#include "Common.h"
#include "MakaDaiDaiShogiBoard.h"
#include "DaiDaiShogiPiece.h"

class DaiDaiShogiBoard : public MakaDaiDaiShogiBoard
{
public:
	DaiDaiShogiBoard();
	~DaiDaiShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	Piece* CreatePiece(PieceType pieceType, PieceColour pieceColour) override;
	void GetMoves(Piece* piece, int x, int y) override;

private:

	PieceType _initialSetup[17][17] = {
	{Lance, HookMover, Dove, Rook, SquareMover, DragonKing, FreeDreamEater, RightGeneral, King, LeftGeneral, Queen, FreeDemon, DragonHorse, RacingChariot, Yaksha, Tengu, Lance},
	{ReverseChariot, PoisonousSnake, LionDog, BlindMonkey, FlyingDragon, RushingBird, Kylin, Gold, NeighboringKing, Gold, Phoenix, CatSword, PrancingStag, OldRat, Lion, OldKite, ReverseChariot},
	{None, Bishop, None, EnchantedBadger, None, FlyingHorse, None, Silver, GreatDragon, Silver, None, WaterBuffalo, None, EnchantedFox, None, VerticalMover, None},
	{WhiteTiger, WhiteElephant, SouthernBarbarian, EasternBarbarian, Wood, Stone, Iron, Copper, GoldenBird, Copper, Iron, Stone, Wood, WesternBarbarian, NorthernBarbarian, FragrantElephant, BlueDragon},
	{RightChariot, SideMover, ViolentOx, AngryBoar, EvilWolf, ViolentBear, Leopard, SavageTiger, StandardBearer, SavageTiger, Leopard, ViolentBear, EvilWolf, AngryBoar, ViolentOx, SideMover, LeftChariot},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{None, None, None, None, None, HowlingDog, None, None, None, None, None, HowlingDog, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None},
	{None, None, None, None, None, HowlingDog, None, None, None, None, None, HowlingDog, None, None, None, None, None},
	{Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn},
	{LeftChariot, SideMover, ViolentOx, AngryBoar, EvilWolf, ViolentBear, Leopard, SavageTiger, StandardBearer, SavageTiger, Leopard, ViolentBear, EvilWolf, AngryBoar, ViolentOx, SideMover, RightChariot},
	{BlueDragon, FragrantElephant, NorthernBarbarian, WesternBarbarian, Wood, Stone, Iron, Copper, GoldenBird, Copper, Iron, Stone, Wood, EasternBarbarian, SouthernBarbarian, WhiteElephant, WhiteTiger},
	{None, VerticalMover, None, EnchantedFox, None, WaterBuffalo, None, Silver, GreatDragon, Silver, None, FlyingHorse, None, EnchantedBadger, None, Bishop, None},
	{ReverseChariot, OldKite, Lion, OldRat, PrancingStag, CatSword, Phoenix, Gold, NeighboringKing, Gold, Kylin, RushingBird, FlyingDragon, BlindMonkey, LionDog, PoisonousSnake, ReverseChariot},
	{Lance, Tengu, Yaksha, RacingChariot, DragonHorse, FreeDemon, Queen, LeftGeneral, King, RightGeneral, FreeDreamEater, DragonKing, SquareMover, Rook, Dove, HookMover, Lance}
	};
};

