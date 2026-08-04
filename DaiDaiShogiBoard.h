#pragma once
#include "Common.h"
#include "MakaDaiDaiShogiBoard.h"

class DaiDaiShogiBoard : public MakaDaiDaiShogiBoard
{
public:
	DaiDaiShogiBoard();
	~DaiDaiShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	PieceType PromotesTo(PieceType pieceType) const override;
    void GetMoves(const std::optional<Piece>& piece, int x, int y) override;

private:

	PieceType _initialSetup[17][17] = {
		{ Lance, Tengu, Yaksha, RacingChariot, DragonHorse, FreeDemon, Queen, LeftGeneral, King, RightGeneral, FreeDreamEater, DragonKing, SquareMover, Rook, Dove, HookMover, Lance },
		{ ReverseChariot, OldKite, Lion, OldRat, PrancingStag, CatSword, Phoenix, Gold, NeighboringKing, Gold, Kylin, RushingBird, FlyingDragon, BlindMonkey, LionDog, PoisonousSnake, ReverseChariot },
		{ None, VerticalMover, None, EnchantedFox, None, WaterBuffalo, None, Silver, GreatDragon, Silver, None, FlyingHorse, None, EnchantedBadger, None, Bishop, None },
		{ BlueDragon, FragrantElephant, NorthernBarbarian, WesternBarbarian, Wood, Stone, Iron, Copper, GoldenBird, Copper, Iron, Stone, Wood, EasternBarbarian, SouthernBarbarian, WhiteElephant, WhiteTiger },
		{ LeftChariot, SideMover, ViolentOx, AngryBoar, EvilWolf, ViolentBear, Leopard, SavageTiger, StandardBearer, SavageTiger, Leopard, ViolentBear, EvilWolf, AngryBoar, ViolentOx, SideMover, RightChariot },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, HowlingDog, None, None, None, None, None, HowlingDog, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, HowlingDog, None, None, None, None, None, HowlingDog, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ RightChariot, SideMover, ViolentOx, AngryBoar, EvilWolf, ViolentBear, Leopard, SavageTiger, StandardBearer, SavageTiger, Leopard, ViolentBear, EvilWolf, AngryBoar, ViolentOx, SideMover, LeftChariot },
		{ WhiteTiger, WhiteElephant, SouthernBarbarian, EasternBarbarian, Wood, Stone, Iron, Copper, GoldenBird, Copper, Iron, Stone, Wood, WesternBarbarian, NorthernBarbarian, FragrantElephant, BlueDragon },
		{ None, Bishop, None, EnchantedBadger, None, FlyingHorse, None, Silver, GreatDragon, Silver, None, WaterBuffalo, None, EnchantedFox, None, VerticalMover, None },
		{ ReverseChariot, PoisonousSnake, LionDog, BlindMonkey, FlyingDragon, RushingBird, Kylin, Gold, NeighboringKing, Gold, Phoenix, CatSword, PrancingStag, OldRat, Lion, OldKite, ReverseChariot },
		{ Lance, HookMover, Dove, Rook, SquareMover, DragonKing, FreeDreamEater, RightGeneral, King, LeftGeneral, Queen, FreeDemon, DragonHorse, RacingChariot, Yaksha, Tengu, Lance }
	};
};

