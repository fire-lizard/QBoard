#include "vboard.h"

VBoard::VBoard(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_Hover, true);
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
	else if (_pieceStyle == Mnemonic && _gameVariant == ChuShogi)
	{
		resourcePrefix = ":/pieces_chu/images_chu/";
	}
	else if (_pieceStyle == Asian && _gameVariant == DaiShogi)
	{
		resourcePrefix = ":/pieces_dai/images_dai/";
	}
	else if (_pieceStyle == Asian && (_gameVariant == Shogi || _gameVariant == ShoShogi || _gameVariant == MiniShogi || _gameVariant == JudkinShogi))
    {
        resourcePrefix = ":/pieces_sho/images_sho/";
    }
	else if (_pieceStyle == Asian && (_gameVariant == WaShogi || _gameVariant == CrazyWa))
	{
		resourcePrefix = ":/pieces_wa2/images_wa2/";
	}
	else if (_gameVariant == WaShogi || _gameVariant == CrazyWa)
	{
		resourcePrefix = ":/pieces_wa/images_wa/";
	}
	else if (_pieceStyle == Asian && _gameVariant == TenjikuShogi)
	{
		resourcePrefix = ":/pieces_tnk/images_tnk/";
	}
	else if (_gameVariant == TenjikuShogi)
	{
		resourcePrefix = ":/pieces_ten/images_ten/";
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
					if (((abs(_oldX - i) == 2 || abs(_oldY - j) == 2) && (_currentPiece->GetType() == Lion || _currentPiece->GetType() == LionHawk)) ||
						(abs(_oldX - i) == 2 && _oldY - j == 2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == White) ||
						(abs(_oldX - i) == 2 && _oldY - j == -2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == Black) ||
						(_oldX == i && _oldY - j == 2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == White) ||
						(_oldX == i && _oldY - j == -2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == Black))
					{
						if (_board->GetData(i, j) != nullptr)
						{
							painter.setBrush(QColorConstants::Svg::lightpink);
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
					else if (i == _oldX && j == _oldY)
					{
						if (_board->GetData(i, j) != nullptr)
						{
							painter.setBrush(Qt::blue);
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
					if (_board->GetData(i, j)->GetColour() != _currentPlayer)
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
			else if (std::any_of(_attackers.begin(), _attackers.end(), [=](std::pair<int, int> t) {return t.first == i && t.second == j;}))
			{
				painter.setBrush(QColorConstants::Svg::salmon);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else if (std::any_of(_defenders.begin(), _defenders.end(), [=](std::pair<int, int> t) {return t.first == i && t.second == j;}))
			{
				painter.setBrush(QColorConstants::Svg::aquamarine);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			// En Passant square highlighting
			/*else if (_gameVariant == Chess && dynamic_cast<ChessBoard*>(_board)->GetEnPassant() != "-" &&
				dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[0] - 97 == i &&
				(_currentPlayer == White && dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[1] - 49 == j || _currentPlayer == Black && dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[1] - 46 == j))
			{
				painter.setBrush(QColorConstants::blue);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}*/
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
				if (_pieceStyle == Asian && _gameVariant == TenjikuShogi)
				{
					imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
				}
				else if (_gameVariant == TenjikuShogi)
				{
					imageFileName = p->GetImageFileName();
				}
				else if (_pieceStyle == Asian && (_gameVariant == Xiangqi || std::find(std::begin(_shogiVariants), std::end(_shogiVariants), _gameVariant) != std::end(_shogiVariants)))
				{
					imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
				}
				else if (_pieceStyle == Mnemonic && _gameVariant == ChuShogi)
				{
					imageFileName = dynamic_cast<ChuShogiPiece*>(p)->GetMnemonicImageFileName();
				}
				else
				{
					imageFileName = p->GetImageFileName();
				}
				QPixmap pixmap(resourcePrefix + QString::fromStdString(imageFileName));
				if (_pieceStyle == Asian && (_gameVariant == Shogi || _gameVariant == ShoShogi || _gameVariant == MiniShogi || _gameVariant == JudkinShogi || _gameVariant == ChuShogi || _gameVariant == DaiShogi))
				{
					painter.drawPixmap(i * w + w / 8, j * h + h / 8, 48, 48, pixmap);
				}
				else if (_gameVariant == WaShogi || _gameVariant == CrazyWa)
				{
					painter.drawPixmap(i * w + w / 8, j * h + h / 8, pixmap.size().width(), pixmap.size().height(), pixmap);
				}
				else
				{
					painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
				}
			}
		}
	}
}

void VBoard::FinishMove()
{
	if (_currentPlayer == White)
	{
		_whiteMoves.push_back(_board->GetFEN());
	}
	else
	{
		_blackMoves.push_back(_board->GetFEN());
	}
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
	if ((_blackEngine != nullptr && _blackEngine->IsActive() && _currentPlayer == Black) ||
		(_whiteEngine != nullptr && _whiteEngine->IsActive() && _currentPlayer == White)) return;
	std::shared_ptr<Engine> engine = _currentPlayer == White ? _blackEngine : _whiteEngine;
	const int w = this->size().width() / _board->GetWidth();
	const int h = this->size().height() / _board->GetHeight();
	const int x = static_cast<int>(event->position().x()) / w;
	const int y = static_cast<int>(event->position().y()) / h;
	Piece* p = _board->GetData(x, y);
	const PieceType ct = p != nullptr ? p->GetType() : None;
	bool isLionPiece = _currentPiece != nullptr && std::find(std::begin(_lionPieces), std::end(_lionPieces), _currentPiece->GetType()) != std::end(_lionPieces);
	// Castling check
	if (_gameVariant == Chess && _currentPiece != nullptr && _currentPiece->GetType() == King && !dynamic_cast<ChessPiece*>(_currentPiece)->HasMoved() &&
		p != nullptr && p->GetColour() == _currentPlayer && p->GetType() == Rook && !dynamic_cast<ChessPiece*>(p)->HasMoved())
	{
		_board->SetData(x, y, _currentPiece);
		_board->SetData(4, y, p);
		if (engine != nullptr && engine->IsActive())
		{
			engine->Move(_oldX, _board->GetHeight() - _oldY, x == 7 ? 6 : 2, _board->GetHeight() - y, ' ');
		}
		dynamic_cast<ChessBoard*>(_board)->WriteMove(x == 7 ? "O-O" : "O-O-O");
		FinishMove();
	}
	else if ((_gameVariant == ChuShogi || _gameVariant == DaiShogi || _gameVariant == TenjikuShogi) && _currentPiece != nullptr &&
		(isLionPiece || _currentPiece->GetType() == ViceGeneral || _currentPiece->GetType() == FireDemon || _currentPiece->GetType() == HeavenlyTetrarch) &&
		p != nullptr && p->GetColour() == _currentPlayer && x == _oldX && y == _oldY)
	{
		if (dynamic_cast<ChuShogiBoard*>(_board)->IsMovePossible(x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y, ' ');
			}
			FinishMove();
		}
	}
	else if (_currentPiece != nullptr && (p == nullptr || p->GetColour() != _currentPlayer))
	{
		// TODO: Shogi repetition rule
		/*if (_currentPlayer == White)
		{
			if (std::any_of(_whiteMoves.begin(), _whiteMoves.end(), [=](const std::string t) {return *_board == t; }))
			{
				//
			}
		}
		else
		{
			if (std::any_of(_blackMoves.begin(), _blackMoves.end(), [=](const std::string t) {return *_board == t; }))
			{
				//
			}
		}*/
		// Lion move
		if (isLionPiece && !_lionMovedOnce)
		{
			if (((abs(_oldX - x) >= 2 || abs(_oldY - y) >= 2) && (_currentPiece->GetType() == Lion || _currentPiece->GetType() == LionHawk)) ||
				(abs(_oldX - x) == 2 && _oldY - y == 2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == White) ||
				(abs(_oldX - x) == 2 && _oldY - y == -2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == Black) ||
				(_oldX == x && _oldY - y == 2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == White) ||
				(_oldX == x && _oldY - y == -2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == Black))
			{
				// Lion capture rule #1
				if ((abs(_oldX - x) == 2 || abs(_oldY - y) == 2) && _currentPiece->GetType() == Lion &&
					_board->GetData(x, y) != nullptr && _board->GetData(x, y)->GetType() == Lion)
				{
					std::vector<std::pair<int, int>> lionDefenders;
					_board->GetDefenders(x, y, lionDefenders);
					if (!lionDefenders.empty())
					{
						return;
					}
				}
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, ' ', ' ');
					FinishMove();
				}
			}
			else if (_board->GetData(x, y) == nullptr)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, ' ', ' ');
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
		else if (isLionPiece && _lionMovedOnce)
		{
			if (dynamic_cast<ChuShogiBoard*>(_board)->LionMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
			{
				if (engine != nullptr && engine->IsActive())
				{
					std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
				}
				EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->GetType(), _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
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
				if (_gameVariant == MiniShogi && !_currentPiece->IsPromoted() &&
					_currentPiece->GetType() != King && _currentPiece->GetType() != Gold &&
					_currentPiece->GetType() != DragonKing && _currentPiece->GetType() != DragonHorse)
				{
					if ((y == 4 && _currentPiece->GetColour() == Black) ||
						(y == 0 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if (_gameVariant == JudkinShogi && !_currentPiece->IsPromoted() &&
					_currentPiece->GetType() != King && _currentPiece->GetType() != Gold &&
					_currentPiece->GetType() != DragonKing && _currentPiece->GetType() != DragonHorse)
				{
					if ((y == 5 && _currentPiece->GetColour() == Black) ||
						(y == 0 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if ((_gameVariant == Shogi || _gameVariant == ShoShogi) && !_currentPiece->IsPromoted() &&
					_currentPiece->GetType() != King && _currentPiece->GetType() != Gold &&
					_currentPiece->GetType() != DragonKing && _currentPiece->GetType() != DragonHorse)
				{
					if ((y >= 6 && _currentPiece->GetColour() == Black) ||
						(y <= 2 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if ((_gameVariant == WaShogi || _gameVariant == CrazyWa) && !_currentPiece->IsPromoted() &&
					_currentPiece->GetType() != King && _currentPiece->GetType() != CloudEagle && _currentPiece->GetType() != TreacherousFox)
				{
					if ((y >= 8 && _currentPiece->GetColour() == Black) ||
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
				if (_gameVariant == DaiShogi &&	!_currentPiece->IsPromoted() && _currentPiece->GetType() != King &&
					_currentPiece->GetType() != Queen && _currentPiece->GetType() != Lion)
				{
					if ((y >= 10 && _currentPiece->GetColour() == Black) ||
						(y <= 4 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if (_gameVariant == TenjikuShogi &&	!_currentPiece->IsPromoted() && _currentPiece->GetType() != King &&
					_currentPiece->GetType() != Queen && _currentPiece->GetType() != Lion && _currentPiece->GetType() != LionHawk &&
					_currentPiece->GetType() != ViceGeneral && _currentPiece->GetType() != GreatGeneral &&
					_currentPiece->GetType() != FireDemon && _currentPiece->GetType() != FreeEagle)
				{
					if ((y >= 11 && _currentPiece->GetColour() == Black) ||
						(y <= 4 && _currentPiece->GetColour() == White))
					{
						promotion = '+';
					}
				}
				if (promotion == '+')
				{
					const PieceType pt = _currentPiece->GetType();
					if ((pt == Pawn || pt == Knight || pt == Lance) &&
						((y == _board->GetHeight() -1 && _currentPiece->GetColour() == Black) || (y == 0 && _currentPiece->GetColour() == White)))
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
			if (engine != nullptr && engine->IsActive())
			{
				if (_gameVariant == Xiangqi)
					engine->Move(_oldX, _board->GetHeight() - _oldY - 1, x, _board->GetHeight() - y - 1, promotion);
				else if (engine->GetType() == USI)
					engine->Move(_board->GetWidth() - _oldX, _oldY, _board->GetWidth() - x, y, promotion);
				else
					engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y, promotion);
			}
			if (_board->GetData(x, y) != nullptr)
			{
				EngineOutputHandler::AddMove(_board, _gameVariant, promotion == '+' ? _board->GetData(x, y)->GetBaseType() : _board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, promotion, ct != None ? 'x' : ' ');
			}
			_lionMovedOnce = false;
			FinishMove();
		}
	}
	else if (x == _oldX && y == _oldY && _lionMovedOnce)
	{
		if (dynamic_cast<ChuShogiBoard*>(_board)->LionMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
			}
			EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->GetType(), _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
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
		if (std::find(std::begin(_shogiVariants), std::end(_shogiVariants), _gameVariant) == std::end(_shogiVariants))
		{
			std::for_each(_moves.begin(), _moves.end(), [=](std::pair<int, int> t)
			{
				CalculateCheck(x, y, t.first, t.second);
			});
			std::for_each(_moves.begin(), _moves.end(), [=](std::pair<int, int> t)
			{
				CalculateCheck(x, y, t.first, t.second);
			});
		}
		this->repaint();
	}
}

bool VBoard::event(QEvent* event)
{
	if (event->type() == QEvent::HoverMove && std::find(std::begin(_shogiVariants), std::end(_shogiVariants), _gameVariant) != std::end(_shogiVariants))
	{
		QHoverEvent* hoverEvent = static_cast<QHoverEvent*>(event);
		const int w = this->size().width() / _board->GetWidth();
		const int h = this->size().height() / _board->GetHeight();
		const int x = static_cast<int>(hoverEvent->position().x()) / w;
		const int y = static_cast<int>(hoverEvent->position().y()) / h;
		if (x < _board->GetWidth() && y < _board->GetHeight() && (x != _px || y != _py))
		{
			_px = x;
			_py = y;
			Piece* p = _board->GetData(x, y);
			if (p != nullptr)
			{
				_board->GetAttackers(x, y, _attackers);
				_board->GetDefenders(x, y, _defenders);
			}
			else
			{
				_attackers.clear();
				_defenders.clear();
			}
			this->repaint();
		}
	}
	return QWidget::event(event); // Call base class implementation
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
	if (_whiteEngine != nullptr)
	{
		_whiteEngine->SetActive(false);
	}
	if (_blackEngine != nullptr)
	{
		_blackEngine->SetActive(false);
	}
	_currentPiece = nullptr;
	_moves.clear();
	_opponentMoves.clear();
	_attackers.clear();
	_defenders.clear();
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
	case TenjikuShogi:
		_board = new TenjikuShogiBoard();
		break;
	case MiniShogi:
		_board = new MiniShogiBoard();
		break;
	case JudkinShogi:
		_board = new JudkinShogiBoard();
		break;
	case WaShogi:
		_board = new WaShogiBoard();
		dynamic_cast<ShogiBoard*>(_board)->SetDrops(false);
		break;
	case CrazyWa:
		_board = new WaShogiBoard();
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
	int s = _gameVariant == TenjikuShogi ? 56 : _gameVariant == DaiShogi ? 60 : 66;
	this->setFixedSize(_board->GetWidth() * s + 1, _board->GetHeight() * s + 1);
	if (this->_window != nullptr)
	{
		this->_window->setFixedSize(width() + 280, height() + 100);
		this->_textEdit->setGeometry(x() + width() + 10, y(), 250, height() / 2);
		this->_textEdit2->setGeometry(x() + width() + 10, y() + 2 + height() / 2, 250, height() / 2);
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

void VBoard::SetTextEdit2(QTextEdit* textEdit)
{
	_textEdit2 = textEdit;
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
	if (board->GetData(oldX, oldY)->GetBaseType() == King)
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
				if (p != nullptr && p->GetBaseType() == King && p->GetColour() == _currentPlayer)
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

void VBoard::SetStatusBar(QStatusBar *statusBar)
{
	_statusBar = statusBar;
}

void VBoard::SetMainWindow(QMainWindow *window)
{
	_window = window;
}

void VBoard::SetWhiteEngine(std::shared_ptr<Engine> engine)
{
	_whiteEngine = engine;
}

void VBoard::SetBlackEngine(std::shared_ptr<Engine> engine)
{
	_blackEngine = engine;
}

void VBoard::whiteEngineReadyReadStandardOutput()
{
	QProcess* p = dynamic_cast<QProcess*>(sender());
	EngineOutputHandler::ReadStandardOutput(p, _whiteEngine, _board, _textEdit2, _gameVariant, _engineOutput, _currentPlayer);
	if (_blackEngine != nullptr && _blackEngine->IsActive())
	{
		_blackEngine->Move();
	}
	else 
	{
		_currentPlayer = Black;
	}
	this->_statusBar->showMessage("Black move");
	this->repaint();
}

void VBoard::whiteEngineReadyReadStandardError() const
{
	EngineOutputHandler::ReadStandardError(dynamic_cast<QProcess*>(sender()), this->_textEdit2);
}

void VBoard::blackEngineReadyReadStandardOutput()
{
	QProcess *p = dynamic_cast<QProcess*>(sender());
	EngineOutputHandler::ReadStandardOutput(p, _blackEngine, _board, _textEdit, _gameVariant, _engineOutput, _currentPlayer);
	if (_whiteEngine != nullptr && _whiteEngine->IsActive())
	{
		_whiteEngine->Move();
	}
	else
	{
		_currentPlayer = White;
	}
	this->_statusBar->showMessage(_gameVariant == Xiangqi ? "Red move" : "White move");
	this->repaint();
}

void VBoard::blackEngineReadyReadStandardError() const
{
	EngineOutputHandler::ReadStandardError(dynamic_cast<QProcess*>(sender()), this->_textEdit);
}

void VBoard::contextMenuEvent(QContextMenuEvent* event)
{
	if (_gameVariant != Shogi && _gameVariant != MiniShogi && _gameVariant != JudkinShogi && _gameVariant != CrazyWa) return;
	if ((_blackEngine != nullptr && _blackEngine->IsActive() && _currentPlayer == Black) ||
		(_whiteEngine != nullptr && _whiteEngine->IsActive() && _currentPlayer == White)) return;

	QMenu menu(this);

	const auto cps = dynamic_cast<ShogiVariantBoard*>(_board)->GetCapturedPieces(_currentPlayer);
	for (const auto cp : cps)
	{
		std::string str;
		if (_gameVariant == CrazyWa)
		{
			WaShogiPiece p(cp, _currentPlayer);
			str = p.LongStringCode() + " (" + p.KanjiStringCode() + ")";
		}
		else
		{
			ShogiPiece p(cp, _currentPlayer);
			str = p.LongStringCode() + " (" + p.KanjiStringCode() + ")";
		}
		menu.addAction(QString::fromStdString(str));
	}

	// Execute the menu at the cursor position
	const QAction* selectedAction = menu.exec(event->globalPos());

	// Handle the selected action
	if (selectedAction != nullptr)
	{
		QStringList parts = selectedAction->text().split(' ', Qt::SkipEmptyParts);
		const std::string longStringCode = _gameVariant == CrazyWa && selectedAction->text() != "Oxcart" ?
			(parts[0] + " " + parts[1]).toStdString() : parts[0].toStdString();
		const PieceType newPiece = _gameVariant == CrazyWa ? 
			WaShogiPiece::LongStringCode2PieceType(longStringCode) : ShogiPiece::LongStringCode2PieceType(longStringCode);

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
			Piece* kp = _currentPlayer == White ? _board->GetData(x, y - 1) : _board->GetData(x, y + 1);
			if (kp != nullptr && kp->GetType() == King && kp->GetColour() != _currentPlayer)
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot check king by the pawn drop",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
			for (int index = 0; index < _board->GetHeight(); index++)
			{
				Piece* p = _board->GetData(x, index);
				if (p != nullptr && p->GetType() == Pawn && p->GetColour() == _currentPlayer)
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
		std::shared_ptr<Engine> engine = _currentPlayer == White ? _blackEngine : _whiteEngine;
		if (engine != nullptr && engine->IsActive())
		{
			if (engine->GetType() == USI)
				engine->Move(sc, '*', _board->GetWidth() - x, y, ' ');
			else
				engine->Move(sc, '@', x, _board->GetHeight() - y, ' ');
		}
		EngineOutputHandler::AddMove(_board, _gameVariant, newPiece, sc, '*', x, y, ' ', ' ');
		dynamic_cast<ShogiVariantBoard*>(_board)->RemoveCapturedPiece(newPiece, _currentPlayer);
		FinishMove();
	}
}
