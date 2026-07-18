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
    _pieces.clear();
	_pieces.emplace_back(std::nullopt);
	for (int index = 0; index < count; index++)
    {
        _pieces.emplace_back(std::make_optional<Piece>(pieces[index], White));
    }
}

void ZBoard::Setup(int width, int height, GameVariant gameVariant, PieceStyle pieceStyle)
{
    _width = width;
    _height = gameVariant == MusketeerChess ? 8 : height;
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
	case ShoShogi:
		Fill(std::size(ShogiPieces), ShogiPieces);
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
			unsigned long long index = j * _height + i;
			if (_pieces.size() > index)
			{
				std::optional<Piece> p = _pieces[index];
				painter.drawRect(i * w, j * h, w, h);
				if (p != std::nullopt)
				{
					GraphicsManager::DrawPiece(painter, Piece(p->Type, Black), _gameVariant, _pieceStyle, w, h, i, j);
				}
			}
		}
	}
	for (int i = _width - 1; i >= 0 ; i--)
	{
		for (int j = _height - 1; j >= 0; j--)
		{
			unsigned long long index = j * _height + i;
			if (_pieces.size() > _width * _height - index - 1)
			{
				std::optional<Piece> p = _pieces[_width * _height - index - 1];
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
    unsigned long long index = y * _height + x;
    if (_pieces.size() > index)
    {
		if (_pieces[index].has_value())
		{
			_chosenPiece = std::make_optional<Piece>(_pieces[index]->Type, Black);
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
}
