#include "zboard.h"

ZBoard::ZBoard(QWidget *parent) : QWidget(parent)
{
}

void ZBoard::Fill(std::vector<std::pair<PieceColour, PieceType>> capturedPieces)
{
    _pieces.clear();
    _pieces.emplace_back(White, None);
    std::ranges::for_each(capturedPieces, [&](std::pair<PieceColour, PieceType> p)
    {
        _pieces.emplace_back(p);
    });
}

void ZBoard::Fill(int count, PieceColour pieceColour, PieceType *pieces)
{
    _pieces.clear();
    _pieces.emplace_back(White, None);
    for (int index = 0; index < count; index++)
    {
        _pieces.emplace_back(pieceColour, pieces[index]);
    }
}

void ZBoard::Setup(int width, int height, GameVariant gameVariant, PieceStyle pieceStyle)
{
    _width = width;
    _height = height;
	_gameVariant = gameVariant;
    _pieceStyle = pieceStyle;
	switch (_gameVariant)
	{
	case Chess:
		Fill(std::size(ChessPieces), White, ChessPieces);
		break;
	case CapablancaChess:
	case GothicChess:
	case GrandChess:
		Fill(std::size(GothicChessPieces), White, GothicChessPieces);
		break;
	case JanusChess:
	case ModernChess:
		Fill(std::size(JanusChessPieces), White, JanusChessPieces);
		break;
	case OmegaChess:
		Fill(std::size(OmegaChessPieces), White, OmegaChessPieces);
		break;
	case NightriderChess:
		Fill(std::size(NightriderChessPieces), White, NightriderChessPieces);
		break;
	case CourierChess:
		Fill(std::size(CourierChessPieces), White, CourierChessPieces);
		break;
	case ChancellorChess:
		Fill(std::size(ChancellorChessPieces), White, ChancellorChessPieces);
		break;
	case MusketeerChess:
		Fill(std::size(MusketeerChessPieces), White, MusketeerChessPieces);
		break;
	case GrandeAcedrex:
		Fill(std::size(GrandeAcedrexPieces), White, GrandeAcedrexPieces);
		break;
	case Shogi:
	case ShoShogi:
		Fill(std::size(ShogiPieces), White, ShogiPieces);
		break;
	case ChuShogi:
		Fill(std::size(ChuShogiPieces), White, ChuShogiPieces);
		break;
	case DaiShogi:
		Fill(std::size(DaiShogiPieces), White, DaiShogiPieces);
		break;
	case TenjikuShogi:
		Fill(std::size(TenjikuShogiPieces), White, TenjikuShogiPieces);
		break;
	case DaiDaiShogi:
		Fill(std::size(DaiDaiShogiPieces), White, DaiDaiShogiPieces);
		break;
	case MakaDaiDaiShogi:
		Fill(std::size(MakaDaiDaiShogiPieces), White, MakaDaiDaiShogiPieces);
		break;
	case KoShogi:
		Fill(std::size(KoShogiPieces), White, KoShogiPieces);
		break;
	case TaiShogi:
		Fill(std::size(TaiShogiPieces), White, TaiShogiPieces);
		break;
	case MicroShogi:
	case KyotoShogi:
		Fill(std::size(MicroShogiPieces), White, MicroShogiPieces);
		break;
	case MiniShogi:
		Fill(std::size(MiniShogiPieces), White, MiniShogiPieces);
		break;
	case JudkinShogi:
		Fill(std::size(JudkinsShogiPieces), White, JudkinsShogiPieces);
		break;
	case WhaleShogi:
		Fill(std::size(WhaleShogiPieces), White, WhaleShogiPieces);
		break;
	case ToriShogi:
		Fill(std::size(ToriShogiPieces), White, ToriShogiPieces);
		break;
	case EuroShogi:
		Fill(std::size(EuroShogiPieces), White, EuroShogiPieces);
		break;
	case YariShogi:
		Fill(std::size(YariShogiPieces), White, YariShogiPieces);
		break;
	case HeianShogi:
		Fill(std::size(HeianShogiPieces), White, HeianShogiPieces);
		break;
	case HeianDaiShogi:
		Fill(std::size(HeianDaiShogiPieces), White, HeianDaiShogiPieces);
		break;
	case CrazyWa:
		Fill(std::size(WaShogiPieces), White, WaShogiPieces);
		break;
	case Xiangqi:
	case Janggi:
		Fill(std::size(XiangqiPieces), White, XiangqiPieces);
		break;
	case Shatranj:
		Fill(std::size(ShatranjPieces), White, ShatranjPieces);
		break;
	case Makruk:
		Fill(std::size(MakrukPieces), White, MakrukPieces);
		break;
	case Shatar:
		Fill(std::size(ShatarPieces), White, ShatarPieces);
		break;
	case Sittuyin:
		Fill(std::size(SittuyinPieces), White, SittuyinPieces);
		break;
	}
}

PieceColour ZBoard::GetChosenColour() const
{
    return _chosenColour;
}

PieceType ZBoard::GetChosenPiece() const
{
    return _chosenPiece;
}

void ZBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(_editorMode ? Qt::magenta : Qt::black);
    painter.setBrush(Qt::NoBrush);

    const QSize s = this->size();
    const int w = s.width() / _width;
    const int h = s.height() / _height;
    unsigned long long index = 0;
    painter.drawRect(QRect(0, 0, w, h));
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            if (_pieces.size() > index)
            {
                QRect rect(j * w, i * h, w, h);
                painter.drawRect(rect);
                auto piece = _pieces[index];
            	GraphicsManager::DrawPiece(painter, Piece(piece.second, Black), _gameVariant, _pieceStyle, w, h, j, i);
            }
            else break;
            index++;
        }
    }
    index = 0;
    for (int i = _width - 1; i >= 0; i--)
    {
        for (int j = _height - 1; j >= 0; j--)
        {
            if (_pieces.size() > index)
            {
                QRect rect(j * w, i * h, w, h);
                painter.drawRect(rect);
                auto piece = _pieces[index];
                GraphicsManager::DrawPiece(painter, Piece(piece.second, White), _gameVariant, _pieceStyle, w, h, j, i);
            }
            else break;
            index++;
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
    unsigned long long index = y * _height + x;
    if (_pieces.size() > index)
    {
        _chosenColour = Black;
        _chosenPiece = _pieces[index].second;
    }
    else if (_pieces.size() > _width * _height - index - 1)
    {
        _chosenColour = White;
        _chosenPiece = _pieces[_width * _height - index - 1].second;
    }
}
