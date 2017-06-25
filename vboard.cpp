#include "vboard.h"

VBoard::VBoard(QWidget *parent) : QWidget(parent)
{
	SetGameVariant(_gameVariant);
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
			else if (any_of(_opponentMoves.begin(), _opponentMoves.end(), [=](tuple<int, int, int, int> t) {return get<2>(t) == i && get<3>(t) == j; }))
			{
				if (_board->GetData(i, j) != nullptr && (_board->GetData(i, j)->GetType() == King || _board->GetData(i, j)->GetType() == Queen))
				{
					painter.setBrush(Qt::yellow);
				}
				else
				{
					if (_gameVariant == Chess || _gameVariant == TrueChess)
					{
						if ((i + j) % 2 != 0)
							painter.setBrush(Qt::gray);
					}
					else if (_gameVariant == Xiangqi)
					{
						if (i > 2 && i < 6 && j < 3)
						{
							painter.setBrush(Qt::green);
						}
						else if (i > 2 && i < 6 && j > 6)
						{
							painter.setBrush(Qt::green);
						}
						else if (j < 5)
						{
							painter.setBrush(Qt::lightGray);
						}
					}
				}
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else
			{
				if (_gameVariant == Chess || _gameVariant == TrueChess)
				{
					if ((i + j) % 2 != 0)
						painter.setBrush(Qt::gray);
				}
				else if (_gameVariant == Xiangqi)
				{
					if (i > 2 && i < 6 && j < 3)
					{
						painter.setBrush(Qt::green);
					}
					else if (i > 2 && i < 6 && j > 6)
					{
						painter.setBrush(Qt::green);
					}
					else if (j < 5)
					{
						painter.setBrush(Qt::lightGray);
					}
				}
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
			if (_engine != nullptr)
			{
				_engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
			}
			_currentPlayer = _currentPlayer == White ? Black : White;
			_statusBar->setStyleSheet("QStatusBar { color : black; }");
			_statusBar->showMessage(_currentPlayer == White ? "White move" : "Black move");
			_opponentMoves = _board->GetAllMoves(_currentPlayer == White ? Black : White);
			if (_gameVariant == Chess || _gameVariant == TrueChess)
			{
				if (_currentPiece->GetType() == Pawn &&
					(y == 7 && _currentPiece->GetColour() == Black ||
						y == 0 && _currentPiece->GetColour() == White))
					_currentPiece->Promote(Queen);
			}
			if (_gameVariant == Shogi)
			{
				if (y >= 7 && _currentPiece->GetColour() == Black ||
					y <= 1 && _currentPiece->GetColour() == White)
					_currentPiece->Promote();
			}
			if (_gameVariant == ChuShogi)
			{
				if (y >= 10 && _currentPiece->GetColour() == Black ||
					y <= 1 && _currentPiece->GetColour() == White)
					_currentPiece->Promote();
			}
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

GameVariant VBoard::GetGameVariant() const
{
	return _gameVariant;
}

void VBoard::SetGameVariant(GameVariant gameVariant)
{
	_currentPiece = nullptr;
	_moves.clear();
	_myMoves.clear();
	_opponentMoves.clear();
	_gameVariant = gameVariant;
	switch (_gameVariant)
	{
	case Shogi:
		_board = new ShogiBoard();
		break;
	case ShoShogi:
		_board = new ShogiBoard();
		static_cast<ShogiBoard*>(_board)->SetDrops(false);
		break;
	case ChuShogi:
		_board = new ChuShogiBoard();
		break;
	case Xiangqi:
		_board = new XiangqiBoard();
		break;
	case TrueChess:
		_board = new TrueChessBoard();
		break;
	default:
		_board = new ChessBoard();
		break;
	}
	this->setFixedSize(_board->GetWidth() * 66 + 1, _board->GetHeight() * 66 + 1);
	if (this->_window != nullptr)
	{
		this->_window->setFixedSize(width() + 280, height() + 100);
		this->_textEdit->setGeometry(x() + width() + 10, y(), 250, height());
	}
}

PieceColour VBoard::GetCurrentPlayer() const
{
	return _currentPlayer;
}

void VBoard::SetCurrentPlayer(PieceColour currentPlayer)
{
	_currentPlayer = currentPlayer;
}

void VBoard::SetTextEdit(QTextEdit* textEdit)
{
	_textEdit = textEdit;
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
	int kx = -1, ky = -1;
	Board *board = _board->Clone();
	if (board->GetData(oldX, oldY)->GetType() == King)
	{
		kx = newX;
		ky = newY;
	}
	else
	{
		for (int i = 0; i < board->GetWidth(); i++)
		{
			for (int j = 0; j < board->GetHeight(); j++)
			{
				Piece *p = board->GetData(i, j);
				if (p != nullptr && p->GetType() == King && p->GetColour() == _currentPlayer)
				{
					kx = i;
					ky = j;
					break;
				}
			}
			if (kx > -1 && ky > -1)
				break;
		}
	}
	board->GetMoves(board->GetData(oldX, oldY), oldX, oldY);
	board->Move(oldX, oldY, newX, newY);
	auto opponentMoves = board->GetAllMoves(_currentPlayer == White ? Black : White);
	for_each(opponentMoves.begin(), opponentMoves.end(), [=](tuple<int, int, int, int> t)
	{
		if (get<2>(t) == kx && get<3>(t) == ky)
		{
			_board->RemoveMove(newX, newY);
			RemoveMove(newX, newY);
		}
	});
	delete board;
}

void VBoard::SetStatusBar(QStatusBar *statusBar)
{
	_statusBar = statusBar;
}

void VBoard::SetMainWindow(QMainWindow *window)
{
	_window = window;
}

void VBoard::SetEngine(Engine* engine)
{
	_engine = engine;
}

void VBoard::readyReadStandardOutput()
{
	QProcess *p = static_cast<QProcess*>(sender());
	QByteArray buf = p->readAllStandardOutput();
	int len = buf.length();
	this->_textEdit->setPlainText(buf);
	if (len >= 6)
	{
		int auxPos1 = buf.lastIndexOf("getmove ");
		int pos = buf.lastIndexOf("move ", auxPos1);
		if (pos == -1)
			return;
		char x1 = buf[pos + 5] - 97;
		char y1 = _board->GetHeight() - buf[pos + 6] + 48;
		char x2 = buf[pos + 7] - 97;
		char y2 = _board->GetHeight() - buf[pos + 8] + 48;
		if (_gameVariant == Xiangqi)
		{
			y1--;
			y2--;
		}
		if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
		{
			_board->GetMoves(_board->GetData(x1, y1), x1, y1);
			_board->Move(x1, y1, x2, y2);
			if ((_gameVariant == Chess || _gameVariant == TrueChess) && 
				(y2 == 0 || y2 == _board->GetHeight() - 1) && 
				_board->GetData(x2, y2)->GetType() == Pawn)
			{
				char promotion = buf[pos + 9];
				switch (promotion)
				{
				case 'n':
					_board->GetData(x2, y2)->Promote(WhiteHorse);
					break;
				case 'b':
					_board->GetData(x2, y2)->Promote(Bishop);
					break;
				case 'r':
					_board->GetData(x2, y2)->Promote(Rook);
					break;
				default:
					_board->GetData(x2, y2)->Promote(Queen);
					break;
				}
			}
		}
		_currentPlayer = White;
		this->_statusBar->showMessage("White move");
		this->repaint();
	}
}

void VBoard::bytesWritten(qint64 bytes)
{
	this->_textEdit->setPlainText(QString::number(bytes) + " bytes written.\n");
}
