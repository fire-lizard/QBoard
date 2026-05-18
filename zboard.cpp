#include "zboard.h"

ZBoard::ZBoard(QWidget *parent, int width, int height) : QWidget(parent)
{
    _width = width;
    _height = height;
}

void ZBoard::Fill(PieceColour pieceColour, std::vector<std::pair<PieceColour, PieceType>> capturedPieces)
{
    _pieces.clear();
    for_each(capturedPieces.begin(), capturedPieces.end(), [&](std::pair<PieceColour, PieceType> p)
    {
        if (p.first == pieceColour)
        {
            _pieces.emplace_back(p.second);
        }
    });
}

void ZBoard::Fill(int count, PieceType *pieces)
{
    _pieces.clear();
    for (int index = 0; index < count; index++)
    {
        _pieces.emplace_back(pieces[index]);
    }
}

PieceType ZBoard::GetChosenPiece() const
{
    return _chosenPiece;
}

void ZBoard::SetChosenPiece(PieceType chosenPiece)
{
    _chosenPiece = chosenPiece;
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
            if (_pieces.size() >= index)
            {
                GraphicsManager::DrawPiece(painter, nullptr, _gameVariant, _pieceStyle, w, h, i, j);
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
    const int x = static_cast<int>(event->x()) / w;
    const int y = static_cast<int>(event->y()) / h;
    unsigned long long index = y * h + x;
    _chosenPiece = _pieces.size() >= index ? _pieces[index] : None;
}
