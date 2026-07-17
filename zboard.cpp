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
    unsigned long long index = y * h + x;
    if (_pieces.size() > index)
    {
        _chosenColour = _pieces[index].first;
        _chosenPiece = _pieces[index].second;
    }
}
