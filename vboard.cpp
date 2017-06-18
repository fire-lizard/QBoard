#include "vboard.h"

VBoard::VBoard(QWidget *parent) : QWidget(parent)
{
	_board = new ChessBoard();
	_currentPiece = nullptr;
}

VBoard::~VBoard()
{
	delete _board;
}


void VBoard::paintEvent(QPaintEvent *)
{
	QString resourcePrefix = ":/pieces_eur/images/";
	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.setBrush(Qt::NoBrush);

	QSize s = this->size();;
	int w = s.width() / _board->GetWidth();
	int h = s.height() / _board->GetHeight();
	for (int i = 0; i < _board->GetWidth(); i++)
	{
		for (int j = 0; j < _board->GetHeight(); j++)
		{
			QRect rect(i * w, j * h, w, h);
			if (PossibleMove(i, j))
			{
				if (_board->GetData(i, j) != nullptr)
				{
					painter.setBrush(Qt::red);
					painter.drawRect(rect);
					painter.setBrush(Qt::NoBrush);
				}
				else if (_board->GetData(i, j) == nullptr)
				{
					painter.setBrush(Qt::cyan);
					painter.drawRect(rect);
					painter.setBrush(Qt::NoBrush);
				}
			}
			else if (any_of(_opponentMoves.begin(), _opponentMoves.end(), [=](tuple<int, int, int, int> p) {return get<2>(p) == i && get<3>(p) == j; }))
			{
				if (_board->GetData(i, j) != nullptr && (_board->GetData(i, j)->GetType() == King || _board->GetData(i, j)->GetType() == Queen))
				{
					painter.setBrush(Qt::yellow);
				}
				else
				{
					if ((i + j) % 2 != 0)
						painter.setBrush(Qt::gray);
				}
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else
			{
				if ((i + j) % 2 != 0)
					painter.setBrush(Qt::gray);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
		}
	}
	for (int i = 0; i < _board->GetWidth(); i++)
	{
		for (int j = 0; j < _board->GetHeight(); j++)
		{
			Piece *p = _board->GetData(i, j);
			if (p != nullptr)
			{
				PieceType t = p->GetType();
				PieceColour c = p->GetColour();
				QPixmap pixmap(resourcePrefix + QString::fromStdString(Piece::GetImageFileName(t, c)));
				painter.drawPixmap(i * w + w / 4, j * h + h / 4, 33, 33, pixmap);
			}
		}
	}
}

void VBoard::mousePressEvent(QMouseEvent *event)
{
	int w = this->size().width() / _board->GetWidth();
	int h = this->size().height() / _board->GetHeight();
	int x = event->x() / w;
	int y = event->y() / h;
	Piece *p = _board->GetData(x, y);
	if (_currentPiece != nullptr && (p == nullptr || p->GetColour() != _currentPlayer))
	{
		CalculateCheck(_oldX, _oldY, x, y);
		if (_board->Move(_oldX, _oldY, x, y))
		{
			_currentPlayer = _currentPlayer == White ? Black : White;
			_opponentMoves = _board->GetAllMoves(_currentPlayer == White ? Black : White);
			_currentPiece = nullptr;
			_oldX = -1;
			_oldY = -1;
			_moves.clear();
		}
		this->repaint();
	}
	else
	{
		if (p != nullptr)
		{
			if (p->GetColour() == _currentPlayer)
			{
				_currentPiece = _board->GetData(x, y);
				_oldX = x;
				_oldY = y;
				_myMoves = _board->GetAllMoves(_currentPlayer);
				_board->GetMoves(p, x, y);
				_moves = _board->Moves();
				this->repaint();
			}
		}
	}
}

Board* VBoard::GetBoard() const
{
	return _board;
}

PieceColour VBoard::GetCurrentPlayer() const
{
	return _currentPlayer;
}

void VBoard::SetCurrentPlayer(PieceColour currentPlayer)
{
	_currentPlayer = currentPlayer;
}

bool VBoard::PossibleMove(int x, int y)
{
	for (int index = 0; index < _moves.size(); index++)
	{
		if (_moves[index].first == x && _moves[index].second == y)
		{
			return true;
		}
	}
	return false;
}

void VBoard::RemoveMove(int x, int y)
{
	for (int index = _moves.size() - 1; index >= 0; index--)
	{
		if (_moves[index].first == x && _moves[index].second == y)
			_moves.erase(_moves.begin() + index);
	}
}

void VBoard::CalculateCheck(int oldX, int oldY, int newX, int newY)
{
	int kx = 0, ky = 0;
	Board *board = _board->Clone();
	if (board->GetData(oldX, oldY)->GetType() == King)
	{
		kx = newX;
		ky = newY;
	}
	else
	{
		for (int i = 0; i < _board->GetWidth(); i++)
		{
			for (int j = 0; j < _board->GetHeight(); j++)
			{
				Piece *p = _board->GetData(i, j);
				if (p != nullptr && p->GetType() == King && p->GetColour() != _currentPlayer)
				{
					kx = i;
					ky = _board->GetHeight() - 1 - j;
					break;
				}
			}
		}
	}
	board->GetMoves(board->GetData(oldX, oldY), oldX, oldY);
	board->Move(oldX, oldY, newX, newY);
	auto opponentMoves = board->GetAllMoves(_currentPlayer == White ? Black : White);
	for_each(opponentMoves.begin(), opponentMoves.end(), [=](tuple<int, int, int, int> p)
	{
		if (get<2>(p) == kx && get<3>(p) == ky)
		{
			_board->RemoveMove(newX, newY);
			RemoveMove(newX, newY);
		}
	});
	delete board;
}
