#include "graphicsmanager.h"

void GraphicsManager::DrawPiece(QPainter& painter, Piece *p, GameVariant gameVariant, PieceStyle pieceStyle, int w, int h, int i, int j)
{
    bool isAsianStyle = pieceStyle == Asian || pieceStyle == Asian2 || pieceStyle == Asian3 || pieceStyle == Asian4;
    QPixmap pixmap(GraphicsManager::GetImageFileName(gameVariant, pieceStyle, p));
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
    case CourierChess:
    case ChancellorChess:
    case ModernChess:
    case GrandeAcedrex:
        painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        break;
    case Makruk:
        if (pieceStyle == European)
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 10, j * h + h / 10, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        break;
    case Chess:
    case Shatranj:
    case Shatar:
        if (pieceStyle == European)
        {
            painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else if (pieceStyle == Mnemonic)
        {
            painter.drawPixmap(i * w + w / 10, j * h + h / 10, pixmap.size().width(), pixmap.size().height(), pixmap);
        }
        else
        {
            painter.drawPixmap(i * w + w / 20, j * h, pixmap.size().width(), pixmap.size().height(), pixmap);
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
        else if (pieceStyle == Mnemonic) return ":/pieces_xia/images_xia/";
        else if (pieceStyle == Asian) return ":/pieces_chi/images_chi/";
        else return ":/pieces_chi2/images_chi2/";
        break;
    case MicroShogi:
    case KyotoShogi:
        return ":/pieces_kyo/images_kyo/";
        break;
    case Shogi:
    case ShoShogi:
    case MiniShogi:
    case JudkinShogi:
    case EuroShogi:
        if (pieceStyle == European) return ":/pieces_eur/images/";
        else if (pieceStyle == Mnemonic) return ":/pieces_sho2/images_sho2/";
        else if (pieceStyle == Asian) return ":/pieces_sho/images_sho/";
        else if (pieceStyle == Asian2) return ":/pieces_sho3/images_sho3/";
        else return ":/pieces_maka2/images_maka2/";
        break;
    case WhaleShogi:
        return ":/pieces_wha/images_wha/";
        break;
    case ToriShogi:
        if (pieceStyle == European || pieceStyle == Asian) return ":/pieces_tori/images_tori/";
        else if (pieceStyle == Mnemonic) return ":/pieces_torim/images_torim/";
        else return ":/pieces_torik/images_torik/";
        break;
    case YariShogi:
        if (pieceStyle == European) return ":/pieces_yam/images_yam/";
        else if (pieceStyle == Mnemonic) return ":/pieces_ptg/images_ptg/";
        else return ":/pieces_yak/images_yak/";
        break;
    case ChuShogi:
        if (pieceStyle == Asian) return ":/pieces_tnk/images_tnk/";
        else if (pieceStyle == Asian2) return ":/pieces_maka2/images_maka2/";
        else if (pieceStyle == Asian3) return ":/pieces_knj/images_knj/";
        else if (pieceStyle == Asian4) return ":/pieces_jap/images_jap/";
        else if (pieceStyle == Mnemonic) return ":/pieces_chu/images_chu/";
        else return ":/pieces_eur/images/";
        break;
    case DaiShogi:
    case HeianShogi:
    case HeianDaiShogi:
        if (pieceStyle == Asian) return ":/pieces_tnk/images_tnk/";
        else if (pieceStyle == Asian2 || pieceStyle == Asian4) return ":/pieces_maka2/images_maka2/";
        else if (pieceStyle == Asian3) return ":/pieces_dai/images_dai/";
        else return ":/pieces_eur/images/";
        break;
    case TenjikuShogi:
        return isAsianStyle ? ":/pieces_tnk/images_tnk/" : ":/pieces_ten/images_ten/";
        break;
    case WaShogi:
    case CrazyWa:
        return isAsianStyle ? ":/pieces_wa2/images_wa2/" : ":/pieces_wa/images_wa/";
        break;
    case DaiDaiShogi:
        return ":/pieces_dd/images_daidai/";
        break;
    case MakaDaiDaiShogi:
        return pieceStyle == Asian ? ":/pieces_mdd/images_maka/" : ":/pieces_maka2/images_maka2/";
        break;
    case KoShogi:
        if (pieceStyle == Asian) return ":/pieces_ko/images_ko/";
        else if (isAsianStyle) return ":/pieces_kok/images_kok/";
        else if (pieceStyle == Mnemonic) return ":/pieces_km/images_kom/";
        else return ":/pieces_kow/images_kow/";
        break;
    case Chess:
    case Shatranj:
    case Shatar:
        if (pieceStyle == European) return ":/pieces_eur/images/";
        else if (pieceStyle == Mnemonic) return ":/pieces_eur/images_eur/";
        else return ":/pieces_eur2/images_eur2/";
        break;
    case Makruk:
        if (pieceStyle == European) return ":/pieces_eur/images/";
        else return ":/pieces_mak/images_mak/";
        break;
    case CapablancaChess:
    case GothicChess:
    case JanusChess:
    case GrandChess:
    case OmegaChess:
    case CourierChess:
    case ChancellorChess:
    case ModernChess:
    case GrandeAcedrex:
        return ":/pieces_eur/images/";
    default:
        return "";
    }
}

QString GraphicsManager::GetImageFileName(GameVariant gameVariant, PieceStyle pieceStyle, Piece *p)
{
    bool isAsianStyle = pieceStyle == Asian || pieceStyle == Asian2 || pieceStyle == Asian3 || pieceStyle == Asian4;
    std::string imageFileName;
    switch (gameVariant)
    {
    case Xiangqi:
    case Janggi:
        imageFileName = pieceStyle == European ?
            p->GetImageFileName() : dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
        break;
    case MicroShogi:
    case KyotoShogi:
        if (pieceStyle == European) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
        else if (pieceStyle == Mnemonic) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
        else imageFileName = p->GetImageFileName();
        break;
    case Shogi:
    case ShoShogi:
    case MiniShogi:
    case JudkinShogi:
    case EuroShogi:
        if (pieceStyle == Mnemonic || pieceStyle == Asian || pieceStyle == Asian2) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
        else if (pieceStyle == Asian3 || pieceStyle == Asian4) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
        else imageFileName = p->GetImageFileName();
        break;
    case WhaleShogi:
        if (pieceStyle == European) imageFileName = p->GetImageFileName();
        else imageFileName = "L" + p->GetImageFileName();
        break;
    case ToriShogi:
        if (pieceStyle == European) imageFileName = p->GetImageFileName();
        else if (pieceStyle == Asian) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
        else imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
        break;
    case YariShogi:
        imageFileName = p->GetImageFileName();
        break;
    case DaiShogi:
    case HeianShogi:
    case HeianDaiShogi:
        if (pieceStyle == Asian) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
        else if (pieceStyle == Asian2 || pieceStyle == Asian4) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
        else imageFileName = p->GetImageFileName();
        break;
    case MakaDaiDaiShogi:
        imageFileName = pieceStyle == Asian ?
            dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName() : dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
        break;
    case KoShogi:
        imageFileName = pieceStyle == Asian || pieceStyle == Mnemonic ?
            dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName() :
            isAsianStyle ? dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2() : dynamic_cast<ChuShogiPiece*>(p)->GetMnemonicImageFileName();
        break;
    case ChuShogi:
        if (pieceStyle == Asian) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
        else if (pieceStyle == Asian2) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
        else if (pieceStyle == Asian3) imageFileName = "J" + dynamic_cast<ChuShogiPiece*>(p)->GetMnemonicImageFileName();
        else if (pieceStyle == Mnemonic) imageFileName = dynamic_cast<ChuShogiPiece*>(p)->GetMnemonicImageFileName();
        else imageFileName = p->GetImageFileName();
        break;
    case TenjikuShogi:
    case WaShogi:
    case CrazyWa:
        imageFileName = isAsianStyle ?
            dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName() : p->GetImageFileName();
        break;
    case DaiDaiShogi:
        imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
        break;
    case Chess:
    case CapablancaChess:
    case GothicChess:
    case JanusChess:
    case GrandChess:
    case OmegaChess:
    case CourierChess:
    case ChancellorChess:
    case ModernChess:
    case Shatranj:
    case Shatar:
    case GrandeAcedrex:
        imageFileName = p->GetImageFileName();
        break;
    case Makruk:
        if (pieceStyle == European) imageFileName = p->GetImageFileName();
        else imageFileName = dynamic_cast<MakrukPiece*>(p)->GetImageFileName2();
        break;
    }
    return GetResourcePrefix(gameVariant, pieceStyle) + QString::fromStdString(imageFileName);
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
    case Schleich:
        return colour + "Hat.png";
    case Courier:
        return colour + "Pegasus.png";
    default:
        return "";
    }
}

QString GraphicsManager::GetMakrukImageFileName(PieceColour pieceColour, PieceType pieceType, PieceType basePieceType, bool isPromoted)
{
    QString colour = pieceColour == White ? "White" : "Black";
    if (basePieceType == Pawn && isPromoted)
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

QString GraphicsManager::GetKanjiImageFileName(PieceColour pieceColour, PieceType pieceType, bool isPromoted)
{
    //
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
