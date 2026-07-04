#include "graphicsmanager.h"

void GraphicsManager::DrawPiece(QPainter& painter, Piece p, GameVariant gameVariant, PieceStyle pieceStyle, int w, int h, int i, int j)
{
    bool isAsianStyle = pieceStyle == Asian || pieceStyle == Asian2 || pieceStyle == Asian3 || pieceStyle == Asian4;
    QPixmap pixmap(GetImageFileName(gameVariant, pieceStyle, p.Colour, p.Type, p.IsPromoted));
    switch (gameVariant)
    {
    case MicroShogi:
    case KyotoShogi:
        painter.drawPixmap(i * w + w / 8, j * h + h / 8, pixmap.size().width(), pixmap.size().height(), pixmap);
        break;
    case Shogi:
    case ShoShogi:
    case MiniShogi:
    case JudkinShogi:
    case EuroShogi:
        if (isAsianStyle)
        {
            painter.drawPixmap(i * w + w / 8, j * h + h / 8, 48, 48, pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    case WhaleShogi:
        painter.drawPixmap(i * w + w / 12, j * h + h / 12, pixmap.size().width(), pixmap.size().height(), pixmap);
        break;
    case ToriShogi:
        if (pieceStyle == European || pieceStyle == Asian)
        {
            painter.drawPixmap(i * w + w / 12, j * h + h / 12, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 6, j * h + h / 6, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    case YariShogi:
        painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        break;
    case MakaDaiDaiShogi:
        if (pieceStyle == Asian)
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 8, j * h + h / 8, 40, 40, pixmap);
        }
        break;
    case KoShogi:
        if (pieceStyle != Mnemonic)
        {
            painter.drawPixmap(i * w + w / 12, j * h + h / 12, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 20, j * h + h / 20, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    case ChuShogi:
    case DaiShogi:
    case HeianShogi:
    case HeianDaiShogi:
        if (pieceStyle == Asian2 || pieceStyle == Asian4)
        {
            painter.drawPixmap(i * w + w / 8, j * h + h / 8, 48, 48, pixmap);
        }
        else if (pieceStyle == Asian3 && gameVariant == DaiShogi)
        {
            painter.drawPixmap(i * w + w / 6, j * h + h / 6, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    case WaShogi:
    case CrazyWa:
        painter.drawPixmap(i * w + w / 8, j * h + h / 8, pixmap.size().width(), pixmap.size().height(), pixmap);
        break;
    case TenjikuShogi:
    case DaiDaiShogi:
    case CapablancaChess:
    case GothicChess:
    case JanusChess:
    case GrandChess:
    case OmegaChess:
    case NightriderChess:
    case CourierChess:
    case ChancellorChess:
    case ModernChess:
    case MusketeerChess:
    case GrandeAcedrex:
        painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        break;
    case Makruk:
        if (pieceStyle == European)
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else if (pieceStyle == Mnemonic)
        {
            painter.drawPixmap(i * w + w / 4.25, j * h + h / 6, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 10, j * h + h / 10, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    case Chess:
    case Shatranj:
    case Shatar:
    case Sittuyin:
        if (pieceStyle == Mnemonic)
        {
            painter.drawPixmap(i * w + w / 10, j * h + h / 10, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else if (pieceStyle == Asian)
        {
            painter.drawPixmap(i * w + w / 20, j * h, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else if (pieceStyle == Asian2)
        {
            painter.drawPixmap(i * w + w / 6, j * h + h / 8, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else if (pieceStyle == Asian3)
        {
            painter.drawPixmap(i * w + w / 3.25, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    case Xiangqi:
    case Janggi:
        if (pieceStyle == European || pieceStyle == Asian)
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 6, j * h + h / 6, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    }
}

QString GraphicsManager::GetResourcePrefix(GameVariant gameVariant, PieceStyle pieceStyle)
{
    bool isAsianStyle = pieceStyle == Asian || pieceStyle == Asian2 || pieceStyle == Asian3 || pieceStyle == Asian4;
    switch (gameVariant)
    {
    case Xiangqi:
    case Janggi:
        if (pieceStyle == European) return ":/pieces_eur/images/";
        if (pieceStyle == Mnemonic) return ":/pieces_xia/images_xia/";
        if (pieceStyle == Asian) return ":/pieces_chi/images_chi/";
        if (pieceStyle == Asian2) return ":/pieces_chi2/images_chi2/";
        if (pieceStyle == Asian3) return ":/pieces_chi3/images_chi3/";
        return ":/pieces_chi4/images_chi4/";
    case MicroShogi:
    case KyotoShogi:
        return ":/pieces_kyo/images_kyo/";
    case Shogi:
    case ShoShogi:
    case MiniShogi:
    case JudkinShogi:
    case EuroShogi:
        if (pieceStyle == European) return ":/pieces_eur/images/";
        if (pieceStyle == Mnemonic) return ":/pieces_sho2/images_sho2/";
        if (pieceStyle == Asian) return ":/pieces_sho/images_sho/";
        if (pieceStyle == Asian2) return ":/pieces_sho3/images_sho3/";
        return ":/pieces_maka2/images_maka2/";
    case WhaleShogi:
        return ":/pieces_wha/images_wha/";
    case ToriShogi:
        if (pieceStyle == European || pieceStyle == Asian) return ":/pieces_tori/images_tori/";
        if (pieceStyle == Mnemonic) return ":/pieces_torim/images_torim/";
        return ":/pieces_torik/images_torik/";
    case YariShogi:
        if (pieceStyle == European) return ":/pieces_yam/images_yam/";
        if (pieceStyle == Mnemonic) return ":/pieces_ptg/images_ptg/";
        return ":/pieces_yak/images_yak/";
    case ChuShogi:
        if (pieceStyle == Asian) return ":/pieces_tnk/images_tnk/";
        if (pieceStyle == Asian2) return ":/pieces_maka2/images_maka2/";
        if (pieceStyle == Asian3) return ":/pieces_knj/images_knj/";
        if (pieceStyle == Asian4) return ":/pieces_jap/images_jap/";
        if (pieceStyle == Mnemonic) return ":/pieces_chu/images_chu/";
        return ":/pieces_eur/images/";
    case DaiShogi:
    case HeianShogi:
    case HeianDaiShogi:
        if (pieceStyle == Asian) return ":/pieces_tnk/images_tnk/";
        if (pieceStyle == Asian2 || pieceStyle == Asian4) return ":/pieces_maka2/images_maka2/";
        if (pieceStyle == Asian3) return ":/pieces_dai/images_dai/";
        return ":/pieces_eur/images/";
    case TenjikuShogi:
        return isAsianStyle ? ":/pieces_tnk/images_tnk/" : ":/pieces_ten/images_ten/";
    case WaShogi:
    case CrazyWa:
        return isAsianStyle ? ":/pieces_wa2/images_wa2/" : ":/pieces_wa/images_wa/";
    case DaiDaiShogi:
        return ":/pieces_dd/images_daidai/";
    case MakaDaiDaiShogi:
        return pieceStyle == Asian ? ":/pieces_mdd/images_maka/" : ":/pieces_maka2/images_maka2/";
    case KoShogi:
        if (pieceStyle == Asian) return ":/pieces_ko/images_ko/";
        if (isAsianStyle) return ":/pieces_kok/images_kok/";
        if (pieceStyle == Mnemonic) return ":/pieces_km/images_kom/";
        return ":/pieces_kow/images_kow/";
    case Chess:
    case Shatranj:
    case Shatar:
    case Sittuyin:
        if (pieceStyle == European) return ":/pieces_eur/images/";
        if (pieceStyle == Mnemonic) return ":/pieces_eur/images_eur/";
        if (pieceStyle == Asian) return ":/pieces_eur2/images_eur2/";
        if (pieceStyle == Asian2) return ":/pieces_eur3/images_eur3/";
        if (pieceStyle == Asian3) return ":/pieces_sit/images_sit/";
        return gameVariant == Sittuyin ? ":/pieces_sit/images_sit/" : ":/pieces_sha/images_sha/";
    case Makruk:
        if (pieceStyle == European) return ":/pieces_eur/images/";
        if (pieceStyle == Mnemonic) return ":/pieces_mak2/images_mak2/";
        return ":/pieces_mak/images_mak/";
    case CapablancaChess:
    case GothicChess:
    case JanusChess:
    case GrandChess:
    case OmegaChess:
    case NightriderChess:
    case CourierChess:
    case ChancellorChess:
    case ModernChess:
    case MusketeerChess:
    case GrandeAcedrex:
        return ":/pieces_eur/images/";
    }
    return "";
}

QString GraphicsManager::GetImageFileName(GameVariant gameVariant, PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    QString imageFileName;
    switch (gameVariant)
    {
    case Xiangqi:
    case Janggi:
        imageFileName = pieceStyle == European ?
            GetImageFileName(pieceColour, pieceType, isPromoted) : GetXiangqiImageFileName(pieceColour, pieceType);
        break;
    case MicroShogi:
    case KyotoShogi:
        imageFileName = GetKyotoShogiImageFileName(pieceStyle, pieceColour, pieceType);
        break;
    case Shogi:
    case ShoShogi:
    case MiniShogi:
    case JudkinShogi:
    case EuroShogi:
    case HeianShogi:
        if (pieceStyle == Mnemonic || pieceStyle == Asian || pieceStyle == Asian2) imageFileName = GetShogiImageFileName(pieceColour, pieceType, isPromoted);
        else if (pieceStyle == Asian3 || pieceStyle == Asian4) imageFileName = GetKanjiImageFileName2(pieceColour, pieceType, isPromoted);
        else imageFileName = GetImageFileName(pieceColour, pieceType, isPromoted);
        break;
    case WhaleShogi:
        if (pieceStyle == European) imageFileName = GetWhaleShogiImageFileName(pieceColour, pieceType);
        else imageFileName = "L" + GetWhaleShogiImageFileName(pieceColour, pieceType);
        break;
    case ToriShogi:
        imageFileName = GetToriShogiImageFileName(pieceStyle, pieceColour, pieceType);
        break;
    case YariShogi:
        imageFileName = GetYariShogiImageFileName(pieceColour, pieceType);
        break;
    case DaiShogi:
    case HeianDaiShogi:
        if (pieceStyle == Asian) imageFileName = GetKanjiImageFileName(pieceColour, pieceType, isPromoted);
        else if (pieceStyle == Asian2 || pieceStyle == Asian4) imageFileName = GetKanjiImageFileName2(pieceColour, pieceType, isPromoted);
        else imageFileName = GetImageFileName(pieceColour, pieceType, isPromoted);
        break;
    case MakaDaiDaiShogi:
        imageFileName = pieceStyle == Asian ?
            GetKanjiImageFileName3(pieceColour, pieceType, isPromoted) : GetKanjiImageFileName2(pieceColour, pieceType, isPromoted);
        break;
    case KoShogi:
        imageFileName = GetKoShogiImageFileName(pieceStyle, pieceColour, pieceType, isPromoted);
        break;
    case ChuShogi:
        if (pieceStyle == Asian) imageFileName = GetKanjiImageFileName(pieceColour, pieceType, isPromoted);
        else if (pieceStyle == Asian2) imageFileName = GetKanjiImageFileName2(pieceColour, pieceType, isPromoted);
        else if (pieceStyle == Asian3) imageFileName = "J" + GetMnemonicImageFileName(pieceColour, pieceType, isPromoted);
        else if (pieceStyle == Mnemonic) imageFileName = GetMnemonicImageFileName(pieceColour, pieceType, isPromoted);
        else imageFileName = GetImageFileName(pieceColour, pieceType, isPromoted);
        break;
    case TenjikuShogi:
        if (pieceStyle == European || pieceStyle == Mnemonic) imageFileName = GetTenjikuShogiImageFileName(pieceColour, pieceType, isPromoted);
        else imageFileName = GetKanjiImageFileName(pieceColour, pieceType, isPromoted);
        break;
    case WaShogi:
    case CrazyWa:
        imageFileName = GetWaShogiImageFileName(pieceStyle, pieceColour, pieceType, isPromoted);
        break;
    case DaiDaiShogi:
        imageFileName = GetKanjiImageFileName3(pieceColour, pieceType, isPromoted);
        break;
    case Chess:
    case CapablancaChess:
    case GothicChess:
    case JanusChess:
    case GrandChess:
    case OmegaChess:
    case NightriderChess:
    case CourierChess:
    case ChancellorChess:
    case ModernChess:
    case MusketeerChess:
    case Shatranj:
    case Shatar:
    case Sittuyin:
    case GrandeAcedrex:
        if (gameVariant == Sittuyin && pieceStyle == Asian4) imageFileName = GetSittuyinImageFileName(pieceColour, pieceType);
    	else imageFileName = GetImageFileName(pieceColour, pieceType, isPromoted);
        break;
    case Makruk:
        if (pieceStyle == European) imageFileName = GetImageFileName(pieceColour, pieceType, isPromoted);
        else imageFileName = GetMakrukImageFileName(pieceColour, pieceType, isPromoted);
        break;
    }
    return GetResourcePrefix(gameVariant, pieceStyle) + imageFileName;
}

QString GraphicsManager::GetImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    const QString colour = pieceColour == White ? "White" : "Black";
    const QString promo = isPromoted ? "Promo" : "";
    switch (pieceType)
    {
    case King:
    case Prince:
        return colour + "King.png";
    case Lion:
        return colour + "Lion.png";
    case Queen:
        return colour + "Queen.png";
    case DragonKing:
        return colour + promo + "CrownedRook.png";
    case DragonHorse:
        return colour + promo + "CrownedBishop.png";
    case Rook:
        return colour + promo + "Rook.png";
    case Bishop:
    case Crocodile:
        return colour + promo + "Bishop.png";
    case VerticalMover:
        return colour + promo + "Sword.png";
    case SideMover:
        return colour + promo + "HSword.png";
    case Cannon:
    case ReverseChariot:
        return colour + "Canon.png";
    case Lance:
        return colour + "Lance.png";
    case Kylin:
        return colour + "Marshall.png";
    case Phoenix:
        return colour + "Archbishop.png";
    case Elephant:
        return colour + "Elephant.png";
    case Tiger:
        return colour + "Claw.png";
    case Gold:
        return colour + "Gold.png";
    case Tokin:
        return colour + "GoldPawn.png";
    case PromotedLance:
        return colour + "GoldLance.png";
    case PromotedKnight:
        return colour + "GoldKnight.png";
    case PromotedSilver:
        return colour + "GoldSilver.png";
    case Silver:
        return colour + "Advisor.png";
    case Copper:
        return colour + "Copper.png";
    case Leopard:
        return colour + "Leopard.png";
    case GoBetween:
        return colour + "Cobra.png";
    case Pawn:
        return colour + "Pawn.png";
    case Eagle:
        return colour + "Hawk.png";
    case Unicorn:
        return colour + "Unicorn.png";
    case FlyingOx:
        return colour + "Princess.png";
    case FreeBoar:
        return colour + "HCrown.png";
    case FlyingStag:
        return colour + "Chancellor.png";
    case Knight:
    case WhiteHorse:
        return colour + "Knight.png";
    case Whale:
        return colour + "Dolphin.png";
    case Iron:
        return colour + "Iron.png";
    case Stone:
        return colour + "Stone.png";
    case AngryBoar:
        return colour + "AngryBoar.png";
    case ViolentOx:
        return colour + "Gnu.png";
    case FlyingDragon:
        return colour + "Dragon.png";
    case EvilWolf:
        return colour + "Wolf.png";
    case CatSword:
        return colour + "CatSword.png";
    case Archbishop:
        return colour + "Archbishop.png";
    case Chancellor:
        return colour + "Chancellor.png";
    case Aanca:
        return colour + "Hawk.png";
    case Giraffe:
        return colour + "Camel.png";
    case Champion:
        return colour + "Viking.png";
    case Wizard:
    case Sage:
        return colour + "Wizard.png";
    case Nightrider:
        return colour + "Nightrider.png";
    case Schleich:
        return colour + "Hat.png";
    case Courier:
        return colour + "Pegasus.png";
    case Fortress:
        return colour + "Tower.png";
    case Spider:
        return colour + "Axe.png";
    default:
        return "";
    }
}

QString GraphicsManager::GetMakrukImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    QString colour = pieceColour == White ? "White" : "Black";
    if (pieceType == Queen && isPromoted)
    {
        return colour + "PawnP.png";
    }
    else
    {
        return GetImageFileName(pieceColour, pieceType, isPromoted);
    }
}

QString GraphicsManager::GetXiangqiImageFileName(PieceColour pieceColour, PieceType pieceType)
{
    QString colour = pieceColour == White ? "r" : "b";
    switch (pieceType)
    {
    case King:
        return colour + "king.png";
    case Rook:
        return colour + "chariot.png";
    case Cannon:
        return colour + "cannon.png";
    case Elephant:
        return colour + "elephant.png";
    case Silver:
        return colour + "advisor.png";
    case Pawn:
        return colour + "pawn.png";
    case Knight:
        return colour + "horse.png";
    default:
        return "";
    }
}

QString GraphicsManager::GetShogiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    if (isPromoted)
    {
        const QString colour = pieceColour == White ? "White" : "Black";
        if (pieceType == DragonHorse)
        {
            return colour + "CrownedBishop.png";
        }
        if (pieceType == DragonKing)
        {
            return colour + "CrownedRook.png";
        }
        if (pieceType == Prince)
        {
            return colour + "King.png";
        }
    }
    return GetImageFileName(pieceColour, pieceType, isPromoted);
}

QString GraphicsManager::GetWhaleShogiImageFileName(PieceColour pieceColour, PieceType pieceType)
{
    QString colour = pieceColour == White ? "B" : "W";
    switch (pieceType)
    {
    case King:
        return colour + "WhWhale.png";
    case GreyWhale:
        return colour + "GrWhale.png";
    case Porpoise:
        return colour + "Porpoise.png";
    case DragonKing:
        return colour + "KWhale.png";
    case Narwhal:
        return colour + "Narwhal.png";
    case Humpback:
        return colour + "HBwhale.png";
    case BlueWhale:
        return colour + "BWhale.png";
    case Pawn:
        return colour + "Dolphin.png";
    default:
        return "";
    }
}

QString GraphicsManager::GetYariShogiImageFileName(PieceColour pieceColour, PieceType pieceType)
{
    QString colour = pieceColour == White ? "" : "Flip";
    switch (pieceType)
    {
    case King:
        return "King" + colour + ".png";
    case Rook:
        return "RookP" + colour + ".png";
    case Pawn:
        return "Pawn" + colour + ".png";
    case YariKnight:
        return "Knight" + colour + ".png";
    case YariRook:
        return "Rook" + colour + ".png";
    case YariBishop:
        return "Bishop" + colour + ".png";
    case YariGold:
        return "Gold" + colour + ".png";
    case YariSilver:
        return "Silver" + colour + ".png";
    default:
        return "";
    }
}

QString GraphicsManager::GetMnemonicImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    const QString colour = pieceColour == White ? "_B" : "_W";
    const QString promo = isPromoted ? "P" : "";
    switch (pieceType)
    {
    case King:
        return "King" + colour + ".png";
    case Prince:
        return "Prince" + colour + ".png";
    case Lion:
        return promo + "Lion" + colour + ".png";
    case Queen:
        return promo + "FreeKing" + colour + ".png";
    case DragonKing:
        return promo + "Dragon" + colour + ".png";
    case DragonHorse:
        return promo + "Horse" + colour + ".png";
    case Rook:
        return promo + "Rook" + colour + ".png";
    case Bishop:
        return promo + "Bishop" + colour + ".png";
    case VerticalMover:
        return promo + "Vertical" + colour + ".png";
    case SideMover:
        return promo + "Side" + colour + ".png";
    case ReverseChariot:
        return "Reverse" + colour + ".png";
    case Lance:
        return "Lance" + colour + ".png";
    case Kylin:
        return "Kylin" + colour + ".png";
    case Phoenix:
        return "Phoenix" + colour + ".png";
    case Elephant:
        return promo + "Elephant" + colour + ".png";
    case Tiger:
        return "Tiger" + colour + ".png";
    case Leopard:
        return "Leopard" + colour + ".png";
    case Gold:
        return "Gold" + colour + ".png";
    case Silver:
        return "Silver" + colour + ".png";
    case Copper:
        return "Copper" + colour + ".png";
    case GoBetween:
        return "GoBetween" + colour + ".png";
    case Eagle:
        return "Eagle" + colour + ".png";
    case Unicorn:
        return "Falcon" + colour + ".png";
    case FlyingStag:
        return "Stag" + colour + ".png";
    case FreeBoar:
        return "Boar" + colour + ".png";
    case FlyingOx:
        return "Ox" + colour + ".png";
    case WhiteHorse:
        return "WHorse" + colour + ".png";
    case Whale:
        return "Whale" + colour + ".png";
    case Tokin:
        return "Tokin" + colour + ".png";
    case Pawn:
        return "Pawn" + colour + ".png";
    case ViceGeneral:
        return "ViceGeneral" + colour + ".png";
    case GreatGeneral:
        return "GreatGeneral" + colour + ".png";
    case BishopGeneral:
        return promo + "BishopGeneral" + colour + ".png";
    case RookGeneral:
        return promo + "RookGeneral" + colour + ".png";
    case MultiGeneral:
        return "Multi-General" + colour + "2.png";
    case Dog:
        return promo + "Dog" + colour + ".png";
    case FreeEagle:
        return "FreeEagle" + colour + ".png";
    case LionHawk:
        return "Lion-Hawk" + colour + ".png";
    case SideSoldier:
        return promo + "SideSoldier" + colour + ".png";
    case VerticalSoldier:
        return promo + "VerticalSoldier" + colour + ".png";
    case ChariotSoldier:
        return promo + "ChariotSoldier" + colour + ".png";
    case WaterBuffalo:
        return promo + "WaterBuffalo" + colour + ".png";
    case HeavenlyTetrarch:
        return "Heaven" + colour + ".png";
    case FireDemon:
        return "FireDemon" + colour + ".png";
    case Knight:
        return "Knight" + colour + ".png";
    case Iron:
        return "Iron" + colour + ".png";
    default:
        return "";
    }
}

QString GraphicsManager::GetKanjiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    QString colour = pieceColour == White ? "" : "Flip";
    if (isPromoted && pieceType != King)
    {
        colour = "P" + colour;
    }
    switch (pieceType)
    {
    case King:
        return "King" + colour + ".png";
    case Prince:
        return "Prince" + colour + ".png";
    case Lion:
        return "Lion" + colour + ".png";
    case Queen:
        return "Queen" + colour + ".png";
    case DragonKing:
        return "DragonKing" + colour + ".png";
    case DragonHorse:
        return "DragonHorse" + colour + ".png";
    case Rook:
        return "Rook" + colour + ".png";
    case Bishop:
        return "Bishop" + colour + ".png";
    case VerticalMover:
        return "VerticalMover" + colour + ".png";
    case SideMover:
        return "SideMover" + colour + ".png";
    case ReverseChariot:
        return "Chariot" + colour + ".png";
    case Lance:
        return "Lance" + colour + ".png";
    case Kylin:
        return "Kirin" + colour + ".png";
    case Phoenix:
        return "Phoenix" + colour + ".png";
    case Elephant:
        return "Elephant" + colour + ".png";
    case Tiger:
        return "Tiger" + colour + ".png";
    case Gold:
    case Tokin:
        return "Gold" + colour + ".png";
    case Silver:
        return "Silver" + colour + ".png";
    case Copper:
        return "Copper" + colour + ".png";
    case Leopard:
        return "Leopard" + colour + ".png";
    case GoBetween:
        return "GoBetween" + colour + ".png";
    case Pawn:
        return "Pawn" + colour + ".png";
    case Eagle:
        return "Eagle" + colour + ".png";
    case Unicorn:
        return "Hawk" + colour + ".png";
    case FlyingOx:
        return "FlyingOx" + colour + ".png";
    case FreeBoar:
        return "FreeBoar" + colour + ".png";
    case FlyingStag:
        return "Stag" + colour + ".png";
    case WhiteHorse:
        return "White" + colour + ".png";
    case Whale:
        return "Whale" + colour + ".png";
    case Knight:
        return "Knight" + colour + ".png";
    case ViolentOx:
        return "ViolentOx" + colour + ".png";
    case FlyingDragon:
        return "FlyingDragon" + colour + ".png";
    case AngryBoar:
        return "AngryBoar" + colour + ".png";
    case CatSword:
        return "Cat" + colour + ".png";
    case EvilWolf:
        return "Wolf" + colour + ".png";
    case Iron:
        return "Iron" + colour + ".png";
    case Stone:
        return "Stone" + colour + ".png";
    case ViceGeneral:
        return "Vice" + colour + ".png";
    case GreatGeneral:
        return "Great" + colour + ".png";
    case BishopGeneral:
        return "BishopGeneral" + colour + ".png";
    case RookGeneral:
        return "RookGeneral" + colour + ".png";
    case MultiGeneral:
        return "Multi" + colour + ".png";
    case Dog:
        return "Dog" + colour + ".png";
    case FreeEagle:
        return "FreeEagle" + colour + ".png";
    case LionHawk:
        return "LionHawk" + colour + ".png";
    case SideSoldier:
        return "SideSoldier" + colour + ".png";
    case VerticalSoldier:
        return "VerticalSoldier" + colour + ".png";
    case ChariotSoldier:
        return "ChariotSoldier" + colour + ".png";
    case WaterBuffalo:
        return "WaterBuffalo" + colour + ".png";
    case HeavenlyTetrarch:
        return "HeavenlyTetrarch" + colour + ".png";
    case FireDemon:
        return "FireDemon" + colour + ".png";
    default:
        return "";
    }
}

QString GraphicsManager::GetKanjiImageFileName2(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    QString colour = pieceColour == White ? "_piece_B_" : "_piece_W_";
    colour += isPromoted ? "prom" : "norm";
    switch (pieceType)
    {
    case King:
        return "Korol" + colour + ".png";
    case Prince:
        return "Kronprinc" + colour + ".png";
    case Lion:
        return "Lev" + colour + ".png";
    case Queen:
        return "Ferz" + colour + ".png";
    case DragonKing:
        return "Car_Drakon" + colour + ".png";
    case DragonHorse:
        return "Loshad" + colour + ".png";
    case Rook:
        return "Ladja" + colour + ".png";
    case Bishop:
        return "Slon" + colour + ".png";
    case VerticalMover:
        return "Vertikalnyj_hodok" + colour + ".png";
    case SideMover:
        return "Gorizontalnyj_hodok" + colour + ".png";
    case ReverseChariot:
        return "Kontrstrelka" + colour + ".png";
    case Lance:
        return "Strelka" + colour + ".png";
    case Kylin:
        return "Edinorog" + colour + ".png";
    case Phoenix:
        return "Feniks" + colour + ".png";
    case Elephant:
        return "Pjanyj_slon" + colour + ".png";
    case Tiger:
        return "Slepoj_tigr" + colour + ".png";
    case Gold:
        return "Zolotoj_general" + colour + ".png";
    case Tokin:
        return "Tokin" + colour + ".png";
    case Silver:
        return "Serebrjanyj_general" + colour + ".png";
    case Copper:
        return "Mednyj_general" + colour + ".png";
    case Leopard:
        return "JArostnyj_leopard" + colour + ".png";
    case GoBetween:
        return "Posrednik" + colour + ".png";
    case Pawn:
        return "Peshka" + colour + ".png";
    case Eagle:
        return "Parjashij_orjol" + colour + ".png";
    case Unicorn:
        return "Rogatyj_sokol" + colour + ".png";
    case FlyingOx:
        return "Letajushij_byk" + colour + ".png";
    case FreeBoar:
        return "Begajushij_vepr" + colour + ".png";
    case FlyingStag:
        return "Letajushij_olen" + colour + ".png";
    case WhiteHorse:
        return "Belyj_kon" + colour + ".png";
    case Whale:
        return "Kit" + colour + ".png";
    case Knight:
        return "Kon" + colour + ".png";
    case ViolentOx:
        return "Silnyj_byk" + colour + ".png";
    case FlyingDragon:
        return "Letajushij_drakon" + colour + ".png";
    case AngryBoar:
        return "Dikij_kaban" + colour + ".png";
    case CatSword:
        return "Koshachij_mech" + colour + ".png";
    case EvilWolf:
        return "Zloj_Volk" + colour + ".png";
    case Iron:
        return "ZHeleznyj_general" + colour + ".png";
    case Stone:
        return "Kamennyj_general" + colour + ".png";
    case Tile:
        return "Plitochnyj_general" + colour + ".png";
    case Earth:
        return "Zemljanoj_general" + colour + ".png";
    case Guardian:
        return "Almaz" + colour + ".png";
    case Yaksha:
        return "Djavolica" + colour + ".png";
    case FreeSerpent:
        return "Svobodnaja_zmeja" + colour + ".png";
    case FreeGo:
        return "Svobodnyj_hodok" + colour + ".png";
    case Emperor:
        return "Imperator" + colour + ".png";
    case Deva:
        return "Deva" + colour + ".png";
    case DarkSpirit:
        return "Duh_nevezhestva" + colour + ".png";
    case TeachingKing:
        return "Uchebnyj_korol" + colour + ".png";
    case BuddhistSpirit:
        return "Buddijskij_duh" + colour + ".png";
    case FreeGold:
        return "Svobodnoe_zoloto" + colour + ".png";
    case FreeSilver:
        return "Svobodnoe_serebro" + colour + ".png";
    case FreeCopper:
        return "Svobodnaja_med" + colour + ".png";
    case FreeIron:
        return "Svobodnoe_zhelezo" + colour + ".png";
    case FreeTile:
        return "Svobodnaja_plitka" + colour + ".png";
    case FreeStone:
        return "Svobodnyj_kamen" + colour + ".png";
    case FreeEarth:
        return "Svobodnaja_zemlja" + colour + ".png";
    case FreeTiger:
        return "Svobodnyj_tigr" + colour + ".png";
    case FreeLeopard:
        return "Svobodnyj_leopard" + colour + ".png";
    case CoiledSerpent:
        return "Svernuvshajasja_zmeja" + colour + ".png";
    case RecliningDragon:
        return "Lezhashij_drakon" + colour + ".png";
    case FreeDragon:
        return "Svobodnyj_drakon" + colour + ".png";
    case OldMonkey:
        return "Staraja_obezjana" + colour + ".png";
    case MountainWitch:
        return "Gornaja_vedma" + colour + ".png";
    case ChineseCock:
        return "Kitajskij_petuh" + colour + ".png";
    case WizardStork:
        return "Volshebnyj_aist" + colour + ".png";
    case FreeCat:
        return "Svobodnaja_koshka" + colour + ".png";
    case FuriousFiend:
        return "JArostnoe_porozhdenie" + colour + ".png";
    case GoldenBird:
        return "Zolotoe_krylo" + colour + ".png";
    case GreatDragon:
        return "Velikij_drakon" + colour + ".png";
    case FreeWolf:
        return "Svobodnyj_volk" + colour + ".png";
    case FreeBear:
        return "Svobodnyj_medved" + colour + ".png";
    case OldRat:
        return "Staraja_krysa" + colour + ".png";
    case Bat:
        return "Letuchaja_mysh" + colour + ".png";
    case LionDog:
        return "Lvinaja_sobaka" + colour + ".png";
    case Wrestler:
        return "Borec" + colour + ".png";
    case BuddhistDevil:
        return "Demon" + colour + ".png";
    case Donkey:
        return "Osjol" + colour + ".png";
    case Capricorn:
        return "Kozerog" + colour + ".png";
    case HookMover:
        return "Krjukovoj_hodok" + colour + ".png";
    case LeftChariot:
        return "Levaja_kolesnica" + colour + ".png";
    case RightChariot:
        return "Pravaja_kolesnica" + colour + ".png";
    case SideFlier:
        return "Gorizontalnyj_letun" + colour + ".png";
    case BlindBear:
        return "Slepoj_medved" + colour + ".png";
    case PromotedLance:
        return "Perevernutaja_strelka" + colour + ".png";
    case PromotedKnight:
        return "Perevernutyj_vsadnik" + colour + ".png";
    case PromotedSilver:
        return "Perevernutyj_serebrjanyj_general" + colour + ".png";
    default:
        return "";
    }
}

QString GraphicsManager::GetKanjiImageFileName3(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    QString colour = pieceColour == White ? "" : "Flip";
    if (isPromoted && pieceType != King && pieceType != Queen && pieceType != DragonKing && pieceType != DragonHorse)
    {
        colour = "P" + colour;
    }
    switch (pieceType)
    {
    case Gold:
    case Silver:
    case Copper:
    case Iron:
    case Tile:
    case Stone:
    case Earth:
        return QString::fromStdString(StringManager::PieceType2Description(DaiDaiShogi, pieceType)) + "General" + colour + ".png";
    case Leopard:
        return "FerociousLeopard" + colour + ".png";
    case Tiger:
        return "BlindTiger" + colour + ".png";
    case Elephant:
        return "DrunkElephant" + colour + ".png";
    case Kylin:
        return "Kirin" + colour + ".png";
    case Guardian:
        return "GuardianGod" + colour + ".png";
    case Yaksha:
        return "SheDevil" + colour + ".png";
    case FreeSerpent:
        return "FreeSnake" + colour + ".png";
    case FreeGo:
        return "FreeGoBetween" + colour + ".png";
    case Tengu:
        return "LongNosedGoblin" + colour + ".png";
    case RacingChariot:
        return "SideChariot" + colour + ".png";
    case NeighboringKing:
        return "NeighborKing" + colour + ".png";
    case Wood:
        return "WoodGeneral" + colour + ".png";
    default:
        QString desc = QString::fromStdString(StringManager::PieceType2Description(DaiDaiShogi, pieceType));
        desc.replace(" ", "");
        return desc + colour + ".png";
    }
}

QString GraphicsManager::GetTenjikuShogiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    const QString colour = pieceColour == White ? "_B" : "_W";
    const QString promo = isPromoted ? "P" : "";
    switch (pieceType)
    {
    case Queen:
        return promo + "Queen" + colour + ".png";
    case Tokin:
        return promo + "Gold" + colour + ".png";
    case FreeBoar:
        return "FBoar" + colour + ".png";
    case FlyingOx:
        return "pOx" + colour + ".png";
    default:
        return GetMnemonicImageFileName(pieceColour, pieceType, isPromoted);
    }
}


QString GraphicsManager::GetKoShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    if (pieceStyle == European)
    {
        QString colour = pieceColour == White ? "w" : "b";
        switch (pieceType)
        {
        case King:           return colour + "g" + ".png";
        case Prince:         return colour + "go" + ".png";
        case Queen:          return colour + "m" + ".png";
        case Rook:           return colour + "cu" + ".png";
        case Bishop:         return colour + "e" + ".png";
        case Gold:           return colour + "a" + ".png";
        case Silver:         return colour + "s" + ".png";
        case Copper:         return colour + "en" + ".png";
        case FlyingOx:       return colour + "co" + ".png";
        case FreeBoar:       return colour + "ib" + ".png";
        case VerticalMover:  return colour + "pu" + ".png";
        case DragonHorse:    return colour + "cr" + ".png";
        case DragonKing:     return colour + "q" + ".png";
        case CatSword:       return colour + "sh" + ".png";
        case Leopard:        return colour + "cs" + ".png";
        case FlyingStag:     return colour + "tb" + ".png";
        case Tiger:          return colour + "sn" + ".png";
        case Elephant:       return colour + "ac" + ".png";
        case Phoenix:        return colour + "so" + ".png";
        case Kylin:          return colour + "cl" + ".png";
        case Knight:         return colour + "hs" + ".png";
        case Pawn:           return colour + "p" + ".png";
        case MiddleTroop:          return colour + "mt" + ".png";
        case Drum:                 return colour + "d" + ".png";
        case Thunderclap:          return colour + "tc" + ".png";
        case Flag:                 return colour + "b" + ".png";
        case RoamingAssault:       return colour + "ra" + ".png";
        case CompanyCommander:     return colour + "vb" + ".png";
        case ViceCommissioner:     return colour + "vc" + ".png";
        case PoisonFlame:          return colour + "pf" + ".png";
        case Lion:                 return colour + "wr" + ".png";
        case DoubleKylin:          return colour + "ma" + ".png";
        case DoublePhoenix:        return colour + "bd" + ".png";
        case TaoistPriest:         return colour + "tp" + ".png";
        case SpiritualMonk:        return colour + "sm" + ".png";
        case ExtensiveFog:         return colour + "tf" + ".png";
        case HolyLight:			   return colour + "il" + ".png";
        case AdvanceGuard:         return colour + "ag" + ".png";
        case RearGuard:            return colour + "rg" + ".png";
        case SkywardNet:           return colour + "hv" + ".png";
        case EarthwardNet:         return colour + "ev" + ".png";
        case RisingDragon:         return colour + "da" + ".png";
        case WingedTiger:          return colour + "tw" + ".png";
        case FlyingHawk:           return colour + "wh" + ".png";
        case Longbow:              return colour + "lb" + ".png";
        case LongbowKnight:        return colour + "lc" + ".png";
        case Crossbow:             return colour + "sb" + ".png";
        case CrossbowKnight:       return colour + "sc" + ".png";
        case Cannon:               return colour + "c" + ".png";
        case CannonCarriage:       return colour + "gc" + ".png";
        case FrankishCannon:       return colour + "ec" + ".png";
        case DivineCarriage:       return colour + "cg" + ".png";
        case KnightCaptain:        return colour + "ca" + ".png";
        case WingedHorse:          return colour + "wg" + ".png";
        case ShieldCaptain:        return colour + "su" + ".png";
        case Chariot:              return colour + "ch" + ".png";
        case Vanguard:             return colour + "v" + ".png";
        default: return "";
        }
    }
    else if (pieceStyle == Asian || pieceStyle == Mnemonic)
    {
        QString colour = pieceColour == White ? "F" : "";
        if (isPromoted && pieceType != King && pieceType != Lion && pieceType != Bishop)
        {
            colour = "P" + colour;
        }
        switch (pieceType)
        {
        case Rook:
            return "ChariotCaptain" + colour + ".png";
        case VerticalMover:
            return "PawnCaptain" + colour + ".png";
        case Knight:
            return "Knight" + colour + ".png";
        case FrankishCannon:
            return "EuropeanCannon" + colour + ".png";
        case Copper:
            return "MilitaryEngineer" + colour + ".png";
        case Queen:
            return "Chiliarch" + colour + ".png";
        case Leopard:
            return "MilitaryOfficer" + colour + ".png";
        case DragonKing:
            return "Optio" + colour + ".png";
        case Elephant:
            return "Guard" + colour + ".png";
        case SkywardNet:
            return "SkyNet" + colour + ".png";
        case EarthwardNet:
            return "EarthNet" + colour + ".png";
        case FlyingStag:
            return "BattalionCommander" + colour + ".png";
        case DoubleKylin:
            return "Strategist" + colour + ".png";
        case DoublePhoenix:
            return "Flag-Drum" + colour + ".png";
        case FlyingOx:
            return "MilitaryCommissioner" + colour + ".png";
        case FreeBoar:
            return "ImperialBase" + colour + ".png";
        case Prince:
            return "Marshal" + colour + ".png";
        case Lion:
            return "Wrestler" + colour + ".png";
        default:
            QString desc = QString::fromStdString(StringManager::PieceType2Description(KoShogi, pieceType));
            desc.replace(" ", "");
            return desc + colour + ".png";
        }
    }
    else
    {
        QString colour = pieceColour == White ? "kw" : "kb";
        switch (pieceType)
        {
        case King:           return colour + "g" + ".png";
        case Prince:         return colour + "go" + ".png";
        case Queen:          return colour + (isPromoted ? "mm" : "m") + ".png";
        case Rook:           return colour + (isPromoted ? "cc" : "cu") + ".png";
        case Bishop:         return colour + "e" + ".png";
        case Gold:           return colour + "a" + ".png";
        case Silver:         return colour + "s" + ".png";
        case Copper:         return colour + "en" + ".png";
        case FlyingOx:       return colour + "co" + ".png";
        case FreeBoar:       return colour + "ib" + ".png";
        case VerticalMover:  return colour + (isPromoted ? "pp" : "pu") + ".png";
        case DragonHorse:    return colour + (isPromoted ? "ss" : "cr") + ".png";
        case DragonKing:     return colour + (isPromoted ? "aa" : "q") + ".png";
        case CatSword:       return colour + "sh" + ".png";
        case Leopard:        return colour + "cs" + ".png";
        case FlyingStag:     return colour + "tb" + ".png";
        case Tiger:          return colour + "sn" + ".png";
        case Elephant:       return colour + "ac" + ".png";
        case Phoenix:        return colour + "so" + ".png";
        case Kylin:          return colour + "cl" + ".png";
        case Knight:         return colour + "hs" + ".png";
        case Pawn:           return colour + "p" + ".png";
        case MiddleTroop:          return colour + "mt" + ".png";
        case Drum:                 return colour + "d" + ".png";
        case Thunderclap:          return colour + "tc" + ".png";
        case Flag:                 return colour + "b" + ".png";
        case RoamingAssault:       return colour + "ra" + ".png";
        case CompanyCommander:     return colour + "vb" + ".png";
        case ViceCommissioner:     return colour + "vc" + ".png";
        case PoisonFlame:          return colour + "pf" + ".png";
        case Lion:                 return colour + "wr" + ".png";
        case DoubleKylin:          return colour + "ma" + ".png";
        case DoublePhoenix:        return colour + "bd" + ".png";
        case TaoistPriest:         return colour + "tp" + ".png";
        case SpiritualMonk:        return colour + "sm" + ".png";
        case ExtensiveFog:         return colour + "tf" + ".png";
        case HolyLight:			   return colour + "il" + ".png";
        case AdvanceGuard:         return colour + "ag" + ".png";
        case RearGuard:            return colour + "rg" + ".png";
        case SkywardNet:           return colour + "hv" + ".png";
        case EarthwardNet:         return colour + "ev" + ".png";
        case RisingDragon:         return colour + "da" + ".png";
        case WingedTiger:          return colour + "tw" + ".png";
        case FlyingHawk:           return colour + "wh" + ".png";
        case Longbow:              return colour + "lb" + ".png";
        case LongbowKnight:        return colour + "lc" + ".png";
        case Crossbow:             return colour + "sb" + ".png";
        case CrossbowKnight:       return colour + "sc" + ".png";
        case Cannon:               return colour + "c" + ".png";
        case CannonCarriage:       return colour + "gc" + ".png";
        case FrankishCannon:       return colour + "ec" + ".png";
        case DivineCarriage:       return colour + "cg" + ".png";
        case KnightCaptain:        return colour + (isPromoted ? "hh" : "ca") + ".png";
        case WingedHorse:          return colour + "wg" + ".png";
        case ShieldCaptain:        return colour + (isPromoted ? "uu" : "su") + ".png";
        case Chariot:              return colour + "ch" + ".png";
        case Vanguard:             return colour + "v" + ".png";
        default: return "";
        }
    }
}

QString GraphicsManager::GetKyotoShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType)
{
    const QString colour = pieceColour == White ? "B" : "W";
    if (pieceStyle == European)
    {
        switch (pieceType)
        {
        case King:
            return "King_I" + colour + ".png";
        case Rook:
            return "Rook_I" + colour + ".png";
        case Bishop:
            return "Bishop_I" + colour + ".png";
        case Lance:
            return "Lance_I" + colour + ".png";
        case Gold:
            return "Gold_I" + colour + ".png";
        case Tokin:
            return "Tokin_I" + colour + ".png";
        case Silver:
            return "Silver_I" + colour + ".png";
        case Pawn:
            return "Pawn_I" + colour + ".png";
        case Knight:
            return "Knight_I" + colour + ".png";
        default:
            return "";
        }
    }
    else if (pieceStyle == Mnemonic)
    {
        switch (pieceType)
        {
        case King:
            return "King_F" + colour + ".png";
        case Rook:
            return "Rook_F" + colour + ".png";
        case Bishop:
            return "Bishop_F" + colour + ".png";
        case Lance:
            return "Lance_F" + colour + ".png";
        case Gold:
            return "Gold_F" + colour + ".png";
        case Tokin:
            return "Tokin_F" + colour + ".png";
        case Silver:
            return "Silver_F" + colour + ".png";
        case Pawn:
            return "Pawn_F" + colour + ".png";
        case Knight:
            return "Knight_F" + colour + ".png";
        default:
            return "";
        }
    }
    else
    {
        switch (pieceType)
        {
        case King:
            return "King_" + colour + ".png";
        case Rook:
            return "Rook_" + colour + ".png";
        case Bishop:
            return "Bishop_" + colour + ".png";
        case Lance:
            return "Lance_" + colour + ".png";
        case Gold:
            return "Gold_" + colour + ".png";
        case Tokin:
            return "Tokin_" + colour + ".png";
        case Silver:
            return "Silver_" + colour + ".png";
        case Pawn:
            return "Pawn_" + colour + ".png";
        case Knight:
            return "Knight_" + colour + ".png";
        default:
            return "";
        }
    }
}

QString GraphicsManager::GetWaShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    if (pieceStyle == European || pieceStyle == Mnemonic)
    {
        QString colour = pieceColour == White ? "B" : "W";
        if (isPromoted && (pieceType == CloudEagle || pieceType == FlyingFalcon || pieceType == Rook
            || pieceType == SideMover || pieceType == Gold || pieceType == Silver || pieceType == TreacherousFox))
        {
            colour += "+";
        }
        switch (pieceType)
        {
        case King:
            return colour + "craneking.png";
        case Rook:
            return colour + "GlidingSwallow.png";
        case Lance:
            return colour + "oxcart.png";
        case Tokin:
            return colour + "GoldenBird.png";
        case Pawn:
            return colour + "SparrowPawn.png";
        case SideMover:
            return colour + "Swallowswings.png";
        case PloddingOx:
            return colour + "PloddingOx.png";
        case LiberatedHorse:
            return colour + "LiberatedHorse.png";
        case HeavenlyHorse:
            return colour + "HeavenlyHorse.png";
        case SwoopingOwl:
            return colour + "SwoopingOwl.png";
        case CloudEagle:
            return colour + "CloudEagle.png";
        case StruttingCrow:
            return colour + "StruttingCrow.png";
        case FlyingFalcon:
            return colour + "FlyingFalcon.png";
        case FlyingCock:
            return colour + "FlyingCockerel.png";
        case RaidingFalcon:
            return colour + "RaidingFalcon.png";
        case FlyingGoose:
            return colour + "FlyingGoose.png";
        case ClimbingMonkey:
            return colour + "ClimbingMonkey.png";
        case Silver:
            return colour + "ViolentStag.png";
        case Dog:
            return colour + "Blinddog.png";
        case Gold:
            return colour + "ViolentWolf.png";
        case Elephant:
            return colour + "RoamingBoar.png";
        case BearEyes:
            return colour + "BearEyes.png";
        case RunningRabbit:
            return colour + "RunningRabbit.png";
        case TreacherousFox:
            return colour + "TreacherousFox.png";
        case TenaciousFalcon:
            return colour + "TenaciousFalcon.png";
        default:
            return "";
        }
    }
    else
    {
        QString colour = pieceColour == White ? "" : "Flip";
        if (isPromoted && pieceType != King)
        {
            colour = "P" + colour;
        }
        switch (pieceType)
        {
        case King:
            return "CraneKing" + colour + ".png";
        case Rook:
            return "GlidingSwallow" + colour + ".png";
        case Lance:
            return "OxCart" + colour + ".png";
        case Tokin:
            return "GoldenBird" + colour + ".png";
        case Pawn:
            return "SparrowPawn" + colour + ".png";
        case SideMover:
            return "SwallowWing" + colour + ".png";
        case PloddingOx:
            return "PloddingOx" + colour + ".png";
        case LiberatedHorse:
            return "LiberatedHorse" + colour + ".png";
        case HeavenlyHorse:
            return "HeavenlyHorse" + colour + ".png";
        case SwoopingOwl:
            return "SwoopingKite" + colour + ".png";
        case CloudEagle:
            return "CloudEagle" + colour + ".png";
        case StruttingCrow:
            return "StruttingCrow" + colour + ".png";
        case FlyingFalcon:
            return "FlyingHawk" + colour + ".png";
        case FlyingCock:
            return "FlyingCock" + colour + ".png";
        case RaidingFalcon:
            return "RaidingHawk" + colour + ".png";
        case FlyingGoose:
            return "FlyingGoose" + colour + ".png";
        case ClimbingMonkey:
            return "ClimbingMonkey" + colour + ".png";
        case Silver:
            return "ViolentStag" + colour + ".png";
        case Dog:
            return "BlindDog" + colour + ".png";
        case Gold:
            return "ViolentWolf" + colour + ".png";
        case Elephant:
            return "RoamingBoar" + colour + ".png";
        case BearEyes:
            return "BearEye" + colour + ".png";
        case RunningRabbit:
            return "RunningRabbit" + colour + ".png";
        case TreacherousFox:
            return "TreacherousFox" + colour + ".png";
        case TenaciousFalcon:
            return "TenaciousHawk" + colour + ".png";
        default:
            return "";
        }
    }
}

QString GraphicsManager::GetToriShogiImageFileName(PieceStyle pieceStyle, PieceColour pieceColour, PieceType pieceType)
{
    if (pieceStyle == European || pieceStyle == Mnemonic)
    {
        QString colour = pieceColour == White ? "B" : "W";
        switch (pieceType)
        {
        case King:
            return colour + "Phoenix.png";
        case Falcon:
            return colour + "Falcon.png";
        case Eagle:
            return colour + "Eagle.png";
        case Crane:
            return colour + "Crane.png";
        case Pheasant:
            return colour + "Pheasant.png";
        case LeftQuail:
            return colour + "LQuail.png";
        case RightQuail:
            return colour + "RQuail.png";
        case Pawn:
            return colour + "Swallow.png";
        case Goose:
            return colour + "Goose.png";
        default:
            return "";
        }
    }
    else if (pieceStyle == Asian)
    {
        QString colour = pieceColour == White ? "B" : "W";
        switch (pieceType)
        {
        case King:
            return colour + "PhoenixJ.png";
        case Falcon:
            return colour + "FalconJ.png";
        case Eagle:
            return colour + "EagleJ.png";
        case Crane:
            return colour + "CraneJ.png";
        case Pheasant:
            return colour + "PheasantJ.png";
        case LeftQuail:
            return colour + "LQuailJ.png";
        case RightQuail:
            return colour + "RQuailJ.png";
        case Pawn:
            return colour + "SwallowJ.png";
        case Goose:
            return colour + "GooseJ.png";
        default:
            return "";
        }
    }
    else
    {
        QString colour = pieceColour == White ? "" : "Flip";
        switch (pieceType)
        {
        case King:
            return "DaPeng" + colour + ".png";
        case Falcon:
            return "Hawk" + colour + ".png";
        case Eagle:
            return "MountainHawkP" + colour + ".png";
        case Crane:
            return "Crane" + colour + ".png";
        case Pheasant:
            return "Pheasant" + colour + ".png";
        case LeftQuail:
            return "L-Quail" + colour + ".png";
        case RightQuail:
            return "R-Quail" + colour + ".png";
        case Pawn:
            return "Swallow" + colour + ".png";
        case Goose:
            return "WildGooseP" + colour + ".png";
        default:
            return "";
        }
    }
}

QString GraphicsManager::GetSittuyinImageFileName(PieceColour pieceColour, PieceType pieceType)
{
    QString colour = pieceColour == White ? "t_w" : "t_b";
    switch (pieceType)
    {
    case King:
        return colour + "k.png";
    case Rook:
        return colour + "r.png";
    case Knight:
        return colour + "h.png";
    case Bishop:
        return colour + "e.png";
    case Queen:
        return colour + "g.png";
    case Pawn:
        return colour + "p.png";
    default:
        return "";
    }
}
