#include "zboard.h"

ZBoard::ZBoard(QWidget *parent) : QWidget(parent)
{
}

void ZBoard::Fill(std::vector<std::pair<PieceColour, PieceType>> capturedPieces)
{
    _pieces.clear();
    std::ranges::for_each(capturedPieces, [&](std::pair<PieceColour, PieceType> p)
    {
        _pieces.emplace_back(p);
    });
}

void ZBoard::Fill(int count, PieceColour pieceColour, PieceType *pieces)
{
    _pieces.clear();
    for (int index = 0; index < count; index++)
    {
        _pieces.emplace_back(pieceColour, pieces[index]);
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
    painter.setPen(_editorMode ? Qt::magenta : Qt::black);
    painter.setBrush(Qt::NoBrush);

    const QSize s = this->size();
    const int w = s.width() / _width;
    const int h = s.height() / _height;
    unsigned long long index = 0;
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            QRect rect(i * w, j * h, w, h);
            painter.drawRect(rect);
            if (_pieces.size() > index)
            {
                GraphicsManager::DrawPiece(painter, Piece(Rook, White), _gameVariant, _pieceStyle, w, h, i, j);
            }
            else break;
            /*Piece *p = _board->GetData(i, j);
            if (p != nullptr)
            {
            }*/
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
