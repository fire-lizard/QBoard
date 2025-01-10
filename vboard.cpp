#include "vboard.h"

VBoard::VBoard(QWidget *parent) : QWidget(parent)
{
    _nlre = QRegularExpression("[\r\n]+");
    _csre = QRegularExpression(R"(([a-l])(1[0-2]|[0-9])([a-l])(1[0-2]|[0-9])([+nbrq])?)");
    _qhre = QRegularExpression(R"(([A-I])([0-9])(\-)([A-I])([0-9]))");
    _sgxbre = QRegularExpression(R"(([RBGSNLPa-l])(\*|@|[1-9])([a-l])([1-9])(\+)?)");
    _sgusre = QRegularExpression(R"(([RBGSNLP1-9])(\*|@|[a-l])([1-9])([a-l])(\+)?)");
    SetGameVariant(_gameVariant);
}

VBoard::~VBoard()
{
	delete _board;
}

void VBoard::paintEvent(QPaintEvent *)
{
	QString resourcePrefix;
	if (_pieceStyle == Asian && _gameVariant == Xiangqi)
	{
		resourcePrefix = ":/pieces_chi/images_chi/";
	}
    else if (_pieceStyle == Asian && _gameVariant == ChuShogi)
	{
		resourcePrefix = ":/pieces_jap/images_jap/";
	}
    else if (_pieceStyle == Asian && _gameVariant > 1)
    {
        resourcePrefix = ":/pieces_sho/images_sho/";
    }
    else
	{
		resourcePrefix = ":/pieces_eur/images/";
	}
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
				if (_currentPiece != nullptr && std::find(std::begin(_lionPieces), std::end(_lionPieces), _currentPiece->GetType()) != std::end(_lionPieces))
				{
					if (((abs(_oldX - i) == 2 || abs(_oldY - j) == 2) && _currentPiece->GetType() == Lion) ||
						(abs(_oldX - i) == 2 && _oldY - j == 2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == White) ||
						(abs(_oldX - i) == 2 && _oldY - j == -2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == Black) ||
						(_oldX == i && _oldY - j == 2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == White) ||
						(_oldX == i && _oldY - j == -2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == Black))
					{
						if (_board->GetData(i, j) != nullptr)
						{
							painter.setBrush(QColorConstants::Svg::pink);
							painter.drawRect(rect);
							painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) == nullptr)
						{
							painter.setBrush(QColorConstants::Svg::lightcyan);
							painter.drawRect(rect);
							painter.setBrush(Qt::NoBrush);
						}
					}
					else
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
				}
				else if (_board->GetData(i, j) != nullptr)
				{
					if (_currentPiece != nullptr && std::find(std::begin(_lionPieces), std::end(_lionPieces), _currentPiece->GetType()) != std::end(_lionPieces))
					{
						painter.setBrush(QColorConstants::Svg::orangered);
					}
					else if (_board->GetData(i, j)->GetColour() != _currentPlayer)
					{
						painter.setBrush(Qt::red);
					}
					else
					{
						painter.setBrush(Qt::magenta);
					}
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
				if (_board->GetData(i, j) != nullptr && _board->GetData(i, j)->GetType() == King)
				{
					painter.setBrush(Qt::yellow);
				}
				else
				{
					if (_gameVariant == Chess || _gameVariant == Shatranj || _gameVariant == Makruk)
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
				if (_gameVariant == Chess || _gameVariant == Shatranj || _gameVariant == Makruk)
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
			Piece *p = _board->GetData(i, j);
			if (p != nullptr)
			{
				std::string imageFileName;
				if (_pieceStyle == Asian)
				{
					imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
				}
				else
				{
					imageFileName = p->GetImageFileName();
				}
				QPixmap pixmap(resourcePrefix + QString::fromStdString(imageFileName));
				painter.drawPixmap(i * w + w / 4, j * h + h / 4, 33, 33, pixmap);
			}
		}
	}
}

void VBoard::FinishMove()
{
	_currentPlayer = _currentPlayer == White ? Black : White;
	_statusBar->setStyleSheet("QStatusBar { color : black; }");
	_statusBar->showMessage(_currentPlayer == White ? _gameVariant == Xiangqi ? "Red move" : "White move" : "Black move");
	_opponentMoves = _board->GetAllMoves(_currentPlayer == White ? Black : White);
	_currentPiece = nullptr;
	_oldX = -1;
	_oldY = -1;
	_moves.clear();
	this->repaint();
}

void VBoard::mousePressEvent(QMouseEvent* event)
{
	if (_engine != nullptr && _currentPlayer == Black) return;
	const int w = this->size().width() / _board->GetWidth();
	const int h = this->size().height() / _board->GetHeight();
	const int x = static_cast<int>(event->position().x()) / w;
	const int y = static_cast<int>(event->position().y()) / h;
	Piece* p = _board->GetData(x, y);
	const PieceType ct = p != nullptr ? p->GetType() : None;
	// Castling check
	if (_gameVariant == Chess && _currentPiece != nullptr && _currentPiece->GetType() == King && !dynamic_cast<ChessPiece*>(_currentPiece)->HasMoved() &&
		p != nullptr && p->GetColour() == _currentPlayer && p->GetType() == Rook && !dynamic_cast<ChessPiece*>(p)->HasMoved())
	{
		_board->SetData(x, y, _currentPiece);
		_board->SetData(4, y, p);
		if (_engine != nullptr)
		{
			_engine->Move(_oldX, _board->GetHeight() - _oldY, x == 7 ? 6 : 2, _board->GetHeight() - y, ' ');
		}
		dynamic_cast<ChessBoard*>(_board)->WriteMove(x == 7 ? "O-O" : "O-O-O");
		FinishMove();
	}
	else if (_currentPiece != nullptr && (p == nullptr || p->GetColour() != _currentPlayer))
	{
		// Lion move
		if (std::find(std::begin(_lionPieces), std::end(_lionPieces), _currentPiece->GetType()) != std::end(_lionPieces) && !_lionMovedOnce)
		{
			if (((abs(_oldX - x) == 2 || abs(_oldY - y) == 2) && _currentPiece->GetType() == Lion) ||
				(abs(_oldX - x) == 2 && _oldY - y == 2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == White) ||
				(abs(_oldX - x) == 2 && _oldY - y == -2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == Black) ||
				(_oldX == x && _oldY - y == 2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == White) ||
				(_oldX == x && _oldY - y == -2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == Black))
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (_engine != nullptr)
					{
						_engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					AddMove(_board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, ' ', ' ');
					FinishMove();
				}
			}
			else if (_board->GetData(x, y) == nullptr)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (_engine != nullptr)
					{
						_engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					AddMove(_board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, ' ', ' ');
					FinishMove();
				}
			}
			else if (dynamic_cast<ChuShogiBoard*>(_board)->IsMovePossible(x, y))
			{
				_lionFirstMove.first = x;
				_lionFirstMove.second = y;
				_lionMovedOnce = true;
				this->repaint();
			}
		}
		else if (std::find(std::begin(_lionPieces), std::end(_lionPieces), _currentPiece->GetType()) != std::end(_lionPieces) && _lionMovedOnce)
		{
			if (dynamic_cast<ChuShogiBoard*>(_board)->LionMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
			{
				if (_engine != nullptr)
				{
					dynamic_cast<WbEngine*>(_engine)->Move(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
				}
				AddMove(_board->GetData(x, y)->GetType(), _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
				_lionMovedOnce = false;
				FinishMove();
			}
		}
		else if (_board->Move(_oldX, _oldY, x, y))
		{
			char promotion = ' ';
			if (_gameVariant == Chess)
			{
				if (_currentPiece->GetType() == Pawn &&
					((y == 7 && _currentPiece->GetColour() == Black) ||
						(y == 0 && _currentPiece->GetColour() == White)))
				{
					PromotionDialog* pd = new PromotionDialog(this);
					pd->exec();
					const PieceType pt = pd->GetChosenPiece();
					if (pt == Bishop)
					{
						promotion = 'b';
					}
					else if (pt == Knight)
					{
						promotion = 'n';
					}
					else if (pt == Rook)
					{
						promotion = 'r';
					}
					else
					{
						promotion = 'q';
					}
					_currentPiece->Promote(pt);
				}
			}
			else if (_gameVariant == Shatranj)
			{
				if (_currentPiece->GetType() == Pawn &&
					((y == 7 && _currentPiece->GetColour() == Black) ||
						(y == 0 && _currentPiece->GetColour() == White)))
				{
					promotion = 'q';
					_currentPiece->Promote();
				}
			}
			else if (_gameVariant == Makruk)
			{
				if (_currentPiece->GetType() == Pawn &&
					((y >= 5 && _currentPiece->GetColour() == Black) ||
						(y <= 2 && _currentPiece->GetColour() == White)))
				{
					promotion = 'q';
					_currentPiece->Promote();
				}
			}
			else if (std::find(std::begin(_shogiVariants), std::end(_shogiVariants), _gameVariant) != std::end(_shogiVariants))
			{
				if (_gameVariant == MiniShogi && !_currentPiece->IsPromoted())
				{
					if ((y == 4 && _currentPiece->GetColour() == Black) ||
						(y == 0 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if (_gameVariant == JudkinShogi && !_currentPiece->IsPromoted())
				{
					if ((y == 5 && _currentPiece->GetColour() == Black) ||
						(y == 0 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if ((_gameVariant == Shogi || _gameVariant == ShoShogi) && !_currentPiece->IsPromoted())
				{
					if ((y >= 6 && _currentPiece->GetColour() == Black) ||
						(y <= 2 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if (_gameVariant == ChuShogi && !_currentPiece->IsPromoted() && _currentPiece->GetType() != King &&
					_currentPiece->GetType() != Queen && _currentPiece->GetType() != Lion)
				{
					if ((y >= 8 && _currentPiece->GetColour() == Black) ||
						(y <= 3 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if (_gameVariant == DaiShogi && !_currentPiece->IsPromoted() && _currentPiece->GetType() != King &&
					_currentPiece->GetType() != Queen && _currentPiece->GetType() != Lion)
				{
					if ((y >= 10 && _currentPiece->GetColour() == Black) ||
						(y <= 4 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if (promotion == '+')
				{
					const PieceType pt = _currentPiece->GetType();
					if ((_gameVariant == MiniShogi || _gameVariant == JudkinShogi) && pt == Pawn)
					{
						_currentPiece->Promote();
					}
					else if ((_gameVariant == Shogi || _gameVariant == ShoShogi) &&
						(pt == Pawn || pt == Knight || pt == Lance) &&
						((y == 8 && _currentPiece->GetColour() == Black) || (y == 0 && _currentPiece->GetColour() == White)))
					{
						_currentPiece->Promote();
					}
					else if (_gameVariant == ChuShogi && (pt == Pawn || pt == Lance) &&
						((y == 11 && _currentPiece->GetColour() == Black) || (y == 0 && _currentPiece->GetColour() == White)))
					{
						_currentPiece->Promote();
					}
					else if (_gameVariant == DaiShogi && (pt == Pawn || pt == Lance) &&
						((y == 14 && _currentPiece->GetColour() == Black) || (y == 0 && _currentPiece->GetColour() == White)))
					{
						_currentPiece->Promote();
					}
					else
					{
						QMessageBox mb(QMessageBox::Question, "Promotion", "Would you like to promote this piece?",
							QMessageBox::Yes | QMessageBox::No, this);
						const int response = mb.exec();
						if (response == QMessageBox::Yes)
						{
							_currentPiece->Promote();
						}
						else
						{
							promotion = ' ';
						}
					}
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
			AddMove(promotion == '+' ? _board->GetData(x, y)->GetBaseType() : _board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, promotion, ct != None ? 'x' : ' ');
			_lionMovedOnce = false;
			FinishMove();
		}
	}
	else if (x == _oldX && y == _oldY && _lionMovedOnce)
	{
		if (dynamic_cast<ChuShogiBoard*>(_board)->LionMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
		{
			if (_engine != nullptr)
			{
				dynamic_cast<WbEngine*>(_engine)->Move(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
			}
			AddMove(_board->GetData(x, y)->GetType(), _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
			_lionMovedOnce = false;
			FinishMove();
		}
	}
	else if (p != nullptr && p->GetColour() == _currentPlayer)
	{
		_currentPiece = _board->GetData(x, y);
		_oldX = x;
		_oldY = y;
		_board->GetMoves(p, x, y);
		_moves = _board->Moves();
		_lionMovedOnce = false;
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
	_opponentMoves.clear();
	_gameVariant = gameVariant;
	switch (_gameVariant)
	{
	case Chess:
		_board = new ChessBoard();
		break;
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
	case DaiShogi:
		_board = new DaiShogiBoard();
		break;
	case MiniShogi:
		_board = new MiniShogiBoard();
		break;
	case JudkinShogi:
		_board = new JudkinShogiBoard();
		break;
	case Xiangqi:
		_board = new XiangqiBoard();
		break;
	case Shatranj:
		_board = new ShatranjBoard();
		break;
	case Makruk:
		_board = new MakrukBoard();
		break;
	}
	this->setFixedSize(_board->GetWidth() * 66 + 1, _board->GetHeight() * 66 + 1);
	if (this->_window != nullptr)
	{
		this->_window->setFixedSize(width() + 280, height() + 100);
		this->_textEdit->setGeometry(x() + width() + 10, y(), 250, height());
	}
}

PieceStyle VBoard::GetPieceStyle() const
{
	return _pieceStyle;
}

void VBoard::SetPieceStyle(PieceStyle pieceStyle)
{
	_pieceStyle = pieceStyle;
}

EngineOutput VBoard::GetEngineOutput() const
{
	return _engineOutput;
}

void VBoard::SetEngineOutput(EngineOutput engineOutput)
{
	_engineOutput = engineOutput;
}

PieceColour VBoard::GetCurrentPlayer() const
{
	return _currentPlayer;
}

void VBoard::SetCurrentPlayer(PieceColour currentPlayer)
{
	_moves.clear();
	_opponentMoves.clear();
	_currentPlayer = currentPlayer;
}

void VBoard::SetTextEdit(QTextEdit* textEdit)
{
	_textEdit = textEdit;
}

bool VBoard::PossibleMove(int x, int y) const
{
	return std::any_of(_moves.begin(), _moves.end(), [x, y](const std::pair<int, int>& p) {return p.first == x && p.second == y;});
}

void VBoard::RemoveMove(int x, int y)
{
	const long long cnt = static_cast<long long>(_moves.size()) - 1;
	for (long long index = cnt; index >= 0; index--)
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

void VBoard::AddMove(PieceType p, int x1, int y1, int x2, int y2, int x3, int y3) const
{
	if (_gameVariant == Chess)
	{
		dynamic_cast<ChessBoard*>(_board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (_gameVariant == Shogi)
	{
		dynamic_cast<ShogiBoard*>(_board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (_gameVariant == Xiangqi)
	{
		dynamic_cast<XiangqiBoard*>(_board)->WriteMove(p, x1, y1, x2, y2);
	}
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

QByteArray VBoard::ExtractMove(const QByteArray& buf) const
{
	QByteArray result;
	QStringList parts = QString(buf).trimmed().split(_nlre, Qt::SkipEmptyParts);
	for (auto& part : parts)
	{
		if (_engine->GetType() == XBoard ? part.startsWith("move ") : part.startsWith("bestmove "))
		{
            if (_engine->GetType() == USI)
            {
                QRegularExpressionMatch match = _sgusre.match(part);
                if (match.hasMatch())
                {
                    QString firstDigit = match.captured(1);
                    QString firstLetter = match.captured(2);
                    QString secondDigit = match.captured(3);
                    QString secondLetter = match.captured(4);
                    QString promotionChar = match.captured(5);
                    result.push_back(firstDigit[0].toLatin1());
                    result.push_back(firstLetter[0].toLatin1());
                    result.push_back(secondDigit[0].toLatin1());
                    result.push_back(secondLetter[0].toLatin1());
                    if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
                }
            }
            else if (_gameVariant == ChuShogi || _gameVariant == DaiShogi)
            {
                QRegularExpressionMatch match = _csre.match(part);
                if (match.hasMatch())
                {
                    QString firstLetter = match.captured(1);
                    QString firstDigit = match.captured(2);
                    QString secondLetter = match.captured(3);
                    QString secondDigit = match.captured(4);
                    QString promotionChar = match.captured(5);
                    result.push_back(firstLetter[0].toLatin1());
                    result.push_back(static_cast<signed char>(firstDigit.toInt()));
                    result.push_back(secondLetter[0].toLatin1());
                    result.push_back(static_cast<signed char>(secondDigit.toInt()));
                    if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
                }
            }
            else
            {
                QRegularExpressionMatch match = _gameVariant == Shogi || _gameVariant == MiniShogi || _gameVariant ==JudkinShogi
            		? _sgxbre.match(part) : _csre.match(part);
                if (match.hasMatch())
                {
                    QString firstLetter = match.captured(1);
                    QString firstDigit = match.captured(2);
                    QString secondLetter = match.captured(3);
                    QString secondDigit = match.captured(4);
                    QString promotionChar = match.captured(5);
                    result.push_back(firstLetter[0].toLatin1());
                    result.push_back(firstDigit[0].toLatin1());
                    result.push_back(secondLetter[0].toLatin1());
                    result.push_back(secondDigit[0].toLatin1());
                    if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
                }
            }
		}
        else if (_engine->GetType() == Qianhong)
        {
            QRegularExpressionMatch match = _qhre.match(part);
            if (match.hasMatch())
            {
                QString firstLetter = match.captured(1);
                QString firstDigit = match.captured(2);
                QString secondLetter = match.captured(4);
                QString secondDigit = match.captured(5);
                result.push_back(firstLetter[0].toLatin1());
                result.push_back(static_cast<signed char>(firstDigit.toInt()));
                result.push_back(secondLetter[0].toLatin1());
                result.push_back(static_cast<signed char>(secondDigit.toInt()));
            }
        }
    }
	return result;
}

void VBoard::readyReadStandardOutput()
{
	QProcess *p = dynamic_cast<QProcess*>(sender());
	const QByteArray buf = p->readAllStandardOutput();
	if (_engine->GetType() == XBoard)
	{
		const QString str = QString(buf);
		if (str.contains("setboard=0")) dynamic_cast<WbEngine*>(_engine)->SetOption("setboard", false);
		if (str.contains("setboard=1")) dynamic_cast<WbEngine*>(_engine)->SetOption("setboard", true);
		if (str.contains("memory=0")) dynamic_cast<WbEngine*>(_engine)->SetOption("memory", false);
		if (str.contains("memory=1")) dynamic_cast<WbEngine*>(_engine)->SetOption("memory", true);
		if (str.contains("usermove=0")) dynamic_cast<WbEngine*>(_engine)->SetOption("usermove", false);
		if (str.contains("usermove=1")) dynamic_cast<WbEngine*>(_engine)->SetOption("usermove", true);
	}
    int x1, y1, x2, y2;
	const QByteArray moveArray = ExtractMove(buf);
	this->_textEdit->setText(_engineOutput == Verbose ? buf : moveArray);
	if (moveArray.isEmpty()) return;
    if (_engine->GetType() == Qianhong)
    {
        x1 = moveArray[0] - 65;
        y1 = 10 - moveArray[1];
        x2 = moveArray[2] - 65;
        y2 = 10 - moveArray[3];
    }
    else if (_engine->GetType() == USI)
	{
        x1 = _board->GetWidth() - moveArray[0] + 48;
        y1 = moveArray[1] - 97;
        x2 = _board->GetWidth() - moveArray[2] + 48;
        y2 = moveArray[3] - 97;
	}
    else if (_gameVariant == ChuShogi || _gameVariant == DaiShogi)
	{
        x1 = moveArray[0] - 97;
        y1 = _board->GetWidth() - moveArray[1];
        x2 = moveArray[2] - 97;
        y2 = _board->GetWidth() - moveArray[3];
	}
    else
    {
        x1 = moveArray[0] - 97;
        y1 = _board->GetHeight() - moveArray[1] + 48;
        x2 = moveArray[2] - 97;
        y2 = _board->GetHeight() - moveArray[3] + 48;
    }
    if (_gameVariant == ChuShogi || _gameVariant == DaiShogi)
	{
		if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
		{
			if (moveArray.size() < 8)
			{
				const bool isPromoted = moveArray.size() == 5 && moveArray[4] == '+' && (y2 <= 3 || y2 >= 8);
				_board->GetMoves(_board->GetData(x1, y1), x1, y1);
				if (_board->GetData(x2, y2) != nullptr)
				{
					delete _board->GetData(x2, y2);
				}
				_board->SetData(x2, y2, _board->GetData(x1, y1));
				_board->SetData(x1, y1, nullptr);
				AddMove(_board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ' ');
				_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
				if (isPromoted)
				{
					_board->GetData(x2, y2)->Promote();
				}
			}
			else
			{
				const int x3 = moveArray[6] - 97;
				const int y3 = _board->GetWidth() - moveArray[7];
				if (_board->GetData(x2, y2) != nullptr)
				{
					delete _board->GetData(x2, y2);
				}
				if (x1 != x3 || y1 != y3)
				{
					if (_board->GetData(x3, y3) != nullptr)
					{
						delete _board->GetData(x3, y3);
					}
					_board->SetData(x3, y3, _board->GetData(x1, y1));
					_board->SetData(x1, y1, nullptr);
				}
				_board->SetData(x2, y2, nullptr);
				AddMove(_board->GetData(x3, y3)->GetType(), x1, y1, x2, y2, x3, y3);
				dynamic_cast<WbEngine*>(_engine)->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], moveArray[6], moveArray[7]);
			}
		}
	}
	else if (_gameVariant == Xiangqi)
	{
		y1--;
		y2--;
		if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
		{
			_board->GetMoves(_board->GetData(x1, y1), x1, y1);
			_board->Move(x1, y1, x2, y2);
			AddMove(_board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ' ');
			_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
	}
	else if (_gameVariant == Chess)
	{
		// Castling check
		if ((moveArray == "e8g8" || moveArray == "e8h8" || moveArray == "e8c8" || moveArray == "e8b8" || moveArray == "e8a8" ||
			moveArray == "e1g1" || moveArray == "e1h1" || moveArray == "e1c1" || moveArray == "e1b1" || moveArray == "e1a1") &&
			_board->GetData(x1, y1) != nullptr && _board->GetData(x1, y1)->GetType() == King &&
			_board->GetData(x2 > 4 ? 7 : 0, y2) != nullptr && _board->GetData(x2 > 4 ? 7 : 0, y2)->GetType() == Rook)
		{
			Piece* rook = _board->GetData(x2 > 4 ? 7 : 0, y2);
			_board->SetData(x2 > 4 ? 7 : 0, y2, _board->GetData(x1, y1));
			_board->SetData(4, y1, rook);
			dynamic_cast<ChessBoard*>(_board)->WriteMove(x1 == 7 ? "O-O" : "O-O-O");
			_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
		else if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
		{
            const bool isPromoted = moveArray.size() == 5
                && (y2 == 0 || y2 == _board->GetHeight() - 1)
				&& _board->GetData(x1, y1)->GetType() == Pawn
				&& (moveArray[4] == 'n' || moveArray[4] == 'b' || moveArray[4] == 'r' || moveArray[4] == 'q');
			_board->GetMoves(_board->GetData(x1, y1), x1, y1);
            const PieceType ct = _board->GetData(x2, y2) != nullptr ? _board->GetData(x2, y2)->GetType() : None;
			_board->Move(x1, y1, x2, y2);
			AddMove(_board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ct != None ? 'x' : ' ');
			_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
			if (isPromoted)
			{
				switch (moveArray[4])
				{
				case 'n':
					_board->GetData(x2, y2)->Promote(Knight);
					break;
				case 'b':
					_board->GetData(x2, y2)->Promote(Bishop);
					break;
				case 'r':
					_board->GetData(x2, y2)->Promote(Rook);
					break;
				case 'q':
					_board->GetData(x2, y2)->Promote(Queen);
					break;
				default:
					break;
				}
			}
		}
	}
	else if (_gameVariant == Shatranj)
	{
		if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = _board->GetData(x1, y1)->GetType() == Pawn && (y2 == 0 || y2 == _board->GetHeight() - 1);
			_board->GetMoves(_board->GetData(x1, y1), x1, y1);
			const PieceType ct = _board->GetData(x2, y2) != nullptr ? _board->GetData(x2, y2)->GetType() : None;
			_board->Move(x1, y1, x2, y2);
			AddMove(_board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
				_board->GetData(x2, y2)->Promote();
			}
		}
	}
	else if (_gameVariant == Makruk)
	{
		if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = _board->GetData(x1, y1)->GetType() == Pawn && (y2 <= 2 || y2 >= _board->GetHeight() - 3);
			_board->GetMoves(_board->GetData(x1, y1), x1, y1);
			const PieceType ct = _board->GetData(x2, y2) != nullptr ? _board->GetData(x2, y2)->GetType() : None;
			_board->Move(x1, y1, x2, y2);
			AddMove(_board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
				_board->GetData(x2, y2)->Promote();
			}
		}
	}
	else if (_gameVariant == Shogi || _gameVariant == ShoShogi || _gameVariant == MiniShogi || _gameVariant == JudkinShogi)
	{
		if ((_gameVariant == Shogi || _gameVariant == MiniShogi || _gameVariant == JudkinShogi) && (moveArray[1] == '@' || moveArray[1] == '*'))
		{
			PieceType newPiece;
			switch (moveArray[0])
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
				newPiece = Knight;
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
            dynamic_cast<ShogiVariantBoard*>(_board)->PlacePiece(newPiece, _currentPlayer, x2, y2);
            AddMove(_board->GetData(x2, y2)->GetType(), moveArray[0], moveArray[1], x2, y2, ' ', ' ');
			_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
		else if (_board->CheckPosition(x1, y1) && _board->GetData(x1, y1) != nullptr)
		{
            const bool isPromoted = moveArray.size() == 5 &&
                ((_gameVariant == MiniShogi && (y2 == 0 || y2 == 4) && moveArray[4] == '+')
				|| (_gameVariant == JudkinShogi && (y2 == 0 || y2 == 5) && moveArray[4] == '+')
                || ((_gameVariant == Shogi || _gameVariant == ShoShogi) && (y2 <= 2 || y2 >= 6) && moveArray[4] == '+'));
			_board->GetMoves(_board->GetData(x1, y1), x1, y1);
			_board->Move(x1, y1, x2, y2);
			AddMove(isPromoted ? _board->GetData(x2, y2)->GetBaseType() : _board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ' ');
			_engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
			if (isPromoted)
			{
				_board->GetData(x2, y2)->Promote();
			}
		}
	}
	_currentPlayer = White;
	this->_statusBar->showMessage(_gameVariant == Xiangqi ? "Red move" : "White move");
	this->repaint();
}

void VBoard::readyReadStandardError() const
{
	QProcess *p = dynamic_cast<QProcess*>(sender());
	const QByteArray buf = p->readAllStandardError();
	this->_textEdit->setHtml("<p style='color:red'>" + buf + "</p>");
}

void VBoard::contextMenuEvent(QContextMenuEvent* event)
{
	if (_gameVariant != Shogi && _gameVariant != MiniShogi && _gameVariant != JudkinShogi) return;

	QMenu menu(this);

	const auto cps = dynamic_cast<ShogiVariantBoard*>(_board)->GetCapturedPieces(_currentPlayer);
	for (const auto cp : cps)
	{
		ShogiPiece p(cp, _currentPlayer);
		std::string str = p.LongStringCode() + " (" + p.KanjiStringCode() + ")";
		menu.addAction(QString::fromStdString(str));
	}

	// Execute the menu at the cursor position
	const QAction* selectedAction = menu.exec(event->globalPos());

	// Handle the selected action
	if (selectedAction != nullptr)
	{
		const std::string longStringCode = selectedAction->text().split(' ', Qt::SkipEmptyParts)[0].toStdString();
		const PieceType newPiece = ShogiPiece::LongStringCode2PieceType(longStringCode);

		const int w = this->size().width() / _board->GetWidth();
		const int h = this->size().height() / _board->GetHeight();
		const int x = event->x() / w;
		const int y = event->y() / h;
		if (_board->GetData(x, y) != nullptr)
		{
			QMessageBox mb(QMessageBox::Warning, "Illegal drop", "Square is already occupied",
				QMessageBox::Ok, this);
			mb.exec();
			return;
		}
		if (newPiece == Pawn)
		{
			if ((_currentPlayer == White && y == 0) || (_currentPlayer == Black && y == _board->GetHeight() - 1))
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot place pawn on the last row",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
			if ((_currentPlayer == White && _board->GetData(x, y - 1) != nullptr && _board->GetData(x, y - 1)->GetType() == King) ||
				(_currentPlayer == Black && _board->GetData(x, y + 1) != nullptr && _board->GetData(x, y + 1)->GetType() == King))
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot check king by the pawn drop",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
			for (int index = 0; index < _board->GetHeight(); index++)
			{
				if (_board->GetData(x, index) != nullptr && _board->GetData(x, index)->GetType() == Pawn)
				{
					QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot place second pawn on the same column",
						QMessageBox::Ok, this);
					mb.exec();
					return;
				}
			}
		}
		else if (newPiece == Lance)
		{
			if ((_currentPlayer == White && y == 0) || (_currentPlayer == Black && y == _board->GetHeight() - 1))
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot place lance on the last row",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
		}
		else if (newPiece == Knight)
		{
			if ((_currentPlayer == White && y <= 1) || (_currentPlayer == Black && y >= _board->GetHeight() - 2))
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot place knight on the last two rows",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
		}
		dynamic_cast<ShogiVariantBoard*>(_board)->PlacePiece(newPiece, _currentPlayer, x, y);
		Piece* p = _board->GetData(x, y);
		const char sc = p->StringCode()[0];
		if (_engine != nullptr)
		{
			if (_engine->GetType() == USI)
				_engine->Move(sc, '*', _board->GetWidth() - x, y, ' ');
			else
				_engine->Move(sc, '@', x, _board->GetHeight() - y, ' ');
		}
		AddMove(newPiece, sc, '*', x, y, ' ', ' ');
		dynamic_cast<ShogiVariantBoard*>(_board)->RemoveCapturedPiece(newPiece, _currentPlayer);
		FinishMove();
	}
}
