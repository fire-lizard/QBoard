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
	const QString resourcePrefix = ":/pieces_eur/images/";
	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.setBrush(Qt::NoBrush);

	const QSize s = this->size();
	const int w = s.width() / _board->GetWidth();
	const int h = s.height() / _board->GetHeight();
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
			else if (std::any_of(_opponentMoves.begin(), _opponentMoves.end(), [=](std::tuple<int, int, int, int> t) {return get<2>(t) == i && get<3>(t) == j; }))
			{
				if (_board->GetData(i, j) != nullptr && (_board->GetData(i, j)->GetType() == King || _board->GetData(i, j)->GetType() == Queen))
				{
					painter.setBrush(Qt::yellow);
				}
				else
				{
					if (_gameVariant == Chess)
					{
						if ((i + j) % 2 != 0)
							painter.setBrush(Qt::gray);
					}
					else if (_gameVariant == Xiangqi)
					{
						if ((i > 2 && i < 6 && j < 3) || (i > 2 && i < 6 && j > 6))
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
				if (_gameVariant == Chess)
				{
					if ((i + j) % 2 != 0)
						painter.setBrush(Qt::gray);
				}
				else if (_gameVariant == Xiangqi)
				{
					if ((i > 2 && i < 6 && j < 3) || (i > 2 && i < 6 && j > 6))
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
			const Piece *p = _board->GetData(i, j);
			if (p != nullptr)
			{
				const PieceType t = p->GetType();
				const PieceColour c = p->GetColour();
				QPixmap pixmap(resourcePrefix + QString::fromStdString(Piece::GetImageFileName(t, c)));
				painter.drawPixmap(i * w + w / 4, j * h + h / 4, 33, 33, pixmap);
			}
		}
	}
}

void VBoard::mousePressEvent(QMouseEvent *event)
{
	if (_engine != nullptr && _currentPlayer == Black) return;
	const int w = this->size().width() / _board->GetWidth();
	const int h = this->size().height() / _board->GetHeight();
	const int x = event->x() / w;
	const int y = event->y() / h;
	Piece *p = _board->GetData(x, y);
	if (_currentPiece != nullptr && (p == nullptr || p->GetColour() != _currentPlayer))
	{
		if (_board->Move(_oldX, _oldY, x, y))
		{
			char promotion = ' ';
			if (_gameVariant == Chess)
			{
				if (_currentPiece->GetType() == Pawn &&
                    ((y == 7 && _currentPiece->GetColour() == Black) ||
                    (y == 0 && _currentPiece->GetColour() == White)))
				{
					_currentPiece->Promote(Queen);
					promotion = 'q';
				}
			}
			if (_gameVariant == MiniShogi)
			{
                if ((y == 4 && _currentPiece->GetColour() == Black) ||
                    (y == 0 && _currentPiece->GetColour() == White))
				{
					_currentPiece->Promote();
					promotion = '+';
				}
			}
			if (_gameVariant == Shogi || _gameVariant == ShoShogi)
			{
                if ((y >= 6 && _currentPiece->GetColour() == Black) ||
                    (y <= 2 && _currentPiece->GetColour() == White))
				{
					_currentPiece->Promote();
					promotion = '+';
				}
			}
			if (_gameVariant == ChuShogi)
			{
                if ((y >= 8 && _currentPiece->GetColour() == Black) ||
                    (y <= 3 && _currentPiece->GetColour() == White))
				{
					_currentPiece->Promote();
					promotion = '+';
				}
			}
			if (_engine != nullptr)
			{
				if (_gameVariant == Xiangqi)
					_engine->Move(_oldX, _board->GetHeight() - _oldY - 1, x, _board->GetHeight() - y - 1, promotion);
				else if (_engine->GetType() == USI)
					_engine->Move(_board->GetWidth() - _oldX, _oldY, _board->GetWidth() - x, y, promotion);
				else
					_engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y, promotion);
			}
			AddMove(_board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, promotion);
			_currentPlayer = _currentPlayer == White ? Black : White;
			_statusBar->setStyleSheet("QStatusBar { color : black; }");
			_statusBar->showMessage(_currentPlayer == White ? "White move" : "Black move");
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
				_board->GetMoves(p, x, y);
				_moves = _board->Moves();
				std::for_each(_moves.begin(), _moves.end(), [=](std::pair<int, int> t)
				{
					CalculateCheck(x, y, t.first, t.second);
				});
				std::for_each(_moves.begin(), _moves.end(), [=](std::pair<int, int> t)
				{
					CalculateCheck(x, y, t.first, t.second);
				});
				this->repaint();
			}
		}
	}
}

Board* VBoard::GetBoard() const
{
	return _board;
}

std::vector<std::string> VBoard::GetGameRecord() const
{
	return _gameRecord;
}

GameVariant VBoard::GetGameVariant() const
{
	return _gameVariant;
}

void VBoard::SetGameVariant(GameVariant gameVariant)
{
	_currentPiece = nullptr;
	_moves.clear();
	_opponentMoves.clear();
	_gameRecord.clear();
	_gameVariant = gameVariant;
	switch (_gameVariant)
	{
	case Shogi:
		_board = new ShogiBoard();
		break;
	case ShoShogi:
		_board = new ShogiBoard();
		dynamic_cast<ShogiBoard*>(_board)->SetDrops(false);
		break;
	case ChuShogi:
		_board = new ChuShogiBoard();
		break;
	case MiniShogi:
		_board = new MiniShogiBoard();
		break;
	case Xiangqi:
		_board = new XiangqiBoard();
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
	_moves.clear();
	_opponentMoves.clear();
	_gameRecord.clear();
	_currentPlayer = currentPlayer;
}

void VBoard::SetTextEdit(QTextEdit* textEdit)
{
	_textEdit = textEdit;
}

bool VBoard::PossibleMove(int x, int y) const
{
	for (size_t index = 0; index < _moves.size(); index++)
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
	for (size_t index = _moves.size() - 1; index >= 0; index--)
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
				const Piece *p = board->GetData(i, j);
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
	for_each(opponentMoves.begin(), opponentMoves.end(), [=](std::tuple<int, int, int, int> t)
	{
		if (get<2>(t) == kx && get<3>(t) == ky)
		{
			_board->RemoveMove(newX, newY);
			RemoveMove(newX, newY);
		}
	});
	delete board;
}

void VBoard::AddMove(PieceType p, int x1, int x2, int y1, int y2, char promotion)
{
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
	QProcess *p = dynamic_cast<QProcess*>(sender());
	QByteArray buf = p->readAllStandardOutput();
	this->_textEdit->setText(buf);
	const qsizetype auxPos1 = buf.lastIndexOf("getmove ");
	const qsizetype pos = _engine->GetType() == WinBoard ? buf.lastIndexOf("move ", auxPos1) : buf.lastIndexOf("bestmove ", auxPos1) + 4;
	if (pos == -1)
		return;
	char x1, y1, x2, y2;
	if (_engine->GetType() == USI)
	{
		x1 = static_cast<char>(_board->GetWidth() - buf[pos + 5] + 48);
		y1 = static_cast<char>(buf[pos + 6] - 97);
		x2 = static_cast<char>(_board->GetWidth() - buf[pos + 7] + 48);
		y2 = static_cast<char>(buf[pos + 8] - 97);
	}
	else
	{
		x1 = static_cast<char>(buf[pos + 5] - 97);
		y1 = static_cast<char>(_board->GetHeight() - buf[pos + 6] + 48);
		x2 = static_cast<char>(buf[pos + 7] - 97);
		y2 = static_cast<char>(_board->GetHeight() - buf[pos + 8] + 48);
	}
	if (_gameVariant == Xiangqi)
	{
		y1--;
		y2--;
	}
	if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
	{
		_board->GetMoves(_board->GetData(x1, y1), x1, y1);
		_board->Move(x1, y1, x2, y2);
		AddMove(_board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, buf[pos + 9]);
		_engine->AddMove(buf[pos + 5], buf[pos + 6], buf[pos + 7], buf[pos + 8], buf[pos + 9]);
		if (_gameVariant == Chess && (y2 == 0 || y2 == _board->GetHeight() - 1) && _board->GetData(x2, y2)->GetType() == Pawn)
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
		if (_gameVariant == MiniShogi && (y2 == 0 || y2 == 4) && buf[pos + 9] == '+')
		{
			_board->GetData(x2, y2)->Promote();
		}
		if ((_gameVariant == Shogi || _gameVariant == ShoShogi) && (y2 <= 2 || y2 >= 6) && buf[pos + 9] == '+')
		{
			_board->GetData(x2, y2)->Promote();
		}
		if (_gameVariant == ChuShogi && (y2 <= 3 || y2 >= 8) && buf[pos + 9] == '+')
		{
			_board->GetData(x2, y2)->Promote();
		}
		if (_gameVariant == Shogi && (buf[pos + 6] == '@' || buf[pos + 6] == '*'))
		{
			PieceType newPiece;
			switch (buf[pos + 5])
			{
			case 'R':
				newPiece = Rook;
				break;
			case 'B':
				newPiece = Bishop;
				break;
			case 'G':
				newPiece = Gold;
				break;
			case 'S':
				newPiece = Silver;
				break;
			case 'N':
				newPiece = WhiteHorse;
				break;
			case 'L':
				newPiece = Lance;
				break;
			case 'P':
				newPiece = Pawn;
				break;
			default:
				newPiece = None;
				break;
			}
			dynamic_cast<ShogiBoard*>(_board)->PlacePiece(newPiece, _currentPlayer, x2, y2);
		}
	}
	_currentPlayer = White;
	this->_statusBar->showMessage("White move");
	this->repaint();
}

void VBoard::readyReadStandardError() const
{
	QProcess *p = dynamic_cast<QProcess*>(sender());
	const QByteArray buf = p->readAllStandardError();
	this->_textEdit->setHtml("<p style='color:red'>" + buf + "</p>");
}
