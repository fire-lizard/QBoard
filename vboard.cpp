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
	bool isAsianStyle = _pieceStyle == Asian || _pieceStyle == Asian2 || _pieceStyle == Asian3 || _pieceStyle == Asian4;
	switch (_gameVariant)
	{
	case Xiangqi:
		if (_pieceStyle == European) resourcePrefix = ":/pieces_eur/images/";
		else if (_pieceStyle == Mnemonic) resourcePrefix = ":/pieces_xia/images_xia/";
		else if (_pieceStyle == Asian) resourcePrefix = ":/pieces_chi/images_chi/";
		else resourcePrefix = ":/pieces_chi2/images_chi2/";
		break;
	case Shogi:
	case ShoShogi:
	case MiniShogi:
	case JudkinShogi:
		if (_pieceStyle == European) resourcePrefix = ":/pieces_eur/images/";
		else if (_pieceStyle == Mnemonic) resourcePrefix = ":/pieces_sho2/images_sho2/";
		else if (_pieceStyle == Asian) resourcePrefix = ":/pieces_sho/images_sho/";
		else if (_pieceStyle == Asian2) resourcePrefix = ":/pieces_sho3/images_sho3/";
		else resourcePrefix = ":/pieces_maka2/images_maka2/";
		break;
	case ChuShogi:
		if (_pieceStyle == Asian) resourcePrefix = ":/pieces_tnk/images_tnk/";
		else if (_pieceStyle == Asian2) resourcePrefix = ":/pieces_maka2/images_maka2/";
		else if (_pieceStyle == Asian3) resourcePrefix = ":/pieces_knj/images_knj/";
		else if (_pieceStyle == Asian4) resourcePrefix = ":/pieces_jap/images_jap/";
		else if (_pieceStyle == Mnemonic) resourcePrefix = ":/pieces_chu/images_chu/";
		else resourcePrefix = ":/pieces_eur/images/";
		break;
	case DaiShogi:
		if (_pieceStyle == Asian) resourcePrefix = ":/pieces_tnk/images_tnk/";
		else if (_pieceStyle == Asian2 || _pieceStyle == Asian4) resourcePrefix = ":/pieces_maka2/images_maka2/";
		else if (_pieceStyle == Asian3) resourcePrefix = ":/pieces_dai/images_dai/";
		else resourcePrefix = ":/pieces_eur/images/";
		break;
	case TenjikuShogi:
		resourcePrefix = isAsianStyle ? ":/pieces_tnk/images_tnk/" : ":/pieces_ten/images_ten/";
		break;
	case WaShogi:
	case CrazyWa:
		resourcePrefix = isAsianStyle ? ":/pieces_wa2/images_wa2/" : ":/pieces_wa/images_wa/";
		break;
	case DaiDaiShogi:
		resourcePrefix = ":/pieces_dd/images_daidai/";
		break;
	case MakaDaiDaiShogi:
		resourcePrefix = _pieceStyle == Asian ? ":/pieces_mdd/images_maka/" : ":/pieces_maka2/images_maka2/";
		break;
	case KoShogi:
		if (_pieceStyle == Asian) resourcePrefix = ":/pieces_ko/images_ko/";
		else if (isAsianStyle) resourcePrefix = ":/pieces_kok/images_kok/";
		else if (_pieceStyle == Mnemonic) resourcePrefix = ":/pieces_km/images_kom/";
		else resourcePrefix = ":/pieces_kow/images_kow/";
		break;
	case Chess:
	case Shatranj:
		if (_pieceStyle == European) resourcePrefix = ":/pieces_eur/images/";
		else if (_pieceStyle == Mnemonic) resourcePrefix = ":/pieces_eur/images_eur/";
		else resourcePrefix = ":/pieces_eur2/images_eur2/";
		break;
	case Makruk:
		resourcePrefix = ":/pieces_eur/images/";
		break;
	}
	QPainter painter(this);
	painter.setPen(_editorMode ? Qt::magenta : Qt::black);
	painter.setBrush(Qt::NoBrush);

	const QSize s = this->size();
	const int w = s.width() / _board->GetWidth();
	const int h = s.height() / _board->GetHeight();
	for (int i = 0; i < _board->GetWidth(); i++)
	{
		for (int j = 0; j < _board->GetHeight(); j++)
		{
			QRect rect(i * w, j * h, w, h);
			if (std::find(std::begin(_tcMoves), std::end(_tcMoves), std::pair<int, int>(i, j)) != std::end(_tcMoves) ||
				_lionFirstMove.first == i && _lionFirstMove.second == j || _lionSecondMove.first == i && _lionSecondMove.second == j ||
				_firstShoot.first == i && _firstShoot.second == j)
			{
				painter.setBrush(QColorConstants::Svg::yellow);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else if (PossibleMove(i, j) && _highlightMoves)
			{
				if (_currentPiece != nullptr && std::find(std::begin(lionPieces), std::end(lionPieces), _currentPiece->GetType()) != std::end(lionPieces))
				{
					// Lion move highlighting
					if (_gameVariant == KoShogi && !_lionMovedOnce && EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, i, j))
					{
						const bool lcond1 = (abs(_oldX - i) == 2 || abs(_oldY - j) == 2) &&
							(_currentPiece->GetType() == Lion || _currentPiece->GetType() == WingedTiger ||
								_currentPiece->GetType() == FlyingHawk || _currentPiece->GetType() == RisingDragon);
						const bool lcond2 = abs(_oldX - i) == 1 && abs(_oldY - j) == 1 && _currentPiece->GetType() == FlyingHawk;
						const bool lcond3 = (abs(_oldX - i) == 4 || abs(_oldY - j) == 4) &&
							(_currentPiece->GetType() == KnightCaptain || _currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight);
						const bool lcond4 = abs(_oldX - i) + abs(_oldY - j) > 2 && _currentPiece->GetType() == DoubleKylin;
						const bool lcond5 = (abs(_oldX - i) > 2 || abs(_oldY - j) > 2 ||
							abs(_oldX - i) + abs(_oldY - j) > 1 && abs(_oldX - i) != abs(_oldY - j) ||
							abs(_oldX - i) == 1 && abs(_oldY - j) == 1) && _currentPiece->GetType() == DoublePhoenix;
						const bool lcond6 = !(abs(_oldX - i) == 2 && abs(_oldY - j) == 1 || abs(_oldX - i) == 1 && abs(_oldY - j) == 2) &&
							_currentPiece->GetType() == WingedHorse;
						const bool lcond7 = _tcMoves.empty() && (abs(_oldX - i) > 1 || abs(_oldY - j) > 1) &&
							_currentPiece->GetType() == Thunderclap;
						const bool lcond8 = !_tcMoves.empty() && 
							(abs(_tcMoves[_tcMoves.size() - 1].first - i) > 1 || abs(_tcMoves[_tcMoves.size() - 1].second - j) > 1) &&
							_currentPiece->GetType() == Thunderclap;
						if ((lcond1 || lcond2 || lcond3 || lcond4 || lcond5 || lcond6 || lcond7 || lcond8) && _board->GetData(i, j) != nullptr)
						{
							painter.setBrush(QColorConstants::Svg::lightpink);
							painter.drawRect(rect);
							painter.setBrush(Qt::NoBrush);
						}
						else if ((lcond1 || lcond2 || lcond3 || lcond4 || lcond5 || lcond6 || lcond7 || lcond8) && _board->GetData(i, j) == nullptr)
						{
							painter.setBrush(QColorConstants::Svg::greenyellow);
							painter.drawRect(rect);
							painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) != nullptr)
						{
							painter.setBrush(QColorConstants::Svg::hotpink);
							painter.drawRect(rect);
							painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) == nullptr)
						{
							painter.setBrush(QColorConstants::Svg::lightgreen);
							painter.drawRect(rect);
							painter.setBrush(Qt::NoBrush);
						}
					}
					else if (EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, i, j))
					{
						if (_board->GetData(i, j) != nullptr)
						{
							painter.setBrush(QColorConstants::Svg::hotpink);
							painter.drawRect(rect);
							painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) == nullptr)
						{
							painter.setBrush(QColorConstants::Svg::lightgreen);
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
				else if (_currentPiece != nullptr && _currentPiece->GetType() == HeavenlyTetrarch &&
					abs(_oldX - i) + abs(_oldY - j) >= 1 && abs(_oldX - i) + abs(_oldY - j) <= 2)
				{
					if (_board->GetData(i, j) != nullptr)
					{
						painter.setBrush(QColorConstants::Svg::orange);
						painter.drawRect(rect);
						painter.setBrush(Qt::NoBrush);
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
			else if (std::any_of(_shoots.begin(), _shoots.end(), [=](std::pair<int, int> t) {return t.first == i && t.second == j;}) && _highlightShoots)
			{
				painter.setBrush(QColorConstants::Svg::violet);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else if (std::any_of(_attackers.begin(), _attackers.end(), [=](std::pair<int, int> t) {return t.first == i && t.second == j;}) && _highlightAttackers)
			{
				painter.setBrush(QColorConstants::Svg::salmon);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else if (std::any_of(_defenders.begin(), _defenders.end(), [=](std::pair<int, int> t) {return t.first == i && t.second == j;}) && _highlightDefenders)
			{
				painter.setBrush(QColorConstants::Svg::aquamarine);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else if ((_lastWhiteMoveFrom.first == i && _lastWhiteMoveFrom.second == j || _lastWhiteMoveTo.first == i && _lastWhiteMoveTo.second == j) && _highlightLastMoves)
			{
				painter.setBrush(QColor(245, 245, 220, 127));
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else if ((_lastBlackMoveFrom.first == i && _lastBlackMoveFrom.second == j || _lastBlackMoveTo.first == i && _lastBlackMoveTo.second == j) && _highlightLastMoves)
			{
				painter.setBrush(QColor(255, 228, 196, 127));
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			// En Passant square highlighting
			else if (_gameVariant == Chess && dynamic_cast<ChessBoard*>(_board)->GetEnPassant() != "-" &&
				dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[0] - 97 == i &&
				(_currentPlayer == White && dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[1] - 48 == j || _currentPlayer == Black && dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[1] - 47 == j))
			{
				painter.setBrush(Qt::blue);
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
				switch (_gameVariant)
				{
				case Xiangqi:
					imageFileName = _pieceStyle == European ?
						p->GetImageFileName() : dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
					break;
				case Shogi:
				case ShoShogi:
				case MiniShogi:
				case JudkinShogi:
					if (_pieceStyle == Asian) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
					else if (_pieceStyle == Asian3 || _pieceStyle == Asian4) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
					else imageFileName = p->GetImageFileName();
					break;
				case DaiShogi:
					if (_pieceStyle == Asian) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
					else if (_pieceStyle == Asian2 || _pieceStyle == Asian4) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
					else imageFileName = p->GetImageFileName();
					break;
				case MakaDaiDaiShogi:
					imageFileName = _pieceStyle == Asian ?
						dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName() : dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
					break;
				case KoShogi:
					imageFileName = _pieceStyle == Asian || _pieceStyle == Mnemonic ?
						dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName() :
						isAsianStyle ? dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2() : dynamic_cast<ChuShogiPiece*>(p)->GetMnemonicImageFileName();
					break;
				case ChuShogi:
					if (_pieceStyle == Asian) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
					else if (_pieceStyle == Asian2) imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName2();
					else if (_pieceStyle == Asian3) imageFileName = "J" + dynamic_cast<ChuShogiPiece*>(p)->GetMnemonicImageFileName();
					else if (_pieceStyle == Mnemonic) imageFileName = dynamic_cast<ChuShogiPiece*>(p)->GetMnemonicImageFileName();
					else imageFileName = p->GetImageFileName();
					break;
				case TenjikuShogi:
				case WaShogi:
				case CrazyWa:
					imageFileName = isAsianStyle ?
						dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName() : p->GetImageFileName();
					break;
				case DaiDaiShogi:
					imageFileName = dynamic_cast<KanjiPiece*>(p)->GetKanjiImageFileName();
					break;
				case Chess:
				case Shatranj:
				case Makruk:
					imageFileName = p->GetImageFileName();
					break;
				}
				QPixmap pixmap(resourcePrefix + QString::fromStdString(imageFileName));
				switch (_gameVariant)
				{
				case Shogi:
				case ShoShogi:
				case MiniShogi:
				case JudkinShogi:
					if (isAsianStyle)
					{
						painter.drawPixmap(i * w + w / 8, j * h + h / 8, 48, 48, pixmap);
					}
					else
					{
						painter.drawPixmap(i* w + w / 4, j* h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					break;
				case MakaDaiDaiShogi:
					if (_pieceStyle == Asian)
					{
						painter.drawPixmap(i* w + w / 4, j* h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					else
					{
						painter.drawPixmap(i* w + w / 8, j* h + h / 8, 40, 40, pixmap);
					}
					break;
				case KoShogi:
					painter.drawPixmap(i * w + w / 20, j * h + h / 20, pixmap.size().width(), pixmap.size().height(), pixmap);
					break;
				case ChuShogi:
				case DaiShogi:
					if (_pieceStyle == Asian2 || _pieceStyle == Asian4)
					{
						painter.drawPixmap(i * w + w / 8, j * h + h / 8, 48, 48, pixmap);
					}
					else if (_pieceStyle == Asian3 && _gameVariant == DaiShogi)
					{
						painter.drawPixmap(i * w + w / 6, j * h + h / 6, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					else
					{
						painter.drawPixmap(i* w + w / 4, j* h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					break;
				case WaShogi:
				case CrazyWa:
					painter.drawPixmap(i * w + w / 8, j * h + h / 8, pixmap.size().width(), pixmap.size().height(), pixmap);
					break;
				case TenjikuShogi:
				case DaiDaiShogi:
				case Makruk:
					painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
					break;
				case Chess:
				case Shatranj:
				case Xiangqi:
					if (_pieceStyle == European)
					{
						painter.drawPixmap(i* w + w / 4, j* h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					else if (_pieceStyle == Mnemonic)
					{
						painter.drawPixmap(i* w + w / 8, j* h + h / 8, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					else if (_gameVariant != Xiangqi)
					{
						painter.drawPixmap(i * w + w / 12, j * h + h / 12, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					else
					{
						painter.drawPixmap(i * w + w / 4, j * h + h / 4, pixmap.size().width(), pixmap.size().height(), pixmap);
					}
					break;
				}
			}
		}
	}
}

bool VBoard::AskForPromotion()
{
	return QMessageBox(QMessageBox::Question, "Promotion", "Would you like to promote this piece?",
		QMessageBox::Yes | QMessageBox::No, this).exec() == QMessageBox::Yes;
}

void VBoard::FinishMove(int x, int y)
{
	if (_currentPlayer == White)
	{
		_lastWhiteMoveFrom = { _oldX, _oldY };
		_lastWhiteMoveTo = { x, y };
		_lastBlackMoveFrom = { -1, -1 };
		_lastBlackMoveTo = { -1, -1 };
		_whiteMoves.push_back(_board->GetFEN());
		if (!_board->HasPiece(King, Black) &&
			(!_board->HasPiece(MiddleTroop, Black) || !_board->HasPiece(Flag, White)) &&
			!_board->HasPiece(Prince, Black))
		{
			QMessageBox::information(this, "Game over", "White wins by eliminating Black King");
		}
	}
	else
	{
		_lastWhiteMoveFrom = { -1, -1 };
		_lastWhiteMoveTo = { -1, -1 };
		_lastBlackMoveFrom = { _oldX, _oldY };
		_lastBlackMoveTo = { x, y };
		_blackMoves.push_back(_board->GetFEN());
		if (!_board->HasPiece(King, White) &&
			(!_board->HasPiece(MiddleTroop, White) || !_board->HasPiece(Flag, White)) &&
			!_board->HasPiece(Prince, White))
		{
			QMessageBox::information(this, "Game over", "Black wins by eliminating White King");
		}
	}
	if (_comm && _comm->is_connected_remotely())
	{
		_comm->send_move(_board->GetFEN());
		_waitForOtherPlayer = true;
	}
	_currentPlayer = _currentPlayer == White ? Black : White;
	_statusBar->setStyleSheet("QStatusBar { color : black; }");
	_statusBar->showMessage(_currentPlayer == White ? _gameVariant == Xiangqi ? "Red move" : "White move" : "Black move");
	_currentPiece = nullptr;
	_oldX = -1;
	_oldY = -1;
	_moves.clear();
	_shoots.clear();
	_tcMoves.clear();
	_lionMovedOnce = false;
	_lionMovedTwice = false;
	_preparedToShoot = false;
	_pieceShotOnce = false;
	_lionFirstMove = { -1, -1 };
	_lionSecondMove = { -1, -1 };
	_firstShoot = { -1, -1 };
	this->repaint();
}

void VBoard::CancelLionMove()
{
	_lionMovedOnce = false;
	_lionMovedTwice = false;
	_lionFirstMove = { -1, -1 };
	_lionSecondMove = { -1, -1 };
	_tcMoves.clear();
}

void VBoard::mousePressEvent(QMouseEvent* event)
{
	if (event->button() != Qt::MouseButton::LeftButton) return;
	const int w = this->size().width() / _board->GetWidth();
	const int h = this->size().height() / _board->GetHeight();
    const int x = static_cast<int>(event->x()) / w;
    const int y = static_cast<int>(event->y()) / h;
	Piece* p = _board->GetData(x, y);
	if (_editorMode)
	{
		delete p;
		if (_chosenPiece == None)
		{
			_board->SetData(x, y, nullptr);
		}
		else
		{
			Piece* newPiece = _board->CreatePiece(_chosenPiece, _chosenColour);
			if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), _chosenPiece) != std::end(_promotedPieces))
			{
				newPiece->Promote();
			}
			_board->SetData(x, y, newPiece);
		}
		repaint();
		return;
	}
	if (_comm != nullptr && _comm->is_connected_remotely() && _waitForOtherPlayer) return;
	if (_blackEngine != nullptr && _blackEngine->IsActive() && _currentPlayer == Black ||
		_whiteEngine != nullptr && _whiteEngine->IsActive() && _currentPlayer == White) return;
	const std::shared_ptr<Engine> engine = _currentPlayer == White ? _blackEngine : _whiteEngine;
	const bool isLionPiece = _currentPiece != nullptr && std::find(std::begin(lionPieces), std::end(lionPieces), _currentPiece->GetType()) != std::end(lionPieces);
	const bool isShootingPiece = _gameVariant == KoShogi && _currentPiece != nullptr &&
		std::find(std::begin(ShootingPieces), std::end(ShootingPieces), _currentPiece->GetType()) != std::end(ShootingPieces);
	// Castling check
	if (_gameVariant == Chess && _currentPiece != nullptr && _currentPiece->GetType() == King && !dynamic_cast<ChessPiece*>(_currentPiece)->HasMoved() &&
		p != nullptr && p->GetColour() == _currentPlayer && p->GetType() == Rook && !dynamic_cast<ChessPiece*>(p)->HasMoved() && _board->IsMovePossible(x, y))
	{
		_board->SetData(x, y, _currentPiece);
		_board->SetData(4, y, p);
		if (engine != nullptr && engine->IsActive())
		{
			engine->Move(_oldX, _board->GetHeight() - _oldY, x == 7 ? 6 : 2, _board->GetHeight() - y, ' ');
		}
		dynamic_cast<ChessBoard*>(_board)->WriteCastling(x == 7 ? "O-O" : "O-O-O");
		FinishMove(x, y);
	}
	// Null move
	else if ((_gameVariant == ChuShogi || _gameVariant == DaiShogi || _gameVariant == TenjikuShogi ||
		_gameVariant == DaiDaiShogi || _gameVariant == MakaDaiDaiShogi || _gameVariant == KoShogi) &&
		_currentPiece != nullptr && p != nullptr && p->GetColour() == _currentPlayer &&
		x == _oldX && y == _oldY && !_lionMovedOnce && _currentPiece->GetType() != Thunderclap &&
		(isLionPiece || _currentPiece->GetType() == ViceGeneral || _currentPiece->GetType() == FireDemon || _currentPiece->GetType() == HeavenlyTetrarch))
	{
		if (_board->IsMovePossible(x, y) && !CheckRepetition(_oldX, _oldY, x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y, ' ');
			}
			FinishMove(x, y);
		}
	}
	// Lion move
	else if (_currentPiece != nullptr && (p == nullptr || p->GetColour() != _currentPlayer) && !CheckRepetition(_oldX, _oldY, x, y))
	{
		if (isLionPiece && !_lionMovedOnce && EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y))
		{
			if (_tcMoves.empty() && (abs(_oldX - x) > 1 || abs(_oldY - y) > 1) && _currentPiece->GetType() == Thunderclap)
			{
			}
			else if (!_tcMoves.empty() && (abs(_tcMoves[_tcMoves.size() - 1].first - x) > 1 ||
				abs(_tcMoves[_tcMoves.size() - 1].second - y) > 1) && _currentPiece->GetType() == Thunderclap)
			{
			}
            else if (std::find(std::begin(_tcMoves), std::end(_tcMoves), std::pair<int, int>(x, y)) != std::end(_tcMoves))
			{
			}
			else if (_currentPiece->GetType() == Thunderclap && PossibleMove(x, y))
			{
				if (_tcMoves.size() < 4)
				{
					_tcMoves.emplace_back(x, y);
					for (int index = _moves.size() - 1; index >= 0; index--)
					{
						if (abs(_tcMoves[_tcMoves.size() - 1].first - _moves[index].first) > 5 - _tcMoves.size() ||
							abs(_tcMoves[_tcMoves.size() - 1].second - _moves[index].second) > 5 - _tcMoves.size())
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					this->repaint();
				}
				else
				{
					_tcMoves.emplace_back(x, y);
					_tcMoves.insert(_tcMoves.begin(), EngineOutputHandler::GetPieceLocation(_board, Thunderclap, _currentPlayer));
					for (int index = 0; index < _tcMoves.size() - 1; index++)
					{
						if (_board->Move(_tcMoves[index].first, _tcMoves[index].second, _tcMoves[index + 1].first, _tcMoves[index + 1].second))
						{
							if (engine != nullptr && engine->IsActive())
							{
								engine->Move(_tcMoves[index].first, _board->GetHeight() - _tcMoves[index].second, 
									_tcMoves[index + 1].first, _board->GetHeight() - _tcMoves[index + 1].second);
							}
						}
					}
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) == 0 && abs(_oldY - y) == 2 || abs(_oldX - x) == 2 && abs(_oldY - y) == 0 ||
				abs(_oldX - x) == 2 && abs(_oldY - y) == 2) && _currentPiece->GetType() == RisingDragon)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) == 0 && abs(_oldY - y) == 2 || abs(_oldX - x) == 2 && abs(_oldY - y) == 0) &&
				_currentPiece->GetType() == WingedTiger)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) == 1 && abs(_oldY - y) == 1) && _currentPiece->GetType() == FlyingHawk)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					FinishMove(x, y);
				}
			}
			else if (_gameVariant == KoShogi && (abs(_oldX - x) == 2 || abs(_oldY - y) == 2) && _currentPiece->GetType() == Lion)
			{
			}
			else if (_gameVariant == KoShogi && (abs(_oldX - x) == 2 && abs(_oldY - y) == 1 || abs(_oldX - x) == 1 && abs(_oldY - y) == 2) &&
				_currentPiece->GetType() == RisingDragon)
			{
			}
			else if (_gameVariant == KoShogi && (abs(_oldX - x) == 2 && abs(_oldY - y) == 2) && _currentPiece->GetType() == WingedTiger)
			{
			}
			else if (abs(_oldX - x) + abs(_oldY - y) > 1 && _currentPiece->GetType() == FlyingHawk)
			{
			}
			else if (PossibleMove(x, y) && _currentPiece->GetType() == RoamingAssault)
			{
				if (x < _oldX)
				{
					for (int index = _oldX - 1; index >= x; index--)
					{
						_board->Move(index + 1, _oldY, index, y);
					}
				}
				else if (x > _oldX)
				{
					for (int index = _oldX + 1; index <= x; index++)
					{
						_board->Move(index - 1, _oldY, index, y);
					}
				}
				else if (y < _oldY)
				{
					for (int index = _oldY - 1; index >= y; index--)
					{
						_board->Move(_oldX, index + 1, x, index);
					}
				}
				else if (y > _oldY)
				{
					for (int index = _oldY + 1; index <= y; index++)
					{
						_board->Move(_oldX, index - 1, x, index);
					}
				}
				FinishMove(x, y);
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) == 2 || abs(_oldY - y) == 2) &&
				(_currentPiece->GetType() == Lion || _currentPiece->GetType() == LionHawk ||
					_currentPiece->GetType() == BuddhistSpirit || _currentPiece->GetType() == FreeEagle))
			{
				// Lion capture rule #1
				if (_gameVariant == ChuShogi && _board->GetData(x, y) != nullptr &&
					_currentPiece->GetType() == Lion && _board->GetData(x, y)->GetType() == Lion &&
					(abs(_oldX - x) == 2 || abs(_oldY - y) == 2))
				{
					const std::vector<std::pair<int, int>> lionDefenders = _board->GetDefenders(x, y);
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
					CheckPromotion(p, y);
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) == 2 || abs(_oldY - y) == 2) &&
				(_currentPiece->GetType() == LionDog || _currentPiece->GetType() == FuriousFiend ||
					_currentPiece->GetType() == GreatElephant || _currentPiece->GetType() == TeachingKing))
			{
				if (p != nullptr)
				{
					_lionFirstMove = { x, y };
					_lionMovedOnce = true;
					_lionMovedTwice = true;
					for (int index = _moves.size() - 1; index >= 0; index--)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					this->repaint();
				}
				else if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, y);
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) >= 3 || abs(_oldY - y) >= 3) &&
				(_currentPiece->GetType() == LionDog || _currentPiece->GetType() == FuriousFiend ||
					_currentPiece->GetType() == GreatElephant || _currentPiece->GetType() == TeachingKing))
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, y);
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) == 2 && _oldY - y == 2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == White) ||
				(abs(_oldX - x) == 2 && _oldY - y == -2 && _currentPiece->GetType() == Eagle && _currentPiece->GetColour() == Black) ||
				(_oldX == x && _oldY - y == 2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == White) ||
				(_oldX == x && _oldY - y == -2 && _currentPiece->GetType() == Unicorn && _currentPiece->GetColour() == Black))
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, y);
					FinishMove(x, y);
				}
			}
			else if ((abs(_oldX - x) == 4 || abs(_oldY - y) == 4) && (_currentPiece->GetType() == KnightCaptain ||
				_currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight))
			{
			}
			else if (!(abs(_oldX - x) == 2 && abs(_oldY - y) == 1 || abs(_oldX - x) == 1 && abs(_oldY - y) == 2) && 
				_currentPiece->GetType() == WingedHorse)
			{
			}
			else if (abs(_oldX - x) + abs(_oldY - y) > 2 && _currentPiece->GetType() == DoubleKylin)
			{
			}
			else if ((abs(_oldX - x) > 2 || abs(_oldY - y) > 2 || abs(_oldX - x) + abs(_oldY - y) > 1 && abs(_oldX - x) != abs(_oldY - y) ||
				abs(_oldX - x) == 1 && abs(_oldY - y) == 1) && _currentPiece->GetType() == DoublePhoenix)
			{
			}
			else if (_gameVariant == KoShogi && _board->GetData(x, y) == nullptr)
			{
				_lionFirstMove = { x, y };
				_lionMovedOnce = true;
				for (int index = _moves.size() - 1; index >= 0; index--)
				{
					if (_currentPiece->GetType() == Lion || _currentPiece->GetType() == RisingDragon)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == WingedTiger)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) != 1 ||
							abs(_moves[index].first - x) != 1 && abs(_moves[index].second - y) == 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == FlyingHawk)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) + abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight)
					{
						if (abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
						_shoots = dynamic_cast<KoShogiBoard*>(_board)->GetShoots(_currentPiece, x, y);
						if (!_shoots.empty())
						{
							_preparedToShoot = true;
						}
					}
					else if (_currentPiece->GetType() == KnightCaptain)
					{
						if (abs(_moves[index].first - x) >= 3 || abs(_moves[index].second - y) >= 3 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 0 ||
							abs(_moves[index].first - x) == 0 && abs(_moves[index].second - y) == 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == WingedHorse)
					{
						if (!(abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 2))
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == DoubleKylin)
					{
						if (abs(_moves[index].first - x) + abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == DoublePhoenix)
					{
						if (abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2 ||
							abs(_moves[index].first - x) + abs(_moves[index].second - y) > 1 &&
							abs(_moves[index].first - x) != abs(_moves[index].second - y) ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
				}
				this->repaint();
			}
			else if (PossibleMove(x, y) && _board->GetData(x, y) == nullptr)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, y);
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y))
			{
				_lionFirstMove = { x, y };
				_lionMovedOnce = true;
				for (int index = _moves.size() - 1; index >= 0; index--)
				{
					if (_currentPiece->GetType() == LionDog || _currentPiece->GetType() == FuriousFiend ||
						_currentPiece->GetType() == TeachingKing)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == GreatElephant)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2 ||
							_currentPlayer == White && abs(_moves[index].first - _oldX) != 0 && _moves[index].second < _oldY ||
							_currentPlayer == Black && abs(_moves[index].first - _oldX) != 0 && _moves[index].second > _oldY)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == Lion || _currentPiece->GetType() == LionHawk ||
						_currentPiece->GetType() == BuddhistSpirit || _currentPiece->GetType() == RisingDragon)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == FreeEagle || _currentPiece->GetType() == Eagle || _currentPiece->GetType() == WingedTiger)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) != 1 ||
							abs(_moves[index].first - x) != 1 && abs(_moves[index].second - y) == 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == Unicorn)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1 ||
							abs(_moves[index].first - x) != 0)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == FlyingHawk)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) + abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight)
					{
						if (abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
						_shoots = dynamic_cast<KoShogiBoard*>(_board)->GetShoots(_currentPiece, x, y);
						if (!_shoots.empty())
						{
							_preparedToShoot = true;
						}
						repaint();
					}
					else if (_currentPiece->GetType() == KnightCaptain)
					{
						if (abs(_moves[index].first - x) >= 3 || abs(_moves[index].second - y) >= 3 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 0 ||
							abs(_moves[index].first - x) == 0 && abs(_moves[index].second - y) == 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == WingedHorse)
					{
						if (!(abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 2))
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == DoubleKylin)
					{
						if (abs(_moves[index].first - x) + abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
					else if (_currentPiece->GetType() == DoublePhoenix)
					{
						if (abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2 ||
							abs(_moves[index].first - x) + abs(_moves[index].second - y) > 1 &&
							abs(_moves[index].first - x) != abs(_moves[index].second - y) ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
				}
				this->repaint();
			}
		}
		else if (isLionPiece && _lionMovedOnce)
		{
			if (_currentPiece->GetType() == Lion || _currentPiece->GetType() == LionHawk ||
				_currentPiece->GetType() == BuddhistSpirit || _currentPiece->GetType() == FreeEagle ||
				_currentPiece->GetType() == Unicorn || _currentPiece->GetType() == Eagle ||
				_currentPiece->GetType() == WingedTiger || _currentPiece->GetType() == FlyingHawk ||
				_currentPiece->GetType() == RisingDragon)
			{
				if (PossibleMove(x, y))
				{
					if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
					{
						if (engine != nullptr && engine->IsActive())
						{
							std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY,
								_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
						}
						CheckPromotion(p, y);
						FinishMove(x, y);
					}
				}
			}
			else if (_currentPiece->GetType() == LionDog || _currentPiece->GetType() == FuriousFiend ||
				_currentPiece->GetType() == GreatElephant || _currentPiece->GetType() == TeachingKing)
			{
				if (_lionMovedTwice && PossibleMove(x, y))
				{
					if (_lionSecondMove.first != -1)
					{
						if (dynamic_cast<MakaDaiDaiShogiBoard*>(_board)->TripleMove(_oldX, _oldY,
							_lionFirstMove.first, _lionFirstMove.second,
							_lionSecondMove.first, _lionSecondMove.second, x, y))
						{
							if (engine != nullptr && engine->IsActive())
							{
								std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY,
									_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second,
									_lionSecondMove.first, _board->GetHeight() - _lionSecondMove.second,
									x, _board->GetHeight() - y);
							}
							CheckPromotion(p, y);
							FinishMove(x, y);
						}
					}
					else
					{
						if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
						{
							if (engine != nullptr && engine->IsActive())
							{
								std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY,
									_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
							}
							CheckPromotion(p, y);
							FinishMove(x, y);
						}
					}
				}
				else if (abs(_lionFirstMove.first - x) == 2 || abs(_lionFirstMove.second - y) == 2)
				{
					if (PossibleMove(x, y))
					{
						if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
						{
							if (engine != nullptr && engine->IsActive())
							{
								std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY,
									_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
							}
							CheckPromotion(p, y);
							FinishMove(x, y);
						}
					}
				}
				else
				{
					if (PossibleMove(x, y))
					{
						_lionSecondMove = { x, y };
						_lionMovedTwice = true;
						for (int index = _moves.size() - 1; index >= 0; index--)
						{
							if (!EngineOutputHandler::IsLionMove(_currentPiece, _lionSecondMove.first, _lionSecondMove.second, x, y) ||
								abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1)
							{
								_moves.erase(_moves.begin() + index);
							}
						}
						this->repaint();
					}
				}
			}
			else if (_preparedToShoot && !_pieceShotOnce && PossibleShoot(x, y) &&
				(_currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight))
			{
				_firstShoot = { x, y };
				_preparedToShoot = false;
				_pieceShotOnce = true;
				_shoots.clear();
				repaint();
			}
			else if (PossibleMove(x, y) &&
				(_currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight))
			{
				KoShogiBoard* ksBoard = dynamic_cast<KoShogiBoard*>(_board);
				_lionSecondMove = { x, y };
				_shoots = ksBoard->GetShoots(_currentPiece, x, y);
				if (!_shoots.empty())
				{
					_preparedToShoot = true;
					_moves.clear();
					repaint();
				}
				else
				{
					ksBoard->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, _lionSecondMove.first, _lionSecondMove.second);
					if (_pieceShotOnce)
					{
						ksBoard->Shoot(_firstShoot.first, _firstShoot.second);
					}
					FinishMove(x, y);
				}
			}
			else if (_moves.empty() && PossibleShoot(x, y) &&
				(_currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight))
			{
				KoShogiBoard *ksBoard = dynamic_cast<KoShogiBoard*>(_board);
				ksBoard->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, _lionSecondMove.first, _lionSecondMove.second);
				ksBoard->Shoot(_firstShoot.first, _firstShoot.second);
				ksBoard->Shoot(x, y);
				FinishMove(x, y);
			}
			else if (x == _lionFirstMove.first && y == _lionFirstMove.second)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (_currentPiece->GetType() == KnightCaptain || _currentPiece->GetType() == WingedHorse ||
				_currentPiece->GetType() == DoubleKylin || _currentPiece->GetType() == DoublePhoenix))
			{
				if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY,
							_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, y);
					FinishMove(x, y);
				}
			}
		}
		else if (isShootingPiece && !_preparedToShoot && PossibleMove(x, y))
		{
			_shoots = dynamic_cast<KoShogiBoard*>(_board)->GetShoots(_currentPiece, x, y);
			if (!_shoots.empty())
			{
				_lionFirstMove = { x, y };
				_preparedToShoot = true;
				_moves.clear();
				_board->RemoveMoves();
				repaint();
			}
			else
			{
				FinishMove(x, y);
			}
		}
		else if (isShootingPiece && _preparedToShoot && PossibleShoot(x, y))
		{
			KoShogiBoard* ksBoard = dynamic_cast<KoShogiBoard*>(_board);
			if (_currentPiece->GetBaseType() == FrankishCannon && !_pieceShotOnce)
			{
				if (_shoots.size() > 1)
				{
					_pieceShotOnce = true;
					_firstShoot = { x, y };
					repaint();
				}
				else
				{
					ksBoard->Move(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, false);
					ksBoard->Shoot(x, y);
					FinishMove(x, y);
				}
			}
			else
			{
				ksBoard->Move(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, false);
				if (_currentPiece->GetBaseType() == FrankishCannon && _pieceShotOnce)
				{
					ksBoard->Shoot(_firstShoot.first, _firstShoot.second);
				}
				ksBoard->Shoot(x, y);
				FinishMove(x, y);
			}
		}
		else if (x == _lionFirstMove.first && y == _lionFirstMove.second && _preparedToShoot)
		{
			_board->Move(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, false);
			FinishMove(x, y);
		}
		else if (_board->Move(_oldX, _oldY, x, y))
		{
			const char promotion = CheckPromotion(p, y);
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
				EngineOutputHandler::AddMove(_board, _gameVariant, promotion == '+' ? _board->GetData(x, y)->GetBaseType() : _board->GetData(x, y)->GetType(), _oldX, _oldY, x, y, promotion, p != nullptr ? 'x' : ' ');
			}
			FinishMove(x, y);
		}
	}
	else if (x == _oldX && y == _oldY && _lionMovedTwice && abs(_lionSecondMove.first - x) < 2 && abs(_lionSecondMove.second - y) < 2)
	{
		if (dynamic_cast<MakaDaiDaiShogiBoard*>(_board)->TripleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, _lionSecondMove.first, _lionSecondMove.second, x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY,
					_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second,
					_lionSecondMove.first, _board->GetHeight() - _lionSecondMove.second,
					x, _board->GetHeight() - y);
			}
			FinishMove(x, y);
		}
	}
	else if (x == _oldX && y == _oldY && _lionMovedOnce && abs(_lionFirstMove.first - x) <= 2 && abs(_lionFirstMove.second - y) <= 2 &&
		(_currentPiece->GetType() == KnightCaptain || _currentPiece->GetType() == ExtensiveFog || _currentPiece->GetType() == HolyLight ||
		_currentPiece->GetType() == DoubleKylin || _currentPiece->GetType() == DoublePhoenix || _currentPiece->GetType() == WingedHorse))
	{
		if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
			}
			EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->GetType(), _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
			FinishMove(x, y);
		}
	}
	else if (x == _oldX && y == _oldY && _lionMovedOnce && abs(_lionFirstMove.first - x) < 2 && abs(_lionFirstMove.second - y) < 2)
	{
		if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				std::dynamic_pointer_cast<WbEngine>(engine)->Move(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
			}
			EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->GetType(), _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
			FinishMove(x, y);
		}
	}
	else if (p != nullptr && p->GetColour() == _currentPlayer)
	{
		_currentPiece = _board->GetData(x, y);
		_oldX = x;
		_oldY = y;
		_board->GetMoves(p, x, y);
		_preparedToShoot = false;
		_shoots.clear();
		_moves = _board->Moves();
		CancelLionMove();
		if (std::find(std::begin(shogiVariants), std::end(shogiVariants), _gameVariant) == std::end(shogiVariants))
		{
			for (int index = 0; index < 4; index++)
			{
				std::for_each(_moves.begin(), _moves.end(), [=](std::pair<int, int> t)
				{
					EngineOutputHandler::CalculateCheck(_board, _currentPlayer, _moves, x, y, t.first, t.second);
				});
			}
		}
		this->repaint();
	}
}

char VBoard::CheckPromotion(const Piece *p, int y)
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
	else if (_gameVariant == DaiDaiShogi)
	{
		if (!_currentPiece->IsPromoted() && p != nullptr &&
			std::find(std::begin(UnpromotablePieces),
				std::end(UnpromotablePieces),
				_currentPiece->GetType()) == std::end(UnpromotablePieces))
		{
			promotion = '+';
			_currentPiece->Promote();
		}
	}
	else if (_gameVariant == MakaDaiDaiShogi)
	{
		if (_currentPiece->GetType() != Queen && _currentPiece->GetType() != DragonKing &&
			_currentPiece->GetType() != DragonHorse && !_currentPiece->IsPromoted() && p != nullptr)
		{
			if (p->GetBaseType() == Deva)
			{
				promotion = '+';
				_currentPiece->Promote(TeachingKing);
			}
			else if (p->GetBaseType() == DarkSpirit)
			{
				promotion = '+';
				_currentPiece->Promote(BuddhistSpirit);
			}
			else if (p->IsPromoted() || AskForPromotion())
			{
				promotion = '+';
				_currentPiece->Promote();
			}
			else
			{
				promotion = '=';
			}
		}
	}
	else if (_gameVariant == KoShogi)
	{
		// If the Taoist priest is captured, the drum and banner can no longer promote.
		if (dynamic_cast<KoShogiBoard*>(_board)->IsTaoistPriestCaptured() && (_currentPiece->GetType() == Flag || _currentPiece->GetType() == Drum))
		{
		}
		else if (_currentPiece->GetType() != King && _currentPiece->GetType() != Lion &&
			_currentPiece->GetType() != Bishop && !_currentPiece->IsPromoted() && p != nullptr)
		{
			if (p->GetType() == King || p->GetType() == Prince || p->GetType() == MiddleTroop || p->GetType() == Flag || p->GetType() == Drum)
			{
				promotion = '+';
				_currentPiece->Promote();
			}
			else if (std::find(std::begin(StepMovers), std::end(StepMovers), _currentPiece->GetType()) != std::end(StepMovers))
			{
				if (p->GetType() == Lion || p->GetType() == RisingDragon || p->GetType() == RoamingAssault || p->GetType() == Thunderclap)
				{
					promotion = '+';
					_currentPiece->Promote();
				}
			}
			else if (_currentPiece->GetType() == Knight)
			{
				if (p->GetType() == FrankishCannon)
				{
					promotion = '+';
					_currentPiece->Promote();
				}
			}
			else if (p->IsPromoted() || AskForPromotion())
			{
				promotion = '+';
				_currentPiece->Promote();
			}
			else
			{
				promotion = '=';
			}
			// When the clerk promotes to master at arms, all the allied advance and rear guards promote as well, while any enemy poison flame dies.
			if (promotion == '+' && _currentPiece->GetBaseType() == Kylin && _currentPiece->GetType() == DoubleKylin)
			{
				const auto aguards = EngineOutputHandler::GetPieceLocations(_board, AdvanceGuard, _currentPlayer);
				for (const auto& aguard : aguards)
				{
					_board->GetData(aguard.first, aguard.second)->Promote();
				}
				const auto rguards = EngineOutputHandler::GetPieceLocations(_board, RearGuard, _currentPlayer);
				for (const auto& rguard : rguards)
				{
					_board->GetData(rguard.first, rguard.second)->Promote();
				}
				const auto pfLocations = EngineOutputHandler::GetPieceLocations(_board, PoisonFlame, _currentPlayer == White ? Black : White);
				for (const auto& pfLocation : pfLocations)
				{
					delete _board->GetData(pfLocation.first, pfLocation.second);
					_board->SetData(pfLocation.first, pfLocation.second, nullptr);
				}
			}
		}
	}
	else if (std::find(std::begin(shogiVariants), std::end(shogiVariants), _gameVariant) != std::end(shogiVariants))
	{
		const PieceType pt = _currentPiece->GetType();
		const bool pcond1 = EngineOutputHandler::CanBePromoted(_currentPiece, _gameVariant, _oldY, y);
		const bool pcond2 = (_gameVariant == ChuShogi || _gameVariant == DaiShogi || _gameVariant == TenjikuShogi) &&
			EngineOutputHandler::IsInsidePromotionZone(_gameVariant, _currentPlayer, _oldY) &&
			EngineOutputHandler::IsInsidePromotionZone(_gameVariant, _currentPlayer, y) && p != nullptr;
		const bool pcond3 = _gameVariant == ChuShogi && pt == Pawn &&
			((y == _board->GetHeight() - 1 && _currentPiece->GetColour() == Black) || (y == 0 && _currentPiece->GetColour() == White));
		if (pcond1 || pcond2 || pcond3)
		{
			if (((pt == Pawn && _gameVariant != ChuShogi) || pt == Knight || pt == Lance) &&
				((y == _board->GetHeight() - 1 && _currentPiece->GetColour() == Black) || (y == 0 && _currentPiece->GetColour() == White)))
			{
				_currentPiece->Promote();
			}
			else if (!_currentPiece->IsPromoted())
			{
				if (AskForPromotion())
				{
					_currentPiece->Promote();
					promotion = '+';
				}
				else
				{
					promotion = '=';
				}
			}
		}
	}
	return promotion;
}

bool VBoard::event(QEvent* event)
{
	if (event->type() == QEvent::HoverMove && std::find(std::begin(shogiVariants), std::end(shogiVariants), _gameVariant) != std::end(shogiVariants))
	{
		const QHoverEvent* hoverEvent = dynamic_cast<QHoverEvent*>(event);
		const int w = this->size().width() / _board->GetWidth();
		const int h = this->size().height() / _board->GetHeight();
        const int x = static_cast<int>(hoverEvent->pos().x()) / w;
        const int y = static_cast<int>(hoverEvent->pos().y()) / h;
		if (x < _board->GetWidth() && y < _board->GetHeight() && (x != _px || y != _py))
		{
			_px = x;
			_py = y;
			const Piece* p = _board->GetData(x, y);
			if (p != nullptr)
			{
				_attackers = _board->GetAttackers(x, y);
				_defenders = _board->GetDefenders(x, y);
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
	_lastWhiteMoveFrom = { -1, -1 };
	_lastWhiteMoveTo = { -1, -1 };
	_lastBlackMoveFrom = { -1, -1 };
	_lastBlackMoveTo = { -1, -1 };
	_whiteMoves.clear();
	_blackMoves.clear();
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
	_shoots.clear();
	_attackers.clear();
	_defenders.clear();
	_gameVariant = gameVariant;
	int s = 66;
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
		s = 60;
		_board = new DaiShogiBoard();
		break;
	case TenjikuShogi:
		s = 56;
		_board = new TenjikuShogiBoard();
		break;
	case DaiDaiShogi:
		s = 52;
		_board = new DaiDaiShogiBoard();
		break;
	case MakaDaiDaiShogi:
		s = 48;
		_board = new MakaDaiDaiShogiBoard();
		break;
	case KoShogi:
		s = 48;
		_board = new KoShogiBoard();
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
	_lastWhiteMoveFrom = { -1, -1 };
	_lastWhiteMoveTo = { -1, -1 };
	_lastBlackMoveFrom = { -1, -1 };
	_lastBlackMoveTo = { -1, -1 };
	_moves.clear();
	_shoots.clear();
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

bool VBoard::PossibleShoot(int x, int y) const
{
	return std::any_of(_shoots.begin(), _shoots.end(), [x, y](const std::pair<int, int> t) {return t.first == x && t.second == y;});
}

void VBoard::SetMainWindow(QMainWindow *window)
{
	_window = window;
}

void VBoard::SetWhiteEngine(std::shared_ptr<Engine> engine)
{
	_whiteEngine = std::move(engine);
}

void VBoard::SetBlackEngine(std::shared_ptr<Engine> engine)
{
	_blackEngine = std::move(engine);
}

void VBoard::SetCommunications(Communications* _communications)
{
	_waitForOtherPlayer = _comm != nullptr && _comm->is_listening();
	_comm = _communications;
}

void VBoard::SetWaitForOtherPlayer(bool waitForOtherPlayer)
{
	_waitForOtherPlayer = waitForOtherPlayer;
}

QStatusBar* VBoard::GetStatusBar() const
{
	return _statusBar;
}

void VBoard::SetStatusBar(QStatusBar* statusBar)
{
	_statusBar = statusBar;
}

bool VBoard::GetEditorMode() const
{
	return _editorMode;
}

void VBoard::SetEditorMode(bool editorMode)
{
	if (editorMode)
	{
		if (_gameVariant == Chess)
		{
			dynamic_cast<ChessBoard*>(_board)->SetCastling("-");
			dynamic_cast<ChessBoard*>(_board)->SetEnPassant("-");
		}
		delete _editorBoard;
		_editorBoard = _board->Clone();
	}
	else
	{
		if (*_board != _editorBoard->GetFEN())
		{
			QMessageBox mb(QMessageBox::Question, "Question", "Do you want to preserve the changes?",
				QMessageBox::Yes | QMessageBox::No);
			const int response = mb.exec();
			if (response == QMessageBox::Yes)
			{
				delete _editorBoard;
				_editorBoard = nullptr;
				if (_blackEngine != nullptr && _blackEngine->IsActive())
				{
					if (_blackEngine->GetType() == XBoard && !std::dynamic_pointer_cast<WbEngine>(_blackEngine)->GetOption("setboard"))
					{
						std::dynamic_pointer_cast<WbEngine>(_blackEngine)->Edit(_board);
					}
					else
					{
						_blackEngine->SetFEN(_board->GetFEN());
					}
				}
				if (_whiteEngine != nullptr && _whiteEngine->IsActive())
				{
					if (_whiteEngine->GetType() == XBoard && !std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->GetOption("setboard"))
					{
						std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->Edit(_board);
					}
					else
					{
						_whiteEngine->SetFEN(_board->GetFEN());
					}
				}
			}
			else
			{
				delete _board;
				_board = _editorBoard;
				repaint();
			}
		}
	}
	_editorMode = editorMode;
}

bool VBoard::GetHighlightMoves() const
{
	return _highlightMoves;
}

void VBoard::SetHighlightMoves(bool highlightMoves)
{
	_highlightMoves = highlightMoves;
}

bool VBoard::GetHighlightShoots() const
{
	return _highlightShoots;
}

void VBoard::SetHighlightShoots(bool highlightShoots)
{
	_highlightShoots = highlightShoots;
}

bool VBoard::GetHighlightAttackers() const
{
	return _highlightAttackers;
}

void VBoard::SetHighlightAttackers(bool highlightAttackers)
{
	_highlightAttackers = highlightAttackers;
}

bool VBoard::GetHighlightDefenders() const
{
	return _highlightDefenders;
}

void VBoard::SetHighlightDefenders(bool highlightDefenders)
{
	_highlightDefenders = highlightDefenders;
}

bool VBoard::GetHighlightLastMoves() const
{
	return _highlightLastMoves;
}

void VBoard::SetHighlightLastMoves(bool highlightLastMoves)
{
	_highlightLastMoves = highlightLastMoves;
}

bool VBoard::CheckRepetition(int oldX, int oldY, int newX, int newY)
{
	// Repetition rule
	Board *board = _board->Clone();
	board->Move(oldX, oldY, newX, newY);
	int repetitions = 0;
	if (_currentPlayer == White)
	{
		for (auto& _whiteMove : _whiteMoves)
		{
			if (*board == _whiteMove)
			{
				repetitions++;
			}
		}
	}
	else
	{
		for (auto& _blackMove : _blackMoves)
		{
			if (*board == _blackMove)
			{
				repetitions++;
			}
		}
	}
	delete board;
	if (repetitions >= 4)
	{
		QMessageBox::warning(this, "Warning", "Repetition rule violated.\nPlease make another move.");
		return true;
	}
	return false;
}

void VBoard::whiteEngineReadyReadStandardOutput()
{
	if (_whiteEngine == nullptr || !_whiteEngine->IsActive()) return;
	QProcess* p = dynamic_cast<QProcess*>(sender());
	const QByteArray buf = p->readAllStandardOutput();
	if (buf.contains("Illegal move"))
	{
		QMessageBox::critical(this, "Error", "Illegal move");
		if (_blackEngine != nullptr && _blackEngine->IsActive() && !_blackEngine->Moves().empty())
		{
			Logger::writeToLog("Illegal move " + _blackEngine->Moves()[_blackEngine->Moves().size() - 1], LogLevel::Warning);
		}
		if (_blackMoves.size() > 1)
		{
			_blackMoves.pop_back();
			EngineOutputHandler::SetFenToBoard(_board, QByteArray::fromStdString(_blackMoves[_blackMoves.size() - 1]), _gameVariant);
			this->repaint();
		}
		this->_statusBar->showMessage("Black move");
		_currentPlayer = Black;
		return;
	}
	EngineOutputHandler::ReadStandardOutput(buf, _whiteEngine, _board, _textEdit2, _gameVariant, _engineOutput, White);
	if (_blackEngine != nullptr && _blackEngine->IsActive())
	{
		const QByteArray moveArray = EngineOutputHandler::ExtractMove(buf, _whiteEngine->GetType(), _gameVariant);
		if (moveArray.isEmpty()) return;
		if (moveArray.size() < 8)
		{
			const Move m = EngineOutputHandler::ByteArrayToMove(moveArray, _blackEngine->GetType(), _gameVariant, _board->GetWidth(), _board->GetHeight());
			QByteArray convertedMoveArray = EngineOutputHandler::MoveToByteArray(m, _blackEngine->GetType(), _board->GetWidth(), _board->GetHeight());
			_blackEngine->Move(convertedMoveArray[0], convertedMoveArray[1], convertedMoveArray[2], convertedMoveArray[3], moveArray.size() > 4 ? moveArray[4] : ' ');
		}
		else
		{
			std::dynamic_pointer_cast<WbEngine>(_blackEngine)->Move(moveArray[0], moveArray[1], moveArray[2], moveArray[3], moveArray[6], moveArray[7]);
		}
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
	QProcess* process = dynamic_cast<QProcess*>(sender());
	const QByteArray buf = process->readAllStandardError();
	if (!buf.isEmpty())
	{
		Logger::writeToLog("Error while running process " + process->program(), LogLevel::Error);
		Logger::writeToLog(buf, LogLevel::Error);
		EngineOutputHandler::ReadStandardError(buf, this->_textEdit2);
	}
}

void VBoard::blackEngineReadyReadStandardOutput()
{
	if (_blackEngine == nullptr || !_blackEngine->IsActive()) return;
	QProcess *p = dynamic_cast<QProcess*>(sender());
	const QByteArray buf = p->readAllStandardOutput();
	if (buf.contains("Illegal move"))
	{
		QMessageBox::critical(this, "Error", "Illegal move");
		if (_whiteEngine != nullptr && _whiteEngine->IsActive() && !_whiteEngine->Moves().empty())
		{
			Logger::writeToLog("Illegal move " + _whiteEngine->Moves()[_whiteEngine->Moves().size() - 1], LogLevel::Warning);
		}
		if (_whiteMoves.size() > 1)
		{
			_whiteMoves.pop_back();
			EngineOutputHandler::SetFenToBoard(_board, QByteArray::fromStdString(_whiteMoves[_whiteMoves.size() - 1]), _gameVariant);
			this->repaint();
		}
		this->_statusBar->showMessage(_gameVariant == Xiangqi ? "Red move" : "White move");
		_currentPlayer = White;
		return;
	}
	EngineOutputHandler::ReadStandardOutput(buf, _blackEngine, _board, _textEdit, _gameVariant, _engineOutput, Black);
	if (_whiteEngine != nullptr && _whiteEngine->IsActive())
	{
		const QByteArray moveArray = EngineOutputHandler::ExtractMove(buf, _blackEngine->GetType(), _gameVariant);
		if (moveArray.isEmpty()) return;
		if (moveArray.size() < 8)
		{
			const Move m = EngineOutputHandler::ByteArrayToMove(moveArray, _whiteEngine->GetType(), _gameVariant, _board->GetWidth(), _board->GetHeight());
			QByteArray convertedMoveArray = EngineOutputHandler::MoveToByteArray(m, _whiteEngine->GetType(), _board->GetWidth(), _board->GetHeight());
			_whiteEngine->Move(convertedMoveArray[0], convertedMoveArray[1], convertedMoveArray[2], convertedMoveArray[3], moveArray.size() > 4 ? moveArray[4] : ' ');
		}
		else
		{
			std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->Move(moveArray[0], moveArray[1], moveArray[2], moveArray[3], moveArray[6], moveArray[7]);
		}
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
	QProcess* process = dynamic_cast<QProcess*>(sender());
	const QByteArray buf = process->readAllStandardError();
	if (!buf.isEmpty())
	{
		Logger::writeToLog("Error while running process " + process->program(), LogLevel::Error);
		Logger::writeToLog(buf, LogLevel::Error);
		EngineOutputHandler::ReadStandardError(buf, this->_textEdit);
	}
}

void VBoard::contextMenuEvent(QContextMenuEvent* event)
{
	const int w = this->size().width() / _board->GetWidth();
	const int h = this->size().height() / _board->GetHeight();
	const int x = event->x() / w;
	const int y = event->y() / h;

	if (_editorMode)
	{
		QMenu menu(this);

		// Add Black and White groups
		QMenu* blackMenu = menu.addMenu("Black");
		QMenu* whiteMenu = menu.addMenu("White");

		// Create Regular and Promoted submenus for Black
		QMenu* blackRegular = blackMenu->addMenu("Regular");
		QMenu* blackPromoted = nullptr;

		// Create Regular and Promoted submenus for White
		QMenu* whiteRegular = whiteMenu->addMenu("Regular");
		QMenu* whitePromoted = nullptr;

		blackRegular->addAction("None");
		whiteRegular->addAction("None");

		if (_gameVariant == CrazyWa || _gameVariant == WaShogi || _gameVariant == ChuShogi || _gameVariant == DaiShogi || _gameVariant == TenjikuShogi ||
			_gameVariant == DaiDaiShogi || _gameVariant == MakaDaiDaiShogi || _gameVariant == KoShogi)
		{
			menu.addAction("Promote");
			blackPromoted = blackMenu->addMenu("Promoted");
			whitePromoted = whiteMenu->addMenu("Promoted");
			blackPromoted->addAction("None");
			whitePromoted->addAction("None");
		}

		if (_gameVariant == Chess)
		{
			for (auto& ChessPiece : ChessPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ChessPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ChessPiece)));
			}
		}
		else if (_gameVariant == Shatranj)
		{
			for (auto& ShatranjPiece : ShatranjPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShatranjPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShatranjPiece)));
			}
		}
		else if (_gameVariant == Makruk)
		{
			for (auto& MakrukPiece : MakrukPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(MakrukPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(MakrukPiece)));
			}
		}
		else if (_gameVariant == Xiangqi)
		{
			for (auto& XiangqiPiece : XiangqiPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(XiangqiPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(XiangqiPiece)));
			}
		}
		else if (_gameVariant == Shogi)
		{
			for (auto& ShogiPiece : ShogiPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
			}
		}
		else if (_gameVariant == Shogi)
		{
			for (auto& ShogiPiece : ShogiPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
			}
		}
		else if (_gameVariant == ShoShogi)
		{
			for (auto& ShogiPiece : ShoShogiPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
			}
		}
		else if (_gameVariant == MiniShogi)
		{
			for (auto& ShogiPiece : MiniShogiPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
			}
		}
		else if (_gameVariant == JudkinShogi)
		{
			for (auto& ShogiPiece : JudkinsShogiPieces)
			{
				whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
				blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ShogiPiece)));
			}
		}
		else if (_gameVariant == WaShogi || _gameVariant == CrazyWa)
		{
			for (auto& WaShogiPiece : WaShogiPieces)
			{
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), WaShogiPiece) != std::end(_promotedPieces))
				{
					whitePromoted->addAction(QString::fromStdString(WaShogiPiece::PieceType2Description(WaShogiPiece)));
					blackPromoted->addAction(QString::fromStdString(WaShogiPiece::PieceType2Description(WaShogiPiece)));
				}
				else
				{
					whiteRegular->addAction(QString::fromStdString(WaShogiPiece::PieceType2Description(WaShogiPiece)));
					blackRegular->addAction(QString::fromStdString(WaShogiPiece::PieceType2Description(WaShogiPiece)));
				}
			}
		}
		else if (_gameVariant == ChuShogi)
		{
			for (auto& ChuShogiPiece : ChuShogiPieces)
			{
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), ChuShogiPiece) != std::end(_promotedPieces))
				{
					whitePromoted->addAction(QString::fromStdString(Piece::PieceType2Description(ChuShogiPiece)));
					blackPromoted->addAction(QString::fromStdString(Piece::PieceType2Description(ChuShogiPiece)));
				}
				else
				{
					whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ChuShogiPiece)));
					blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(ChuShogiPiece)));
				}
			}
		}
		else if (_gameVariant == DaiShogi)
		{
			for (auto& DaiShogiPiece : DaiShogiPieces)
			{
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), DaiShogiPiece) != std::end(_promotedPieces))
				{
					whitePromoted->addAction(QString::fromStdString(Piece::PieceType2Description(DaiShogiPiece)));
					blackPromoted->addAction(QString::fromStdString(Piece::PieceType2Description(DaiShogiPiece)));
				}
				else
				{
					whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(DaiShogiPiece)));
					blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(DaiShogiPiece)));
				}
			}
		}
		else if (_gameVariant == TenjikuShogi)
		{
			for (auto& TenjikuShogiPiece : TenjikuShogiPieces)
			{
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), TenjikuShogiPiece) != std::end(_promotedPieces))
				{
					whitePromoted->addAction(QString::fromStdString(Piece::PieceType2Description(TenjikuShogiPiece)));
					blackPromoted->addAction(QString::fromStdString(Piece::PieceType2Description(TenjikuShogiPiece)));
				}
				else
				{
					whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(TenjikuShogiPiece)));
					blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(TenjikuShogiPiece)));
				}
			}
		}
		else if (_gameVariant == DaiDaiShogi)
		{
			for (auto& DaiDaiShogiPiece : DaiDaiShogiPieces)
			{
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), DaiDaiShogiPiece) != std::end(_promotedPieces))
				{
					whitePromoted->addAction(QString::fromStdString(Piece::PieceType2Description(DaiDaiShogiPiece)));
					blackPromoted->addAction(QString::fromStdString(Piece::PieceType2Description(DaiDaiShogiPiece)));
				}
				else
				{
					whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(DaiDaiShogiPiece)));
					blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(DaiDaiShogiPiece)));
				}
			}
		}
		else if (_gameVariant == MakaDaiDaiShogi)
		{
			for (auto& MakaDaiDaiShogiPiece : MakaDaiDaiShogiPieces)
			{
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), MakaDaiDaiShogiPiece) != std::end(_promotedPieces))
				{
					whitePromoted->addAction(QString::fromStdString(Piece::PieceType2Description(MakaDaiDaiShogiPiece)));
					blackPromoted->addAction(QString::fromStdString(Piece::PieceType2Description(MakaDaiDaiShogiPiece)));
				}
				else
				{
					whiteRegular->addAction(QString::fromStdString(Piece::PieceType2Description(MakaDaiDaiShogiPiece)));
					blackRegular->addAction(QString::fromStdString(Piece::PieceType2Description(MakaDaiDaiShogiPiece)));
				}
			}
			}
		else if (_gameVariant == KoShogi)
		{
			for (auto& KoShogiPiece : KoShogiPieces)
			{
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), KoShogiPiece) != std::end(_promotedPieces))
				{
					whitePromoted->addAction(QString::fromStdString(KoShogiPiece::PieceType2Description(KoShogiPiece)));
					blackPromoted->addAction(QString::fromStdString(KoShogiPiece::PieceType2Description(KoShogiPiece)));
				}
				else
				{
					whiteRegular->addAction(QString::fromStdString(KoShogiPiece::PieceType2Description(KoShogiPiece)));
					blackRegular->addAction(QString::fromStdString(KoShogiPiece::PieceType2Description(KoShogiPiece)));
				}
			}
		}

		const QAction* selectedAction = menu.exec(event->globalPos());

		if (selectedAction != nullptr)
		{
			if (selectedAction->text() == "Promote")
			{
				if (_board->GetData(x, y) != nullptr && !_board->GetData(x, y)->IsPromoted())
				{
					_board->GetData(x, y)->Promote();
				}
				return;
			}
			_chosenColour = qobject_cast<QMenu*>(selectedAction->parent()->parent())->title() == "White" ? White : Black;
			if (_gameVariant == CrazyWa || _gameVariant == WaShogi)
			{
				_chosenPiece = WaShogiPiece::Description2PieceType(selectedAction->text().toStdString());
			}
			else if (_gameVariant == KoShogi)
			{
				_chosenPiece = KoShogiPiece::Description2PieceType(selectedAction->text().toStdString());
			}
			else
			{
				_chosenPiece = Piece::Description2PieceType(selectedAction->text().toStdString());
			}

			const Piece* p = _board->GetData(x, y);
			delete p;
			if (_chosenPiece == None)
			{
				_board->SetData(x, y, nullptr);
			}
			else
			{
				Piece* newPiece = _board->CreatePiece(_chosenPiece, _chosenColour);
				if (std::find(std::begin(_promotedPieces), std::end(_promotedPieces), _chosenPiece) != std::end(_promotedPieces))
				{
					newPiece->Promote();
				}
				_board->SetData(x, y, newPiece);
			}
		}

		repaint();
		return;
	}

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
			str = p.Description() + " (" + p.KanjiStringCode() + ")";
		}
		else
		{
			ShogiPiece p(cp, _currentPlayer);
			str = p.Description() + " (" + p.KanjiStringCode() + ")";
		}
		menu.addAction(QString::fromStdString(str));
	}

	// Execute the menu at the cursor position
	const QAction* selectedAction = menu.exec(event->globalPos());

	// Handle the selected action
	if (selectedAction != nullptr)
	{
		QStringList parts = selectedAction->text().split(' ', Qt::SkipEmptyParts);
		const std::string longStringCode = _gameVariant == CrazyWa ? (parts[0] + " " + parts[1]).toStdString() : parts[0].toStdString();
		const PieceType newPiece = _gameVariant == CrazyWa ? 
			WaShogiPiece::Description2PieceType(longStringCode) : ShogiPiece::Description2PieceType(longStringCode);

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
			const Piece* kp = _currentPlayer == White ? _board->GetData(x, y - 1) : _board->GetData(x, y + 1);
			if (kp != nullptr && kp->GetType() == King && kp->GetColour() != _currentPlayer)
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot check king by the pawn drop",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
			for (int index = 0; index < _board->GetHeight(); index++)
			{
				const Piece* p = _board->GetData(x, index);
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
		const std::shared_ptr<Engine> engine = _currentPlayer == White ? _blackEngine : _whiteEngine;
		if (engine != nullptr && engine->IsActive())
		{
			if (engine->GetType() == USI)
				engine->Move(sc, '*', _board->GetWidth() - x, y, ' ');
			else
				engine->Move(sc, '@', x, _board->GetHeight() - y, ' ');
		}
		EngineOutputHandler::AddMove(_board, _gameVariant, newPiece, sc, '*', x, y, ' ', ' ');
		dynamic_cast<ShogiVariantBoard*>(_board)->RemoveCapturedPiece(newPiece, _currentPlayer);
		FinishMove(x, y);
	}
}
