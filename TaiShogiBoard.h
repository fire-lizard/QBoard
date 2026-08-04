#pragma once
#include "DaiDaiShogiBoard.h"

class TaiShogiBoard : public DaiDaiShogiBoard
{
public:
	TaiShogiBoard();
	~TaiShogiBoard() override;
	void Initialize() override;
	Board* Clone() override;
	PieceType PromotesTo(PieceType pieceType) const override;
    void GetMoves(const std::optional<Piece>& piece, int x, int y) override;

private:

	PieceType _initialSetup[25][25] = {
		{ Lance, TurtleSnake, Whale, FlyingDragon, Tengu, Dove, Rook, DragonHorse, DragonKing, Queen, Gold, Deva, Emperor, DarkSpirit, Gold, Queen, DragonKing, DragonHorse, Rook, Dove, Tengu, FlyingDragon, Whale, WhiteTiger, Lance },
		{ ReverseChariot, SideDragon, Eagle, Knight, PoisonousSnake, FreeDreamEater, Bishop, FierceEagle, WhiteElephant, FreeDemon, Silver, LeftGeneral, Prince, RightGeneral, Silver, FreeDemon, WhiteElephant, FierceEagle, Bishop, FreeDreamEater, PoisonousSnake, Knight, Eagle, SideDragon, ReverseChariot },
		{ RacingChariot, WhiteHorse, RamHeadSoldier, ViolentOx, CatSword, BlindBear, SilverHare, GoldenDeer, BlindMonkey, Tiger, BuddhistDevil, Wrestler, NeighboringKing, Guardian, Yaksha, Tiger, BlindMonkey, GoldenDeer, SilverHare, BlindBear, CatSword, ViolentOx, RamHeadSoldier, WhiteHorse, RacingChariot },
		{ Soldier, WaterBuffalo, Leopard, WesternBarbarian, EasternBarbarian, ChineseCock, Falcon, OldMonkey, OldKite, Peacock, GreatDragon, Kylin, Lion, Phoenix, GoldenBird, Peacock, RushingBird, OldMonkey, Falcon, ChineseCock, SouthernBarbarian, NorthernBarbarian, Leopard, WaterBuffalo, Soldier },
		{ LeftChariot, BlueDragon, Wood, Earth, Stone, Tile, Iron, Copper, OldRat, CoiledSerpent, RecliningDragon, Capricorn, Elephant, HookMover, RecliningDragon, CoiledSerpent, OldRat, Copper, Iron, Tile, Stone, Earth, Wood, VermillionSparrow, RightChariot },
		{ HowlingDog, FlyingHorse, EnchantedBadger, Donkey, FlyingOx, SideMover, VerticalMover, ViolentBear, StandardBearer, PrancingStag, AngryBoar, EvilWolf, LionDog, EvilWolf, AngryBoar, PrancingStag, StandardBearer, ViolentBear, VerticalMover, SideMover, FlyingOx, Donkey, EnchantedBadger, FlyingHorse, HowlingDog },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ None, None, None, None, None, None, None, GoBetween, None, None, None, None, None, None, None, None, None, GoBetween, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None },
		{ None, None, None, None, None, None, None, GoBetween, None, None, None, None, None, None, None, None, None, GoBetween, None, None, None, None, None, None, None },
		{ Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn, Pawn },
		{ HowlingDog, FlyingHorse, EnchantedBadger, Donkey, FlyingOx, SideMover, VerticalMover, ViolentBear, StandardBearer, PrancingStag, AngryBoar, EvilWolf, LionDog, EvilWolf, AngryBoar, PrancingStag, StandardBearer, ViolentBear, VerticalMover, SideMover, FlyingOx, Donkey, EnchantedBadger, FlyingHorse, HowlingDog },
		{ RightChariot, VermillionSparrow, Wood, Earth, Stone, Tile, Iron, Copper, OldRat, CoiledSerpent, RecliningDragon, HookMover, Elephant, Capricorn, RecliningDragon, CoiledSerpent, OldRat, Copper, Iron, Tile, Stone, Earth, Wood, BlueDragon, LeftChariot },
		{ Soldier, WaterBuffalo, Leopard, NorthernBarbarian, SouthernBarbarian, ChineseCock, Falcon, OldMonkey, RushingBird, Peacock, GoldenBird, Phoenix, Lion, Kylin, GreatDragon, Peacock, OldKite, OldMonkey, Falcon, ChineseCock, EasternBarbarian, WesternBarbarian, Leopard, WaterBuffalo, Soldier },
		{ RacingChariot, WhiteHorse, RamHeadSoldier, ViolentOx, CatSword, BlindBear, SilverHare, GoldenDeer, BlindMonkey, Tiger, Yaksha, Guardian, NeighboringKing, Wrestler, BuddhistDevil, Tiger, BlindMonkey, GoldenDeer, SilverHare, BlindBear, CatSword, ViolentOx, RamHeadSoldier, WhiteHorse, RacingChariot },
		{ ReverseChariot, SideDragon, Eagle, Knight, PoisonousSnake, FreeDreamEater, Bishop, FierceEagle, WhiteElephant, FreeDemon, Silver, RightGeneral, Prince, LeftGeneral, Silver, FreeDemon, WhiteElephant, FierceEagle, Bishop, FreeDreamEater, PoisonousSnake, Knight, Eagle, SideDragon, ReverseChariot },
		{ Lance, WhiteTiger, Whale, FlyingDragon, Tengu, Dove, Rook, DragonHorse, DragonKing, Queen, Gold, DarkSpirit, Emperor, Deva, Gold, Queen, DragonKing, DragonHorse, Rook, Dove, Tengu, FlyingDragon, Whale, TurtleSnake, Lance }
	};
};

