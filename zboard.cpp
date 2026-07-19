#include "zboard.h"

ZBoard::ZBoard(QWidget *parent) : QWidget(parent)
{
}

void ZBoard::Fill(std::vector<std::pair<PieceColour, PieceType>> capturedPieces)
{
    _pieces.clear();
    std::ranges::for_each(capturedPieces, [&](std::pair<PieceColour, PieceType> p)
    {
        _pieces.emplace_back(std::make_optional<Piece>(p.second, p.first));
    });
}

void ZBoard::Fill(int count, PieceType *pieces)
{
	auto promotedPieces = GetPromotedPieces();
	_pieces.clear();
	_pieces.emplace_back(std::nullopt);
	for (int index = 0; index < count; index++)
    {
		auto piece = std::make_optional<Piece>(pieces[index], White);
		piece->IsPromoted = std::ranges::find(promotedPieces, piece->Type) != std::end(promotedPieces);
		_pieces.emplace_back(piece);
    }
}

void ZBoard::Setup(int width, int height, GameVariant gameVariant, PieceStyle pieceStyle)
{
    _width = gameVariant == MicroShogi ? 5 : width;
    _height = height;
	_gameVariant = gameVariant;
    _pieceStyle = pieceStyle;
	switch (_gameVariant)
	{
	case Chess:
		Fill(std::size(ChessPieces), ChessPieces);
		break;
	case CapablancaChess:
	case GothicChess:
	case GrandChess:
		Fill(std::size(GothicChessPieces), GothicChessPieces);
		break;
	case JanusChess:
	case ModernChess:
		Fill(std::size(JanusChessPieces), JanusChessPieces);
		break;
	case OmegaChess:
		Fill(std::size(OmegaChessPieces), OmegaChessPieces);
		break;
	case NightriderChess:
		Fill(std::size(NightriderChessPieces), NightriderChessPieces);
		break;
	case CourierChess:
		Fill(std::size(CourierChessPieces), CourierChessPieces);
		break;
	case ChancellorChess:
		Fill(std::size(ChancellorChessPieces), ChancellorChessPieces);
		break;
	case MusketeerChess:
		Fill(std::size(MusketeerChessPieces), MusketeerChessPieces);
		break;
	case GrandeAcedrex:
		Fill(std::size(GrandeAcedrexPieces), GrandeAcedrexPieces);
		break;
	case Shogi:
		Fill(std::size(ShogiPieces), ShogiPieces);
		break;
	case ShoShogi:
		Fill(std::size(ShoShogiPieces), ShoShogiPieces);
		break;
	case ChuShogi:
		Fill(std::size(ChuShogiPieces), ChuShogiPieces);
		break;
	case DaiShogi:
		Fill(std::size(DaiShogiPieces), DaiShogiPieces);
		break;
	case TenjikuShogi:
		Fill(std::size(TenjikuShogiPieces), TenjikuShogiPieces);
		break;
	case DaiDaiShogi:
		Fill(std::size(DaiDaiShogiPieces), DaiDaiShogiPieces);
		break;
	case MakaDaiDaiShogi:
		Fill(std::size(MakaDaiDaiShogiPieces), MakaDaiDaiShogiPieces);
		break;
	case KoShogi:
		Fill(std::size(KoShogiPieces), KoShogiPieces);
		break;
	case TaiShogi:
		Fill(std::size(TaiShogiPieces), TaiShogiPieces);
		break;
	case MicroShogi:
	case KyotoShogi:
		Fill(std::size(MicroShogiPieces), MicroShogiPieces);
		break;
	case MiniShogi:
		Fill(std::size(MiniShogiPieces), MiniShogiPieces);
		break;
	case JudkinShogi:
		Fill(std::size(JudkinsShogiPieces), JudkinsShogiPieces);
		break;
	case WhaleShogi:
		Fill(std::size(WhaleShogiPieces), WhaleShogiPieces);
		break;
	case ToriShogi:
		Fill(std::size(ToriShogiPieces), ToriShogiPieces);
		break;
	case EuroShogi:
		Fill(std::size(EuroShogiPieces), EuroShogiPieces);
		break;
	case YariShogi:
		Fill(std::size(YariShogiPieces), YariShogiPieces);
		break;
	case HeianShogi:
		Fill(std::size(HeianShogiPieces), HeianShogiPieces);
		break;
	case HeianDaiShogi:
		Fill(std::size(HeianDaiShogiPieces), HeianDaiShogiPieces);
		break;
	case CrazyWa:
		Fill(std::size(WaShogiPieces), WaShogiPieces);
		break;
	case Xiangqi:
	case Janggi:
		Fill(std::size(XiangqiPieces), XiangqiPieces);
		break;
	case Shatranj:
		Fill(std::size(ShatranjPieces), ShatranjPieces);
		break;
	case Makruk:
		Fill(std::size(MakrukPieces), MakrukPieces);
		break;
	case Shatar:
		Fill(std::size(ShatarPieces), ShatarPieces);
		break;
	case Sittuyin:
		Fill(std::size(SittuyinPieces), SittuyinPieces);
		break;
	}
}

std::optional<Piece> ZBoard::GetChosenPiece() const
{
    return _chosenPiece;
}

std::vector<PieceType> ZBoard::GetPromotedPieces() const
{
	switch (_gameVariant)
	{
	case Shogi:
	case ShoShogi:
	case MiniShogi:
	case JudkinShogi:
	case EuroShogi:
		return {Tokin, PromotedKnight, PromotedLance, PromotedSilver, DragonHorse, DragonKing};
	case CrazyWa:
		return {TenaciousFalcon, BearEyes, Elephant, RaidingFalcon, Rook, HeavenlyHorse, PloddingOx, Tokin};
	case ChuShogi:
	case DaiShogi:
		return {FlyingStag, FlyingOx, FreeBoar, Whale, WhiteHorse, Prince, Falcon, Eagle, Tokin};
	case TenjikuShogi:
		return {Prince, HeavenlyTetrarch, FlyingStag, FlyingOx, FreeBoar, Whale, WhiteHorse, MultiGeneral, Tokin};
	case DaiDaiShogi:
		return {GreatElephant, FuriousFiend, MountainWitch, WizardStork};
	case MakaDaiDaiShogi:
		return {Emperor, TeachingKing, BuddhistSpirit, FreeGold, FreeSilver, FreeCopper, FreeIron, FreeTile, FreeStone, FreeEarth, FreeGo, Prince,
		           FreeTiger, FreeLeopard, FreeSerpent, FreeDragon, MountainWitch, WizardStork, FreeCat, FuriousFiend, GoldenBird, GreatDragon, Bat,
				   FreeWolf, FreeBear, FreeBoar};
	case KoShogi:
		return {Prince, Thunderclap, RoamingAssault, FlyingStag, CompanyCommander, ViceCommissioner, PoisonFlame, DoubleKylin, DoublePhoenix, ExtensiveFog, HolyLight,
				   SkywardNet, EarthwardNet, RisingDragon, WingedTiger, FlyingHawk, LongbowKnight, CrossbowKnight, CannonCarriage, DivineCarriage, WingedHorse, FlyingOx,
				   FreeBoar};
	case TaiShogi:
		return {SquareMover, WizardStork, MountainWitch, FragrantElephant, GreatElephant, FuriousFiend, TeachingKing, BuddhistSpirit};
	default:
		return {};
	}
}

int ZBoard::GetRowCount(GameVariant gameVariant)
{
	switch (gameVariant)
	{
	case MusketeerChess:
	case MiniShogi:
	case JudkinShogi:
	case CrazyWa:
	case ChuShogi:
	case DaiShogi:
	case TenjikuShogi:
		return 3;
	case DaiDaiShogi:
	case MakaDaiDaiShogi:
	case KoShogi:
		return 4;
	case TaiShogi:
		return 5;
	default:
		return 2;
	}
}

void ZBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(_editorMode ? Qt::magenta : Qt::black);

    const QSize s = this->size();
    const int w = s.width() / _width;
    const int h = s.height() / _height;
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			unsigned long long index = j * _width + i;
			if (_pieces.size() > index)
			{
				std::optional<Piece> p = _pieces[index];
				if (_chosenPiece.has_value() && p.has_value() && _chosenPiece->Type == p->Type && _chosenPiece->Colour == Black)
				{
					painter.setBrush(QColorConstants::Svg::violet);
				}
				else
				{
					painter.setBrush(Qt::NoBrush);
				}
				painter.drawRect(i * w, j * h, w, h);
				if (p != std::nullopt)
				{
					p->Colour = Black;
					GraphicsManager::DrawPiece(painter, p.value(), _gameVariant, _pieceStyle, w, h, i, j);
				}
			}
		}
	}
	for (int i = _width - 1; i >= 0 ; i--)
	{
		for (int j = _height - 1; j >= 0; j--)
		{
			unsigned long long index = j * _width + i;
			if (_pieces.size() > _width * _height - index - 1)
			{
				std::optional<Piece> p = _pieces[_width * _height - index - 1];
				if (_chosenPiece.has_value() && p.has_value() && _chosenPiece->Type == p->Type && _chosenPiece->Colour == p->Colour)
				{
					painter.setBrush(QColorConstants::Svg::violet);
				}
				else
				{
					painter.setBrush(Qt::NoBrush);
				}
				painter.drawRect(i * w, j * h, w, h);
				if (p != std::nullopt)
				{
					GraphicsManager::DrawPiece(painter, p.value(), _gameVariant, _pieceStyle, w, h, i, j);
				}
			}
		}
	}
}

void ZBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::MouseButton::LeftButton) return;
    const int w = this->size().width() / _width;
    const int h = this->size().height() / _height;
    const int x = static_cast<int>(event->position().x()) / w;
    const int y = static_cast<int>(event->position().y()) / h;
    unsigned long long index = y * _width + x;
    if (_pieces.size() > index)
    {
		if (_pieces[index].has_value())
		{
			_chosenPiece = _pieces[index];
			_chosenPiece->Colour = Black;
		}
		else
		{
			_chosenPiece = std::nullopt;
		}
    }
    else if (_pieces.size() > _width * _height - index - 1)
    {
        _chosenPiece = _pieces[_width * _height - index - 1];
    }
	repaint();
}
