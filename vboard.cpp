#include "vboard.h"

VBoard::VBoard(QWidget *parent) : QWidget(parent)
{

}

void VBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::NoBrush);

        QSize s = this->size();;
        int w = s.width() / _board.GetWidth();
        int h = s.height() / _board.GetHeight();
        for (int i = 0; i < _board.GetWidth(); i++)
        {
            for (int j = 0; j < _board.GetHeight(); j++)
            {
                QRect rect(i * w, j * h, w, h);
                if (PossibleMove(i, j))
                {
                    if (_board.GetData(i, j) != nullptr)
                    {
                        painter.setBrush(Qt::red);
                        painter.drawRect(rect);
                        painter.setBrush(Qt::NoBrush);
                    }
                    else if (_board.GetData(i, j) == nullptr)
                    {
                        painter.setBrush(Qt::cyan);
                        painter.drawRect(rect);
                        painter.setBrush(Qt::NoBrush);
                    }
                }
                else if (any_of(_opponentMoves.begin(), _opponentMoves.end(), [=](pair<int,int> p){return p.first == i && p.second == j;}))
                {
                    if (_board.GetData(i, j) != nullptr && (_board.GetData(i, j)->GetType() == King || _board.GetData(i, j)->GetType() == Queen))
                    {
                        painter.setBrush(Qt::yellow);
                        if (_board.GetData(i, j)->GetType() == King)
                            _check = true;
                    }
                    painter.drawRect(rect);
                    painter.setBrush(Qt::NoBrush);
                }
                else
                {
                    painter.drawRect(rect);
                }
            }
        }
        /*for (int i = 0; i < _board.GetWidth(); i++)
        {
            for (int j = 0; j < _board.GetHeight(); j++)
            {
                Piece *p = _board.GetData(i, j);
                if (p != nullptr)
                {
                    PieceType t = p->GetType();
                    PieceColour c = p->GetColour();
                    wxImage image("images/" + Piece::GetImageFileName(t, c));
                    wxBitmap bitmap(image);
                    dc.DrawBitmap(bitmap, i * w + 10, j * h + 5);
                }
            }
        }*/
}

void VBoard::mousePressEvent(QMouseEvent *event)
{
    int w = this->size().width() / _board.GetWidth();
    int h = this->size().height() / _board.GetHeight();
    int x = event->x() / w;
    int y = event->y() / h;
    Piece *p = _board.GetData(x, y);
    if (_currentPiece != nullptr && (p == nullptr || p->GetColour() != _currentPlayer))
    {
        if (_board.Move(_oldX, _oldY, x, y))
        {
            _currentPlayer = _currentPlayer == White ? Black : White;
            _opponentMoves = _board.GetAllMoves(_currentPlayer == White ? Black : White);
            _currentPiece = nullptr;
            _oldX = -1;
            _oldY = -1;
            _moves.clear();
            this->repaint();
            _check = false;
        }
    }
    else
    {
        if (p != nullptr && (!_check || p->GetType() == King))
        {
            if (p->GetColour() == _currentPlayer)
            {
                _currentPiece = _board.GetData(x, y);
                _oldX = x;
                _oldY = y;
                _myMoves = _board.GetAllMoves(_currentPlayer);
                _board.GetMoves(p, x, y);
                _moves = _board.Moves();
                if (_check)
                {
                    for (vector<pair<int,int>>::reverse_iterator iter = _moves.rbegin(); iter != _moves.rend(); ++iter)
                    {
                        if (any_of(_opponentMoves.begin(), _opponentMoves.end(), [=](pair<int,int> pp)
                                   {return pp.first == (*iter).first && pp.second == (*iter).second;}))
                        {
                            _moves.erase(iter == _moves.rbegin() ? (iter + 1).base() : iter.base());
                        }
                        if (_moves.size() == 0)
                        {
                            QMessageBox::information(this, "Game over...", "Checkmate!");
                        }
                    }
                }
                else if (_myMoves.size() == 0)
                {
                    QMessageBox::information(this, "Game over...", "Stalemate!");
                }
                this->repaint();
            }
        }
    }
}

bool VBoard::PossibleMove(int x, int y)
{
    for (unsigned index = 0; index < _moves.size(); index++)
    {
        if (_moves[index].first == x && _moves[index].second == y)
        {
            return true;
        }
    }
    return false;
}
