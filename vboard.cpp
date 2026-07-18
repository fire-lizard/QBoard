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
	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
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
			if (std::ranges::find(_tcMoves, std::pair(i, j)) != std::end(_tcMoves) ||
				_lionFirstMove.first == i && _lionFirstMove.second == j || _lionSecondMove.first == i && _lionSecondMove.second == j ||
				_firstShoot.first == i && _firstShoot.second == j)
			{
				painter.setBrush(QColorConstants::Svg::yellow);
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(rect);
                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
				painter.setBrush(Qt::NoBrush);
			}
            else if (_gameVariant == OmegaChess &&
                    (j == 0 && i >= 1 && i <= _board->GetWidth() - 2 ||
                     j == _board->GetHeight() - 1 && i >= 1 && i <= _board->GetWidth() - 2 ||
                     i == 0 && j >= 1 && j <= _board->GetHeight() - 2 ||
                     i == _board->GetWidth() - 1 && j >= 1 && j <= _board->GetHeight() - 2))
            {
                painter.setBrush(Qt::black);
                painter.drawRect(rect);
                painter.setBrush(Qt::NoBrush);
            }
            else if (PossibleMove(i, j) && _highlightMoves)
			{
                if (_currentPiece != std::nullopt && std::ranges::find(lionPieces, _currentPiece->Type) != std::end(lionPieces))
				{
					// Lion move highlighting
					if (_gameVariant == KoShogi && !_lionMovedOnce && EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, i, j))
					{
						const bool lcond1 = (abs(_oldX - i) == 2 || abs(_oldY - j) == 2) &&
                            (_currentPiece->Type == Lion || _currentPiece->Type == WingedTiger ||
                                _currentPiece->Type == FlyingHawk || _currentPiece->Type == RisingDragon);
                        const bool lcond2 = abs(_oldX - i) == 1 && abs(_oldY - j) == 1 && _currentPiece->Type == FlyingHawk;
						const bool lcond3 = (abs(_oldX - i) == 4 || abs(_oldY - j) == 4) &&
                            (_currentPiece->Type == KnightCaptain || _currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight);
                        const bool lcond4 = abs(_oldX - i) + abs(_oldY - j) > 2 && _currentPiece->Type == DoubleKylin;
						const bool lcond5 = (abs(_oldX - i) > 2 || abs(_oldY - j) > 2 ||
							abs(_oldX - i) + abs(_oldY - j) > 1 && abs(_oldX - i) != abs(_oldY - j) ||
                            abs(_oldX - i) == 1 && abs(_oldY - j) == 1) && _currentPiece->Type == DoublePhoenix;
						const bool lcond6 = !(abs(_oldX - i) == 2 && abs(_oldY - j) == 1 || abs(_oldX - i) == 1 && abs(_oldY - j) == 2) &&
                            _currentPiece->Type == WingedHorse;
						const bool lcond7 = _tcMoves.empty() && (abs(_oldX - i) > 1 || abs(_oldY - j) > 1) &&
                            _currentPiece->Type == Thunderclap;
						const bool lcond8 = !_tcMoves.empty() && 
							(abs(_tcMoves[_tcMoves.size() - 1].first - i) > 1 || abs(_tcMoves[_tcMoves.size() - 1].second - j) > 1) &&
                            _currentPiece->Type == Thunderclap;
						if ((lcond1 || lcond2 || lcond3 || lcond4 || lcond5 || lcond6 || lcond7 || lcond8) && _board->GetData(i, j) != std::nullopt)
						{
							painter.setBrush(QColorConstants::Svg::lightpink);
                            painter.setPen(Qt::NoPen);
                            painter.drawEllipse(rect);
                            painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            painter.setBrush(Qt::NoBrush);
						}
						else if ((lcond1 || lcond2 || lcond3 || lcond4 || lcond5 || lcond6 || lcond7 || lcond8) && _board->GetData(i, j) == std::nullopt)
						{
							painter.setBrush(QColorConstants::Svg::greenyellow);
                            painter.setPen(Qt::NoPen);
                            painter.drawEllipse(rect);
                            painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) != std::nullopt)
						{
							painter.setBrush(QColorConstants::Svg::hotpink);
                            painter.setPen(Qt::NoPen);
                            painter.drawEllipse(rect);
                            painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) == std::nullopt)
						{
							painter.setBrush(QColorConstants::Svg::lightgreen);
                            painter.setPen(Qt::NoPen);
                            painter.drawEllipse(rect);
                            painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            painter.setBrush(Qt::NoBrush);
						}
					}
                    else if (_gameVariant != ToriShogi && _gameVariant != GrandeAcedrex && _gameVariant != MusketeerChess &&
                             EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, i, j))
					{
						if (_board->GetData(i, j) != std::nullopt)
						{
							painter.setBrush(QColorConstants::Svg::hotpink);
                            if (_gameVariant != KoShogi)
                            {
                                painter.drawRect(rect);
                            }
                            else
                            {
                                painter.setPen(Qt::NoPen);
                                painter.drawEllipse(rect);
                                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            }
                            painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) == std::nullopt)
						{
							painter.setBrush(QColorConstants::Svg::lightgreen);
                            if (_gameVariant != KoShogi)
                            {
                                painter.drawRect(rect);
                            }
                            else
                            {
                                painter.setPen(Qt::NoPen);
                                painter.drawEllipse(rect);
                                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            }
                            painter.setBrush(Qt::NoBrush);
						}
					}
					else if (i == _oldX && j == _oldY)
					{
						if (_board->GetData(i, j) != std::nullopt)
						{
							painter.setBrush(Qt::blue);
                            if (_gameVariant != KoShogi)
                            {
                                painter.drawRect(rect);
                            }
                            else
                            {
                                painter.setPen(Qt::NoPen);
                                painter.drawEllipse(rect);
                                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            }
                            painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) == std::nullopt)
						{
							painter.setBrush(Qt::cyan);
                            if (_gameVariant != KoShogi)
                            {
                                painter.drawRect(rect);
                            }
                            else
                            {
                                painter.setPen(Qt::NoPen);
                                painter.drawEllipse(rect);
                                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            }
                            painter.setBrush(Qt::NoBrush);
						}
					}
					else
					{
						if (_board->GetData(i, j) != std::nullopt)
						{
							painter.setBrush(Qt::red);
                            if (_gameVariant != KoShogi)
                            {
                                painter.drawRect(rect);
                            }
                            else
                            {
                                painter.setPen(Qt::NoPen);
                                painter.drawEllipse(rect);
                                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            }
                            painter.setBrush(Qt::NoBrush);
						}
						else if (_board->GetData(i, j) == std::nullopt)
						{
							painter.setBrush(Qt::cyan);
                            if (_gameVariant != KoShogi)
                            {
                                painter.drawRect(rect);
                            }
                            else
                            {
                                painter.setPen(Qt::NoPen);
                                painter.drawEllipse(rect);
                                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                            }
                            painter.setBrush(Qt::NoBrush);
						}
					}
				}
                else if (_currentPiece != std::nullopt && _currentPiece->Type == HeavenlyTetrarch &&
					abs(_oldX - i) + abs(_oldY - j) >= 1 && abs(_oldX - i) + abs(_oldY - j) <= 2)
				{
					if (_board->GetData(i, j) != std::nullopt)
					{
						painter.setBrush(QColorConstants::Svg::orange);
						painter.drawRect(rect);
						painter.setBrush(Qt::NoBrush);
					}
				}
				else if (_board->GetData(i, j) != std::nullopt)
				{
                    if (_board->GetData(i, j)->Colour != _currentPlayer)
					{
						painter.setBrush(Qt::red);
					}
					else
					{
						painter.setBrush(Qt::magenta);
					}
                    if (_gameVariant != KoShogi && _gameVariant != Xiangqi && _gameVariant != Janggi)
                    {
                        painter.drawRect(rect);
                    }
                    else
                    {
                        painter.setPen(Qt::NoPen);
                        painter.drawEllipse(rect);
                        painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                    }
                    painter.setBrush(Qt::NoBrush);
				}
				else if (_board->GetData(i, j) == std::nullopt)
				{
					painter.setBrush(Qt::cyan);
                    if (_gameVariant != KoShogi && _gameVariant != Xiangqi && _gameVariant != Janggi)
                    {
                        painter.drawRect(rect);
                    }
                    else
                    {
                        painter.setPen(Qt::NoPen);
                        painter.drawEllipse(rect);
                        painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                    }
                    painter.setBrush(Qt::NoBrush);
				}
			}
			else if (std::ranges::any_of(_shoots, [=](std::pair<int, int> t) {return t.first == i && t.second == j;}) && _highlightShoots)
			{
				painter.setBrush(QColorConstants::Svg::violet);
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(rect);
                painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                painter.setBrush(Qt::NoBrush);
			}
			else if (std::ranges::any_of(_attackers, [=](std::pair<int, int> t) {return t.first == i && t.second == j;}) && _highlightAttackers)
			{
				painter.setBrush(QColorConstants::Svg::salmon);
                if (_gameVariant != KoShogi)
                {
                    painter.drawRect(rect);
                }
                else
                {
                    painter.setPen(Qt::NoPen);
                    painter.drawEllipse(rect);
                    painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                }
                painter.setBrush(Qt::NoBrush);
			}
			else if (std::ranges::any_of(_defenders, [=](std::pair<int, int> t) {return t.first == i && t.second == j;}) && _highlightDefenders)
			{
				painter.setBrush(QColorConstants::Svg::aquamarine);
                if (_gameVariant != KoShogi)
                {
                    painter.drawRect(rect);
                }
                else
                {
                    painter.setPen(Qt::NoPen);
                    painter.drawEllipse(rect);
                    painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                }
                painter.setBrush(Qt::NoBrush);
			}
			else if ((_lastWhiteMoveFrom.first == i && _lastWhiteMoveFrom.second == j || _lastWhiteMoveTo.first == i && _lastWhiteMoveTo.second == j) && _highlightLastMoves)
			{
				painter.setBrush(QColor(245, 245, 220, 127));
                if (_gameVariant != KoShogi && _gameVariant != Xiangqi && _gameVariant != Janggi)
                {
                    painter.drawRect(rect);
                }
                else
                {
                    painter.setPen(Qt::NoPen);
                    painter.drawEllipse(rect);
                    painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                }
                painter.setBrush(Qt::NoBrush);
			}
			else if ((_lastBlackMoveFrom.first == i && _lastBlackMoveFrom.second == j || _lastBlackMoveTo.first == i && _lastBlackMoveTo.second == j) && _highlightLastMoves)
			{
				painter.setBrush(QColor(255, 228, 196, 127));
                if (_gameVariant != KoShogi && _gameVariant != Xiangqi && _gameVariant != Janggi)
                {
                    painter.drawRect(rect);
                }
                else
                {
                    painter.setPen(Qt::NoPen);
                    painter.drawEllipse(rect);
                    painter.setPen(_editorMode ? Qt::magenta : Qt::black);
                }
                painter.setBrush(Qt::NoBrush);
			}
			// En Passant square highlighting
            else if (std::ranges::find(chessVariants, _gameVariant) != std::end(chessVariants) &&
					 dynamic_cast<ChessBoard*>(_board)->GetEnPassant() != "-" && dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[0] - 97 == i &&
					 EngineOutputHandler::GetEnPassantRank(_gameVariant, _currentPlayer, dynamic_cast<ChessBoard*>(_board)->GetEnPassant()[1]) == j)
			{
				painter.setBrush(Qt::blue);
				painter.drawRect(rect);
				painter.setBrush(Qt::NoBrush);
			}
			// Frozen pieces highlighting
			else if (_gameVariant == KoShogi && _board->GetData(i, j) != std::nullopt && !_board->GetData(i, j)->CanMove)
			{
				painter.setBrush(QColorConstants::Svg::lightsteelblue);
				painter.drawEllipse(rect);
				painter.setBrush(Qt::NoBrush);
			}
			else
			{
                if (std::ranges::find(chessVariants, _gameVariant) != std::end(chessVariants) || _gameVariant == CourierChess ||
					_gameVariant == GrandeAcedrex || _gameVariant == Shatranj || _gameVariant == Makruk || _gameVariant == Shatar ||
					_gameVariant == Sittuyin)
				{
					if ((i + j) % 2 != 0)
						painter.setBrush(Qt::gray);
				}
				if (_gameVariant == MusketeerChess)
				{
					if (j == 0 || j == _board->GetHeight() - 1)
						painter.setBrush(QColorConstants::Svg::wheat);
				}
				if (_gameVariant != KoShogi && _gameVariant != Xiangqi && _gameVariant != Janggi)
                {
                    painter.drawRect(rect);
                }
				painter.setBrush(Qt::NoBrush);
			}
		}
	}
    if (_gameVariant == KoShogi || _gameVariant == Xiangqi || _gameVariant == Janggi)
    {
        for (int i = 0; i < _board->GetWidth() - 1; i++)
        {
            for (int j = 0; j < _board->GetHeight() - 1; j++)
            {
                if (_gameVariant == KoShogi || _gameVariant == Janggi || j != 4)
                {
					painter.drawRect(i * w + w / 2, j * h + h / 2, w, h);
                }
                if (_gameVariant == KoShogi && (i == 3 || i == 9 || i == 15) && (j == 3 || j == 9 || j == 15))
                {
                    painter.setBrush(Qt::black);
                    painter.drawEllipse(i * w + w / 2 - 5, j * h + h / 2 - 5, 10, 10);
                    painter.setBrush(Qt::NoBrush);
                }
                else if (_gameVariant == Xiangqi && (i == 3 && j == 0 || i == 4 && j == 1 || i == 3 && j == 7 || i == 4 && j == 8))
                {
                    painter.setBrush(Qt::black);
                    painter.drawLine(i * w + w / 2, j * h + h / 2, (i + 1) * w + w / 2, (j + 1) * h + h / 2);
                    painter.setBrush(Qt::NoBrush);
                }
                else if (_gameVariant == Xiangqi && (i == 4 && j == 0 || i == 3 && j == 1 || i == 4 && j == 7 || i == 3 && j == 8))
                {
                    painter.setBrush(Qt::black);
                    painter.drawLine((i + 1) * w + w / 2, j * h + h / 2, i * w + w / 2, (j + 1) * h + h / 2);
                    painter.setBrush(Qt::NoBrush);
                }
            }
        }
    }
    for (int i = 0; i < _board->GetWidth(); i++)
	{
		for (int j = 0; j < _board->GetHeight(); j++)
		{
			std::optional<Piece> p = _board->GetData(i, j);
			if (p != std::nullopt)
			{
                GraphicsManager::DrawPiece(painter, p.value(), _gameVariant, _pieceStyle, w, h, i, j);
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
			(!_board->HasPiece(MiddleTroop, Black) || !_board->HasPiece(Flag, Black)) &&
			!_board->HasPiece(Prince, Black) && !_board->HasPiece(Emperor, Black) && _gameVariant != Sittuyin)
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
			!_board->HasPiece(Prince, White) && !_board->HasPiece(Emperor, White) && _gameVariant != Sittuyin)
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
    _statusBar->showMessage(_currentPlayer == White ? _gameVariant == Xiangqi || _gameVariant == Janggi ? "Red move" : "White move" : "Black move");
	_currentPiece = std::nullopt;
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
	if (!_editorMode && _gameVariant == Sittuyin && !dynamic_cast<SittuyinBoard*>(_board)->GetCapturedPieces(_currentPlayer).empty()) return;
	if (event->button() != Qt::MouseButton::LeftButton) return;
	const int w = this->size().width() / _board->GetWidth();
	const int h = this->size().height() / _board->GetHeight();
    const int x = static_cast<int>(event->position().x()) / w;
    const int y = static_cast<int>(event->position().y()) / h;
	if (!_editorMode && _gameVariant == MusketeerChess)
	{
		if (_currentPlayer == White && dynamic_cast<MusketeerChessBoard*>(_board)->WhitePiecesToPlace > 0) return;
		if (_currentPlayer == Black && dynamic_cast<MusketeerChessBoard*>(_board)->BlackPiecesToPlace > 0) return;
		if (y == 0 || y == _board->GetHeight() - 1) return;
	}
	std::optional<Piece> p = _board->GetData(x, y);
	if (_editorMode && _editor != nullptr)
	{
		auto chosenPiece = _editor->GetBoard()->GetChosenPiece();
		_board->SetData(x, y, chosenPiece);
		if (chosenPiece != std::nullopt)
		{
			if (std::ranges::find(_promotedPieces, chosenPiece->Type) != std::end(_promotedPieces))
			{
				if (_gameVariant != MicroShogi && _gameVariant != KyotoShogi &&
					_gameVariant != GrandeAcedrex && _gameVariant != MusketeerChess)
				{
					_board->Promote(x, y);
				}
			}
		}
		repaint();
		return;
	}
	if (_comm != nullptr && _comm->is_connected_remotely() && _waitForOtherPlayer) return;
	if (_blackEngine != nullptr && _blackEngine->IsActive() && _currentPlayer == Black ||
		_whiteEngine != nullptr && _whiteEngine->IsActive() && _currentPlayer == White) return;
	const std::shared_ptr<Engine> engine = _currentPlayer == White ? _blackEngine : _whiteEngine;
    const bool isLionPiece = _currentPiece != std::nullopt && std::ranges::find(lionPieces, _currentPiece->Type) != std::end(lionPieces);
	const bool isShootingPiece = _gameVariant == KoShogi && _currentPiece != std::nullopt &&
        std::ranges::find(ShootingPieces, _currentPiece->Type) != std::end(ShootingPieces);
	// Castling check
    if ((_gameVariant == Chess || _gameVariant == CapablancaChess || _gameVariant == GothicChess ||
         _gameVariant == JanusChess || _gameVariant == ChancellorChess || _gameVariant == ModernChess ||
         _gameVariant == OmegaChess || _gameVariant == NightriderChess || _gameVariant == MusketeerChess) &&
        _currentPiece != std::nullopt && _currentPiece->Type == King && !_currentPiece->HasMoved &&
        p != std::nullopt && p->Colour == _currentPlayer && p->Type == Rook && !p->HasMoved && _board->IsMovePossible(x, y))
	{
        if (_gameVariant == JanusChess)
        {
			if (_board->IsSquareUnderAttack(_oldX < x ? _oldX + 4 : _oldX - 3, _oldY, _currentPlayer))
			{
				QMessageBox::warning(this, "Warning", "Castling destination square is under attack.");
			}
			else
			{
				_board->Move(_oldX, _oldY, _oldX < x ? _oldX + 4 : _oldX - 3, _oldY, false);
				_board->Move(x, y, _oldX < x ? x - 2 : x + 2, y, false);
				if (engine != nullptr && engine->IsActive())
				{
					engine->Move(_oldX, _board->GetHeight() - _oldY, _oldX < x ? _oldX + 3 : _oldX - 3, _board->GetHeight() - y, ' ');
				}
				dynamic_cast<ChessBoard*>(_board)->WriteCastling(x > _oldX ? "O-O" : "O-O-O");
				FinishMove(x, y);
			}
        }
		else if (_gameVariant == CapablancaChess || _gameVariant == GothicChess)
		{
			if (_board->IsSquareUnderAttack(_oldX < x ? _oldX + 3 : _oldX - 3, _oldY, _currentPlayer))
			{
				QMessageBox::warning(this, "Warning", "Castling destination square is under attack.");
			}
			else
			{
				_board->Move(_oldX, _oldY, _oldX < x ? _oldX + 3 : _oldX - 3, _oldY, false);
				_board->Move(x, y, _oldX < x ? x - 2 : x + 3, y, false);
				if (engine != nullptr && engine->IsActive())
				{
					engine->Move(_oldX, _board->GetHeight() - _oldY, _oldX < x ? _oldX + 3 : _oldX - 3, _board->GetHeight() - y, ' ');
				}
				dynamic_cast<ChessBoard*>(_board)->WriteCastling(x > _oldX ? "O-O" : "O-O-O");
				FinishMove(x, y);
			}
		}
		else if (_gameVariant == ChancellorChess || _gameVariant == ModernChess)
		{
			if (_board->IsSquareUnderAttack(_oldX < x ? _oldX + 2 : _oldX - 2, _oldY, _currentPlayer))
			{
				QMessageBox::warning(this, "Warning", "Castling destination square is under attack.");
			}
			else
			{
				_board->Move(_oldX, _oldY, _oldX < x ? _oldX + 2 : _oldX - 2, _oldY, false);
				_board->Move(x, y, _oldX < x ? x - 3 : x + 3, y, false);
				if (engine != nullptr && engine->IsActive())
				{
					engine->Move(_oldX, _board->GetHeight() - _oldY, _oldX < x ? _oldX + 2 : _oldX - 2, _board->GetHeight() - y, ' ');
				}
				dynamic_cast<ChessBoard*>(_board)->WriteCastling(x > _oldX ? "O-O" : "O-O-O");
				FinishMove(x, y);
			}
		}
        else
        {
			if (_board->IsSquareUnderAttack(_oldX < x ? _oldX + 2 : _oldX - 2, _oldY, _currentPlayer))
			{
				QMessageBox::warning(this, "Warning", "Castling destination square is under attack.");
			}
			else
			{
				_board->Move(_oldX, _oldY, _oldX < x ? _oldX + 2 : _oldX - 2, _oldY, false);
				_board->Move(x, y, _oldX < x ? x - 2 : x + 3, y, false);
				if (engine != nullptr && engine->IsActive())
				{
					engine->Move(_oldX, _board->GetHeight() - _oldY, _oldX < x ? _oldX + 2 : _oldX - 2, _board->GetHeight() - y, ' ');
				}
				dynamic_cast<ChessBoard*>(_board)->WriteCastling(x > _oldX ? "O-O" : "O-O-O");
				FinishMove(x, y);
			}
        }
	}
	// Null move
	else if ((_gameVariant == ChuShogi || _gameVariant == DaiShogi || _gameVariant == TenjikuShogi ||
		_gameVariant == DaiDaiShogi || _gameVariant == MakaDaiDaiShogi || _gameVariant == KoShogi || _gameVariant == TaiShogi) &&
        _currentPiece != std::nullopt && p != std::nullopt && p->Colour == _currentPlayer &&
        x == _oldX && y == _oldY && !_lionMovedOnce && _currentPiece->Type != Thunderclap &&
        (isLionPiece || _currentPiece->Type == ViceGeneral || _currentPiece->Type == FireDemon || _currentPiece->Type == HeavenlyTetrarch))
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
    else if (_currentPiece != std::nullopt && (p == std::nullopt || p->Colour != _currentPlayer) && !CheckRepetition(_oldX, _oldY, x, y))
	{
		if (isLionPiece && !_lionMovedOnce && EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y))
		{
            if (_tcMoves.empty() && (abs(_oldX - x) > 1 || abs(_oldY - y) > 1) && _currentPiece->Type == Thunderclap)
			{
			}
			else if (!_tcMoves.empty() && (abs(_tcMoves[_tcMoves.size() - 1].first - x) > 1 ||
                abs(_tcMoves[_tcMoves.size() - 1].second - y) > 1) && _currentPiece->Type == Thunderclap)
			{
			}
            else if (std::ranges::find(_tcMoves, std::pair(x, y)) != std::end(_tcMoves))
			{
			}
            else if (_currentPiece->Type == Thunderclap && PossibleMove(x, y))
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
                    _tcMoves.insert(_tcMoves.begin(), _board->GetPieceLocation(Thunderclap, _currentPlayer));
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
                abs(_oldX - x) == 2 && abs(_oldY - y) == 2) && _currentPiece->Type == RisingDragon)
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
                _currentPiece->Type == WingedTiger)
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
            else if (PossibleMove(x, y) && (abs(_oldX - x) == 1 && abs(_oldY - y) == 1) && _currentPiece->Type == FlyingHawk)
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
            else if (_gameVariant == KoShogi && (abs(_oldX - x) == 2 || abs(_oldY - y) == 2) && _currentPiece->Type == Lion)
			{
			}
			else if (_gameVariant == KoShogi && (abs(_oldX - x) == 2 && abs(_oldY - y) == 1 || abs(_oldX - x) == 1 && abs(_oldY - y) == 2) &&
                _currentPiece->Type == RisingDragon)
			{
			}
            else if (_gameVariant == KoShogi && (abs(_oldX - x) == 2 && abs(_oldY - y) == 2) && _currentPiece->Type == WingedTiger)
			{
			}
            else if (abs(_oldX - x) + abs(_oldY - y) > 1 && _currentPiece->Type == FlyingHawk)
			{
			}
            else if (PossibleMove(x, y) && _currentPiece->Type == RoamingAssault)
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
                (_currentPiece->Type == Lion || _currentPiece->Type == LionHawk ||
                    _currentPiece->Type == BuddhistSpirit || _currentPiece->Type == FreeEagle))
			{
				// Lion capture rule #1
				if (_gameVariant == ChuShogi && _board->GetData(x, y) != std::nullopt &&
                    _currentPiece->Type == Lion && _board->GetData(x, y)->Type == Lion &&
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
					CheckPromotion(p, x, y);
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) == 2 || abs(_oldY - y) == 2) &&
                (_currentPiece->Type == LionDog || _currentPiece->Type == FuriousFiend ||
                    _currentPiece->Type == GreatElephant || _currentPiece->Type == TeachingKing))
			{
				if (p != std::nullopt)
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
					CheckPromotion(p, x, y);
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y) && (abs(_oldX - x) >= 3 || abs(_oldY - y) >= 3) &&
                (_currentPiece->Type == LionDog || _currentPiece->Type == FuriousFiend ||
                    _currentPiece->Type == GreatElephant || _currentPiece->Type == TeachingKing))
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, x, y);
					FinishMove(x, y);
				}
			}
            else if (PossibleMove(x, y) && (abs(_oldX - x) == 2 && _oldY - y == 2 && _currentPiece->Type == Eagle && _currentPiece->Colour == White) ||
                (abs(_oldX - x) == 2 && _oldY - y == -2 && _currentPiece->Type == Eagle && _currentPiece->Colour == Black) ||
                (_oldX == x && _oldY - y == 2 && _currentPiece->Type == Falcon && _currentPiece->Colour == White) ||
                (_oldX == x && _oldY - y == -2 && _currentPiece->Type == Falcon && _currentPiece->Colour == Black))
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, x, y);
					FinishMove(x, y);
				}
			}
			else if (!(abs(_oldX - x) == 2 && abs(_oldY - y) == 1 || abs(_oldX - x) == 1 && abs(_oldY - y) == 2) &&
                _currentPiece->Type == KnightCaptain)
			{
			}
			else if (!(abs(_oldX - x) == 2 && abs(_oldY - y) == 0 || abs(_oldX - x) == 0 && abs(_oldY - y) == 2 ||
                abs(_oldX - x) == 2 && abs(_oldY - y) == 2) && (_currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight))
			{
			}
            else if ((abs(_oldX - x) == 4 || abs(_oldY - y) == 4) && (_currentPiece->Type == KnightCaptain ||
                _currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight))
			{
			}
			else if (!(abs(_oldX - x) == 2 && abs(_oldY - y) == 1 || abs(_oldX - x) == 1 && abs(_oldY - y) == 2) && 
                _currentPiece->Type == WingedHorse)
			{
			}
            else if (abs(_oldX - x) + abs(_oldY - y) > 2 && _currentPiece->Type == DoubleKylin)
			{
			}
			else if ((abs(_oldX - x) > 2 || abs(_oldY - y) > 2 || abs(_oldX - x) + abs(_oldY - y) > 1 && abs(_oldX - x) != abs(_oldY - y) ||
                abs(_oldX - x) == 1 && abs(_oldY - y) == 1) && _currentPiece->Type == DoublePhoenix)
			{
			}
			else if (_gameVariant == KoShogi && _board->GetData(x, y) == std::nullopt)
			{
				_lionFirstMove = { x, y };
				_lionMovedOnce = true;
				for (int index = _moves.size() - 1; index >= 0; index--)
				{
                    if (_currentPiece->Type == Lion || _currentPiece->Type == RisingDragon)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == WingedTiger)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) != 1 ||
							abs(_moves[index].first - x) != 1 && abs(_moves[index].second - y) == 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == FlyingHawk)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) + abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight)
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
                    else if (_currentPiece->Type == KnightCaptain)
					{
						if (abs(_moves[index].first - x) >= 3 || abs(_moves[index].second - y) >= 3 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 0 ||
							abs(_moves[index].first - x) == 0 && abs(_moves[index].second - y) == 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == WingedHorse)
					{
						if (!(abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 2))
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == DoubleKylin)
					{
						if (abs(_moves[index].first - x) + abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == DoublePhoenix)
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
			else if (PossibleMove(x, y) && _board->GetData(x, y) == std::nullopt)
			{
				if (_board->Move(_oldX, _oldY, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, x, y);
					FinishMove(x, y);
				}
			}
			else if (PossibleMove(x, y))
			{
				_lionFirstMove = { x, y };
				_lionMovedOnce = true;
				for (int index = _moves.size() - 1; index >= 0; index--)
				{
                    if (_currentPiece->Type == LionDog || _currentPiece->Type == FuriousFiend ||
                        _currentPiece->Type == TeachingKing)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == GreatElephant)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 2 || abs(_moves[index].second - y) > 2 ||
							_currentPlayer == White && abs(_moves[index].first - _oldX) != 0 && _moves[index].second < _oldY ||
							_currentPlayer == Black && abs(_moves[index].first - _oldX) != 0 && _moves[index].second > _oldY)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == Lion || _currentPiece->Type == LionHawk ||
                        _currentPiece->Type == BuddhistSpirit || _currentPiece->Type == RisingDragon)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == FreeEagle || _currentPiece->Type == Eagle || _currentPiece->Type == WingedTiger)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) != 1 ||
							abs(_moves[index].first - x) != 1 && abs(_moves[index].second - y) == 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == Falcon)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) > 1 || abs(_moves[index].second - y) > 1 ||
							abs(_moves[index].first - x) != 0)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == FlyingHawk)
					{
						if (!EngineOutputHandler::IsLionMove(_currentPiece, _oldX, _oldY, x, y) ||
							abs(_moves[index].first - x) + abs(_moves[index].second - y) > 1)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight)
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
                    else if (_currentPiece->Type == KnightCaptain)
					{
						if (abs(_moves[index].first - x) >= 3 || abs(_moves[index].second - y) >= 3 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 0 ||
							abs(_moves[index].first - x) == 0 && abs(_moves[index].second - y) == 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == WingedHorse)
					{
						if (!(abs(_moves[index].first - x) == 2 && abs(_moves[index].second - y) == 1 ||
							abs(_moves[index].first - x) == 1 && abs(_moves[index].second - y) == 2))
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == DoubleKylin)
					{
						if (abs(_moves[index].first - x) + abs(_moves[index].second - y) > 2)
						{
							_moves.erase(_moves.begin() + index);
						}
					}
                    else if (_currentPiece->Type == DoublePhoenix)
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
            if (_currentPiece->Type == Lion || _currentPiece->Type == LionHawk ||
                _currentPiece->Type == BuddhistSpirit || _currentPiece->Type == FreeEagle ||
                _currentPiece->Type == Falcon || _currentPiece->Type == Eagle ||
                _currentPiece->Type == WingedTiger || _currentPiece->Type == FlyingHawk ||
                _currentPiece->Type == RisingDragon)
			{
				if (PossibleMove(x, y))
				{
					if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
					{
						if (engine != nullptr && engine->IsActive())
						{
							std::dynamic_pointer_cast<WbEngine>(engine)->DoubleMove(_oldX, _board->GetHeight() - _oldY,
								_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
						}
						CheckPromotion(p, x, y);
						FinishMove(x, y);
					}
				}
			}
            else if (_currentPiece->Type == LionDog || _currentPiece->Type == FuriousFiend ||
                _currentPiece->Type == GreatElephant || _currentPiece->Type == TeachingKing)
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
								std::dynamic_pointer_cast<WbEngine>(engine)->TripleMove(_oldX, _board->GetHeight() - _oldY,
									_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second,
									_lionSecondMove.first, _board->GetHeight() - _lionSecondMove.second,
									x, _board->GetHeight() - y);
							}
							CheckPromotion(p, x, y);
							FinishMove(x, y);
						}
					}
					else
					{
						if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
						{
							if (engine != nullptr && engine->IsActive())
							{
								std::dynamic_pointer_cast<WbEngine>(engine)->DoubleMove(_oldX, _board->GetHeight() - _oldY,
									_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
							}
							CheckPromotion(p, x, y);
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
								std::dynamic_pointer_cast<WbEngine>(engine)->DoubleMove(_oldX, _board->GetHeight() - _oldY,
									_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
							}
							CheckPromotion(p, x, y);
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
                (_currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight))
			{
				if (_lionMovedTwice)
				{
					KoShogiBoard* ksBoard = dynamic_cast<KoShogiBoard*>(_board);
					ksBoard->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, _lionSecondMove.first, _lionSecondMove.second);
					ksBoard->Shoot(x, y);
					FinishMove(x, y);
				}
				else
				{
					_firstShoot = { x, y };
					_preparedToShoot = false;
					_pieceShotOnce = true;
					_shoots.clear();
					repaint();
				}
			}
			else if (PossibleMove(x, y) &&
                (_currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight))
			{
				KoShogiBoard* ksBoard = dynamic_cast<KoShogiBoard*>(_board);
				_shoots = ksBoard->GetShoots(_currentPiece, x, y);
				if (!_lionMovedTwice && !_shoots.empty())
				{
					_lionSecondMove = { x, y };
					_lionMovedTwice = true;
					_preparedToShoot = true;
					_board->RemoveMove(_lionFirstMove.first, _lionFirstMove.second);
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
			else if ((_moves.empty() || _lionMovedTwice) && PossibleShoot(x, y) &&
                (_currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight))
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
            else if (PossibleMove(x, y) && (_currentPiece->Type == KnightCaptain || _currentPiece->Type == WingedHorse ||
                _currentPiece->Type == DoubleKylin || _currentPiece->Type == DoublePhoenix))
			{
				if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
				{
					if (engine != nullptr && engine->IsActive())
					{
						std::dynamic_pointer_cast<WbEngine>(engine)->DoubleMove(_oldX, _board->GetHeight() - _oldY,
							_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
					}
					CheckPromotion(p, x, y);
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
				_board->Move(_oldX, _oldY, x, y);
				FinishMove(x, y);
			}
		}
		else if (isShootingPiece && _preparedToShoot && PossibleShoot(x, y))
		{
			KoShogiBoard* ksBoard = dynamic_cast<KoShogiBoard*>(_board);
            if (_currentPiece->BaseType == FrankishCannon && !_pieceShotOnce)
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
                if (_currentPiece->BaseType == FrankishCannon && _pieceShotOnce)
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
            const char promotion = CheckPromotion(p, x, y);
			if (engine != nullptr && engine->IsActive())
			{
                if (_gameVariant == Xiangqi || _gameVariant == Janggi || _gameVariant == GrandChess || _gameVariant == MusketeerChess)
					engine->Move(_oldX, _board->GetHeight() - _oldY - 1, x, _board->GetHeight() - y - 1, promotion);
                else if (engine->GetType() == USI)
					engine->Move(_board->GetWidth() - _oldX, _oldY, _board->GetWidth() - x, y, promotion);
				else
					engine->Move(_oldX, _board->GetHeight() - _oldY, x, _board->GetHeight() - y, promotion);
			}
			if (_board->GetData(x, y) != std::nullopt)
			{
                EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->BaseType, _oldX, _oldY, x, y, promotion, p != std::nullopt ? 'x' : ' ');
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
				std::dynamic_pointer_cast<WbEngine>(engine)->TripleMove(_oldX, _board->GetHeight() - _oldY,
					_lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second,
					_lionSecondMove.first, _board->GetHeight() - _lionSecondMove.second,
					x, _board->GetHeight() - y);
			}
			FinishMove(x, y);
		}
	}
	else if (x == _oldX && y == _oldY && _lionMovedOnce && abs(_lionFirstMove.first - x) <= 2 && abs(_lionFirstMove.second - y) <= 2 &&
        (_currentPiece->Type == KnightCaptain || _currentPiece->Type == ExtensiveFog || _currentPiece->Type == HolyLight ||
        _currentPiece->Type == DoubleKylin || _currentPiece->Type == DoublePhoenix || _currentPiece->Type == WingedHorse))
	{
		if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				std::dynamic_pointer_cast<WbEngine>(engine)->DoubleMove(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
			}
            EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->Type, _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
			FinishMove(x, y);
		}
	}
	else if (x == _oldX && y == _oldY && _lionMovedOnce && abs(_lionFirstMove.first - x) < 2 && abs(_lionFirstMove.second - y) < 2)
	{
		if (dynamic_cast<ChuShogiBoard*>(_board)->DoubleMove(_oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y))
		{
			if (engine != nullptr && engine->IsActive())
			{
				std::dynamic_pointer_cast<WbEngine>(engine)->DoubleMove(_oldX, _board->GetHeight() - _oldY, _lionFirstMove.first, _board->GetHeight() - _lionFirstMove.second, x, _board->GetHeight() - y);
			}
            EngineOutputHandler::AddMove(_board, _gameVariant, _board->GetData(x, y)->Type, _oldX, _oldY, _lionFirstMove.first, _lionFirstMove.second, x, y);
			FinishMove(x, y);
		}
	}
    else if (p != std::nullopt && p->Colour == _currentPlayer)
	{
		_currentPiece = _board->GetData(x, y);
		_oldX = x;
		_oldY = y;
		_board->GetMoves(p, x, y);
		_preparedToShoot = false;
		_shoots.clear();
		_moves = _board->Moves();
		CancelLionMove();
        if (_gameVariant != ShoShogi && _gameVariant != ChuShogi && _gameVariant != DaiShogi && _gameVariant != TenjikuShogi &&
            _gameVariant != DaiDaiShogi && _gameVariant != MakaDaiDaiShogi && _gameVariant != KoShogi && _gameVariant != TaiShogi)
		{
            for (int index = 0; index < 4; index++)
			{
				std::ranges::for_each(_moves, [this, x, y](std::pair<int, int> t)
				{
					EngineOutputHandler::CalculateCheck(_board, _currentPlayer, _moves, x, y, t.first, t.second);
				});
			}
		}
        if (_gameVariant == Xiangqi || (_gameVariant == Janggi && dynamic_cast<XiangqiBoard*>(_board)->AreTwoKingsLookingOnEachOther()))
        {
            std::ranges::for_each(_moves, [this, x, y](std::pair<int, int> t)
            {
	            EngineOutputHandler::CalculateXiangqiCheck(_board, _moves, x, y, t.first, t.second);
            });
        }
        if (_gameVariant == OmegaChess)
        {
            std::ranges::for_each(_moves, [this](std::pair<int, int> t)
            {
	            if (t.second == 0 && t.first >= 1 && t.first <= _board->GetWidth() - 2 ||
		            t.second == _board->GetHeight() - 1 && t.first >= 1 && t.first <= _board->GetWidth() - 2 ||
		            t.first == 0 && t.second >= 1 && t.second <= _board->GetHeight() - 2 ||
		            t.first == _board->GetWidth() - 1 && t.second >= 1 && t.second <= _board->GetHeight() - 2)
	            {
		            _board->RemoveMove(t.first, t.second);
		            EngineOutputHandler::RemoveMove(_moves, t.first, t.second);
	            }
            });
        }
        this->repaint();
	}
}

char VBoard::CheckPromotion(const std::optional<Piece>& p, int x, int y)
{
	char promotion = ' ';
	if (_gameVariant == GrandeAcedrex)
	{
		if (_currentPiece->Type == Pawn &&
			((y == 11 && _currentPiece->Colour == Black) ||
				(y == 0 && _currentPiece->Colour == White)))
		{
			switch (x)
			{
			case 0:
			case 11:
				promotion = 'r';
				_board->Promote(x, y, Rook);
				break;
			case 1:
			case 10:
				promotion = 'l';
				_board->Promote(x, y, Lion);
				break;
			case 2:
			case 9:
				promotion = 'u';
				_board->Promote(x, y, Unicorn);
				break;
			case 3:
			case 8:
				promotion = 'g';
				_board->Promote(x, y, Giraffe);
				break;
			case 4:
			case 7:
				promotion = 'c';
				_board->Promote(x, y, Bishop);
				break;
			default:
				promotion = 'a';
				_board->Promote(x, y, Aanca);
				break;
			}
		}
	}
	else if (_gameVariant == GrandChess)
    {
        GrandChessBoard* gcBoard = dynamic_cast<GrandChessBoard*>(_board);
        auto capturedPieces = gcBoard->GetCapturedPieces(_currentPlayer == White ? Black : White);
        if (_currentPiece->Type == Pawn && !capturedPieces.empty() &&
            ((y >= 7 && _currentPiece->Colour == Black) ||
            (y <= 2 && _currentPiece->Colour == White)))
        {
            PromotionDialog* pd = new PromotionDialog(this);
            pd->SetEnabled(Rook, std::ranges::find(capturedPieces, Rook) != std::end(capturedPieces));
            pd->SetEnabled(Knight, std::ranges::find(capturedPieces, Knight) != std::end(capturedPieces));
            pd->SetEnabled(Bishop, std::ranges::find(capturedPieces, Bishop) != std::end(capturedPieces));
            pd->SetEnabled(Queen, std::ranges::find(capturedPieces, Queen) != std::end(capturedPieces));
            pd->SetEnabled(Archbishop, std::ranges::find(capturedPieces, Archbishop) != std::end(capturedPieces));
            pd->SetEnabled(Chancellor, std::ranges::find(capturedPieces, Chancellor) != std::end(capturedPieces));
            pd->SetEnabled(Champion, false);
            pd->SetEnabled(Wizard, false);
			pd->SetEnabled(Nightrider, false);
			if (pd->exec() == QDialog::Accepted)
            {
                const PieceType pt = pd->GetChosenPiece();
                promotion = EngineOutputHandler::ChessPieceChar(pt);
                _board->Promote(x, y, pt);
                gcBoard->RemoveCapturedPiece(pt, _currentPlayer);
            }
            else if (y == 9 || y == 0)
            {
                promotion = EngineOutputHandler::ChessPieceChar(capturedPieces[0]);
                _board->Promote(x, y, capturedPieces[0]);
                gcBoard->RemoveCapturedPiece(capturedPieces[0], _currentPlayer);
            }
        }
    }
    else if (_gameVariant == OmegaChess)
    {
        if (_currentPiece->Type == Pawn &&
            ((y == 10 && _currentPiece->Colour == Black) ||
            (y == 1 && _currentPiece->Colour == White)))
        {
            PromotionDialog* pd = new PromotionDialog(this);
			pd->SetEnabled(Nightrider, false);
			if (pd->exec() == QDialog::Accepted)
            {
                const PieceType pt = pd->GetChosenPiece();
                promotion = EngineOutputHandler::ChessPieceChar(pt);
                _board->Promote(x, y, pt);
            }
            else
            {
                promotion = 'q';
                _board->Promote(x, y, Queen);
            }
        }
    }
	else if (_gameVariant == MusketeerChess)
	{
		if (_currentPiece->Type == Pawn &&
			((y == 8 && _currentPiece->Colour == Black) ||
			(y == 1 && _currentPiece->Colour == White)))
		{
			PromotionDialog* pd = new PromotionDialog(this);
			pd->SetEnabled(Nightrider, false);
			if (pd->exec() == QDialog::Accepted)
			{
				const PieceType pt = pd->GetChosenPiece();
				promotion = EngineOutputHandler::ChessPieceChar(pt);
				_board->Promote(x, y, pt);
			}
			else
			{
				promotion = 'q';
				_board->Promote(x, y, Queen);
			}
		}
	}
	else if (std::ranges::find(chessVariants, _gameVariant) != std::end(chessVariants))
    {
        if (_currentPiece->Type == Pawn &&
            ((y == _board->GetHeight() - 1 && _currentPiece->Colour == Black) ||
                (y == 0 && _currentPiece->Colour == White)))
        {
            PromotionDialog* pd = new PromotionDialog(this);
            pd->SetEnabled(Champion, false);
            pd->SetEnabled(Wizard, false);
			pd->SetEnabled(Nightrider, _gameVariant == NightriderChess);
			if (_gameVariant == Chess || _gameVariant == NightriderChess)
            {
                pd->SetEnabled(Archbishop, false);
                pd->SetEnabled(Chancellor, false);
            }
            else if (_gameVariant == JanusChess || _gameVariant == ModernChess)
            {
                pd->SetEnabled(Chancellor, false);
            }
            else if (_gameVariant == ChancellorChess)
            {
                pd->SetEnabled(Archbishop, false);
            }
            if (pd->exec() == QDialog::Accepted)
            {
                const PieceType pt = pd->GetChosenPiece();
                promotion = EngineOutputHandler::ChessPieceChar(pt);
                _board->Promote(x, y, pt);
            }
            else
            {
                promotion = 'q';
                _board->Promote(x, y, Queen);
            }
        }
    }
    else if (_gameVariant == Shatranj)
	{
        if (_currentPiece->Type == Pawn &&
            ((y == _board->GetHeight() - 1 && _currentPiece->Colour == Black) ||
                (y == 0 && _currentPiece->Colour == White)))
		{
			promotion = 'q';
            _board->Promote(x, y);
		}
	}
	else if (_gameVariant == CourierChess)
	{
		if (_currentPiece->Type == Pawn &&
			((y == _board->GetHeight() - 1 && _currentPiece->Colour == Black) ||
				(y == 0 && _currentPiece->Colour == White)))
		{
			promotion = 'f';
			_board->Promote(x, y);
		}
		}
	else if (_gameVariant == Shatar)
	{
		if (_currentPiece->Type == Pawn &&
			((y == _board->GetHeight() - 1 && _currentPiece->Colour == Black) ||
				(y == 0 && _currentPiece->Colour == White)))
		{
			promotion = 'j';
			_board->Promote(x, y);
		}
	}
	else if (_gameVariant == Makruk)
	{
        if (_currentPiece->Type == Pawn &&
            ((y >= 5 && _currentPiece->Colour == Black) ||
                (y <= 2 && _currentPiece->Colour == White)))
		{
			promotion = _currentPlayer == White ? 'M' : 'm';
            _board->Promote(x, y);
		}
	}
	else if (_gameVariant == Sittuyin)
	{
		if (_currentPiece->Type == Pawn &&
			(x == y + 1 || x == _board->GetHeight() - y - 1) &&
			(y <= 3 && _currentPlayer == White || y >= 4 && _currentPlayer == Black) &&
			!_board->HasPiece(Queen, _currentPlayer))
		{
			promotion = 'f';
			_board->Promote(x, y);
		}
	}
	else if (_gameVariant == KyotoShogi)
    {
        if (_currentPiece->Type != King)
        {
            promotion = '+';
            _board->Promote(x, y);
        }
    }
    else if (_gameVariant == DaiDaiShogi || _gameVariant == TaiShogi)
	{
        if (!_currentPiece->IsPromoted && p != std::nullopt &&
			std::ranges::find(UnpromotablePieces,
			                  _currentPiece->Type) == std::end(UnpromotablePieces))
		{
			promotion = '+';
            _board->Promote(x, y);
		}
	}
	else if (_gameVariant == MakaDaiDaiShogi)
	{
        if (_currentPiece->Type != Queen && _currentPiece->Type != DragonKing &&
            _currentPiece->Type != DragonHorse && !_currentPiece->IsPromoted && p != std::nullopt)
		{
            if (p->BaseType == Deva)
			{
				promotion = '+';
                _board->Promote(x, y, TeachingKing);
			}
            else if (p->BaseType == DarkSpirit)
			{
				promotion = '+';
                _board->Promote(x, y, BuddhistSpirit);
			}
            else if (p->IsPromoted || AskForPromotion())
			{
				promotion = '+';
                _board->Promote(x, y);
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
        if (dynamic_cast<KoShogiBoard*>(_board)->IsTaoistPriestCaptured() && (_currentPiece->Type == Flag || _currentPiece->Type == Drum))
		{
		}
        else if (_currentPiece->Type != King && _currentPiece->Type != Lion &&
            _currentPiece->Type != Bishop && !_currentPiece->IsPromoted && p != std::nullopt)
		{
            if (p->Type == King || p->Type == Prince || p->Type == MiddleTroop || p->Type == Flag || p->Type == Drum)
			{
				promotion = '+';
                _board->Promote(x, y);
			}
            else if (std::ranges::find(StepMovers, _currentPiece->Type) != std::end(StepMovers))
			{
                if (p->Type == Lion || p->Type == RisingDragon || p->Type == RoamingAssault || p->Type == Thunderclap)
				{
					promotion = '+';
                    _board->Promote(x, y);
				}
			}
            else if (_currentPiece->Type == Knight)
			{
                if (p->Type == FrankishCannon)
				{
					promotion = '+';
                    _board->Promote(x, y);
				}
			}
            else if (p->IsPromoted || AskForPromotion())
			{
				promotion = '+';
                _board->Promote(x, y);
			}
			else
			{
				promotion = '=';
			}
			// When the clerk promotes to master at arms, all the allied advance and rear guards promote as well, while any enemy poison flame dies.
            if (promotion == '+' && _currentPiece->BaseType == Kylin && _currentPiece->Type == DoubleKylin)
			{
				const auto aguards = EngineOutputHandler::GetPieceLocations(_board, AdvanceGuard, _currentPlayer);
				for (const auto& aguard : aguards)
				{
                    _board->Promote(aguard.first, aguard.second);
				}
				const auto rguards = EngineOutputHandler::GetPieceLocations(_board, RearGuard, _currentPlayer);
				for (const auto& rguard : rguards)
				{
                    _board->Promote(rguard.first, rguard.second);
				}
				const auto pfLocations = EngineOutputHandler::GetPieceLocations(_board, PoisonFlame, _currentPlayer == White ? Black : White);
				for (const auto& pfLocation : pfLocations)
				{
					_board->SetData(pfLocation.first, pfLocation.second, std::nullopt);
				}
			}
		}
	}
	else if (std::ranges::find(shogiVariants, _gameVariant) != std::end(shogiVariants))
	{
        const PieceType pt = _currentPiece->Type;
		const bool pcond1 = EngineOutputHandler::CanBePromoted(_currentPiece, _gameVariant, _oldY, y);
		const bool pcond2 = (_gameVariant == ChuShogi || _gameVariant == DaiShogi || _gameVariant == TenjikuShogi) &&
			EngineOutputHandler::IsInsidePromotionZone(_gameVariant, _currentPlayer, _oldY) &&
			EngineOutputHandler::IsInsidePromotionZone(_gameVariant, _currentPlayer, y) && p != std::nullopt;
		const bool pcond3 = _gameVariant == ChuShogi && pt == Pawn &&
            ((y == _board->GetHeight() - 1 && _currentPiece->Colour == Black) || (y == 0 && _currentPiece->Colour == White));
		if (pcond1 || pcond2 || pcond3)
		{
            if (_gameVariant == ToriShogi)
            {
                _board->Promote(x, y);
            }
            else if (((pt == Pawn && _gameVariant != ChuShogi && _gameVariant != HeianDaiShogi) || (pt == Knight && _gameVariant != HeianDaiShogi) ||
                      (pt == Lance && _gameVariant != HeianDaiShogi)) &&
                ((y == _board->GetHeight() - 1 && _currentPiece->Colour == Black) || (y == 0 && _currentPiece->Colour == White)))
			{
                _board->Promote(x, y);
			}
            else if (!_currentPiece->IsPromoted)
			{
				if (AskForPromotion())
				{
                    _board->Promote(x, y);
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
	if (event->type() == QEvent::HoverMove && std::ranges::find(shogiVariants, _gameVariant) != std::end(shogiVariants))
	{
		const QHoverEvent* hoverEvent = dynamic_cast<QHoverEvent*>(event);
		const int w = this->size().width() / _board->GetWidth();
		const int h = this->size().height() / _board->GetHeight();
        const int x = static_cast<int>(hoverEvent->position().x()) / w;
        const int y = static_cast<int>(hoverEvent->position().y()) / h;
		if (x < _board->GetWidth() && y < _board->GetHeight() && (x != _px || y != _py))
		{
			_px = x;
			_py = y;
			const std::optional<Piece> p = _board->GetData(x, y);
			if (p != std::nullopt)
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
	_currentPiece = std::nullopt;
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
    case CapablancaChess:
        _board = new CapablancaChessBoard();
        break;
    case GothicChess:
        _board = new GothicChessBoard();
        break;
    case JanusChess:
        _board = new JanusChessBoard();
        break;
    case GrandChess:
        _board = new GrandChessBoard();
        break;
    case OmegaChess:
        _board = new OmegaChessBoard();
        break;
	case NightriderChess:
		_board = new NightriderChessBoard();
		break;
	case CourierChess:
        _board = new CourierChessBoard();
        break;
    case ChancellorChess:
        _board = new ChancellorChessBoard();
        break;
    case ModernChess:
        _board = new ModernChessBoard();
        break;
	case MusketeerChess:
		_board = new MusketeerChessBoard();
		break;
	case GrandeAcedrex:
        _board = new GrandeAcedrexBoard();
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
	case TaiShogi:
		s = 36;
		_board = new TaiShogiBoard();
		break;
	case MicroShogi:
        _board = new MicroShogiBoard();
        break;
    case KyotoShogi:
        _board = new KyotoShogiBoard();
        break;
    case MiniShogi:
		_board = new MiniShogiBoard();
		break;
	case JudkinShogi:
		_board = new JudkinShogiBoard();
		break;
    case WhaleShogi:
        _board = new WhaleShogiBoard();
        break;
    case ToriShogi:
        _board = new ToriShogiBoard();
        break;
    case EuroShogi:
        _board = new EuroShogiBoard();
        break;
    case YariShogi:
        _board = new YariShogiBoard();
        break;
    case HeianShogi:
        _board = new HeianShogiBoard();
        break;
    case HeianDaiShogi:
        _board = new HeianDaiShogiBoard();
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
    case Janggi:
        _board = new JanggiBoard();
        break;
    case Shatar:
        _board = new ShatarBoard();
        break;
	case Sittuyin:
		_board = new SittuyinBoard();
		break;
	}
    this->setFixedSize(_board->GetWidth() * s + 1, _board->GetHeight() * s + 1);
	if (this->_window != nullptr)
	{
        this->_window->setFixedSize(width() + 280, height() + 100);
        this->_groupBox->setGeometry(x() + width() + 10, y() + 2, 250, 0.2 * height());
        this->_textEdit->setGeometry(x() + width() + 10, y() + 2 + 0.2 * height(), 250, 0.4 * height());
        this->_textEdit2->setGeometry(x() + width() + 10, y() + 2 + 0.6 * height(), 250, 0.4 * height());
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

void VBoard::SetGroupBox(QGroupBox* groupBox)
{
    _groupBox = groupBox;
}

bool VBoard::PossibleMove(int x, int y) const
{
	return std::ranges::any_of(_moves, [x, y](const std::pair<int, int>& p) {return p.first == x && p.second == y;});
}

bool VBoard::PossibleShoot(int x, int y) const
{
	return std::ranges::any_of(_shoots, [x, y](const std::pair<int, int> t) {return t.first == x && t.second == y;});
}

void VBoard::SetMainWindow(QMainWindow *window)
{
	_window = window;
}

void VBoard::SetWhiteEngine(std::shared_ptr<Engine> engine)
{
	_whiteEngine = std::move(engine);
	_whiteEngineBuffer.clear();
}

void VBoard::SetBlackEngine(std::shared_ptr<Engine> engine)
{
	_blackEngine = std::move(engine);
	_blackEngineBuffer.clear();
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

void VBoard::SetEditorMode(bool editorMode, bool newGameStarted)
{
	if (editorMode)
	{
		if (std::ranges::find(chessVariants, _gameVariant) != std::end(chessVariants))
		{
			dynamic_cast<ChessBoard*>(_board)->SetCastling("-");
			dynamic_cast<ChessBoard*>(_board)->SetEnPassant("-");
		}
		delete _editorBoard;
		_editorBoard = _board->Clone();
		if (_editor == nullptr)
		{
			_editor = new Editor();
		}
		int s;
		switch (_gameVariant)
		{
		case DaiShogi:
			s = 60;
			break;
		case TenjikuShogi:
			s = 56;
			break;
		case DaiDaiShogi:
			s = 52;
			break;
		case MakaDaiDaiShogi:
		case KoShogi:
			s = 48;
			break;
		case TaiShogi:
			s = 36;
			break;
		default:
			s = 66;
			break;
		}
		_editor->GetBoard()->setFixedSize(_board->GetWidth() * s + 1, _board->GetHeight() * s + 1);
		_editor->setFixedSize(_editor->GetBoard()->width() + 20, _editor->GetBoard()->height() + 20);
		_editor->GetBoard()->Setup(_board->GetWidth(), _board->GetHeight(), _gameVariant, _pieceStyle);
	}
    else if (!newGameStarted)
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
				_editorBoard = nullptr;
				repaint();
			}
		}
	}
	if (_editor != nullptr)
	{
		_editor->setVisible(editorMode);
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

bool VBoard::GetTimerState() const
{
    return _timerState;
}

void VBoard::SetTimerState(bool timerState)
{
    _timerState = timerState;
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

void VBoard::ReportInfo(const QString& buf, const QString& infoStr, QTextEdit* textEdit, LogLevel logLevel)
{
	switch (logLevel)
	{
	case LogLevel::Info:
		QMessageBox::information(this, infoStr, buf);
		break;
	case LogLevel::Warning:
		QMessageBox::warning(this, infoStr, buf);
		break;
	case LogLevel::Error:
		QMessageBox::critical(this, infoStr, buf);
		break;
	}
	Logger::writeToLog(buf, logLevel);
	textEdit->setText(buf);
}

void VBoard::whiteEngineReadyReadStandardOutput()
{
	if (_whiteEngine == nullptr || !_whiteEngine->IsActive()) return;
	QProcess* p = dynamic_cast<QProcess*>(sender());
	if (p == nullptr) return;
	_whiteEngineBuffer.append(p->readAllStandardOutput());
	const qsizetype nl = _whiteEngineBuffer.lastIndexOf('\n');
	if (nl == -1) return; // no complete line yet — wait for the rest
	const QByteArray buf = _whiteEngineBuffer.left(nl + 1);
	_whiteEngineBuffer.remove(0, nl + 1);
	if (buf.contains("Illegal move"))
	{
		ReportInfo(buf, "Illegal move", _textEdit2, LogLevel::Error);
        EngineOutputHandler::RollbackIllegalMove(_gameVariant, _board, _whiteMoves);
        this->repaint();
        this->_statusBar->showMessage("Black move");
		_currentPlayer = Black;
		return;
	}
	if (buf.contains("tellusererror"))
	{
		ReportInfo(buf, "tellusererror", _textEdit2, LogLevel::Error);
		return;
	}
	if (buf.contains("telluser"))
	{
		ReportInfo(buf, "telluser", _textEdit2, LogLevel::Info);
		return;
	}
	if (buf.contains("tellall"))
	{
		ReportInfo(buf, "tellall", _textEdit2, LogLevel::Info);
		return;
	}
	if (buf.contains("tellopponent"))
	{
		ReportInfo(buf, "tellopponent", _textEdit2, LogLevel::Info);
		return;
	}
	if (buf.contains("askuser"))
	{
		if (_whiteEngine->GetType() != XBoard) return;
		QString str = buf.mid(buf.indexOf("askuser") + QString("askuser").length()).trimmed();
		QStringList parts = str.split(' ');
		if (parts.size() < 2) return;
		const QString& reptag = parts.first();
		const QString& message = parts.sliced(1).join(' ');
		bool ok;
		QString text = QInputDialog::getText(this, message, reptag, QLineEdit::Normal,	"", &ok);
		if (ok)
		{
			dynamic_cast<WbEngine*>(_whiteEngine.get())->SendString((reptag + " " + text).toLatin1());
		}
		return;
	}
	EngineOutputHandler::ReadStandardOutput(buf, _whiteEngine, _board, _textEdit2, _gameVariant, _engineOutput, White);
	if (_blackEngine != nullptr && _blackEngine->IsActive())
	{
        const QByteArray moveArray = EngineOutputHandler::ExtractMove(buf, _whiteEngine->GetType(), _gameVariant);
		if (moveArray.isEmpty()) return;
		if (moveArray.contains("O-O"))
		{
			_blackEngine->Move(moveArray);
		}
		else if (moveArray.size() < 8)
		{
            const Move m = EngineOutputHandler::ByteArrayToMove(moveArray, _blackEngine->GetType(), _board->GetWidth(), _board->GetHeight());
            QByteArray convertedMoveArray = EngineOutputHandler::MoveToByteArray(m, _blackEngine->GetType(), _board->GetWidth(), _board->GetHeight());
			_blackEngine->Move(moveArray[1] == '*' || moveArray[1] == '@' ? moveArray[0] : convertedMoveArray[0],
			                   moveArray[1] == '*' || moveArray[1] == '@' ? moveArray[1] : convertedMoveArray[1],
				               convertedMoveArray[2], convertedMoveArray[3], moveArray.size() > 4 ? moveArray[4] : ' ');
		}
		else
		{
			std::dynamic_pointer_cast<WbEngine>(_blackEngine)->DoubleMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], moveArray[6], moveArray[7]);
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
	if (p == nullptr) return;
	_blackEngineBuffer.append(p->readAllStandardOutput());
	const qsizetype nl = _blackEngineBuffer.lastIndexOf('\n');
	if (nl == -1) return; // no complete line yet — wait for the rest
	const QByteArray buf = _blackEngineBuffer.left(nl + 1);
	_blackEngineBuffer.remove(0, nl + 1);
	if (buf.contains("Illegal move"))
	{
		ReportInfo(buf, "Illegal move", _textEdit, LogLevel::Error);
		EngineOutputHandler::RollbackIllegalMove(_gameVariant, _board, _blackMoves);
        this->repaint();
        this->_statusBar->showMessage(_gameVariant == Xiangqi || _gameVariant == Janggi ? "Red move" : "White move");
		_currentPlayer = White;
		return;
	}
	if (buf.contains("tellusererror"))
	{
		ReportInfo(buf, "tellusererror", _textEdit, LogLevel::Error);
		return;
	}
	if (buf.contains("telluser"))
	{
		ReportInfo(buf, "telluser", _textEdit, LogLevel::Info);
		return;
	}
	if (buf.contains("tellall"))
	{
		ReportInfo(buf, "tellall", _textEdit, LogLevel::Info);
		return;
	}
	if (buf.contains("tellopponent"))
	{
		ReportInfo(buf, "tellopponent", _textEdit, LogLevel::Info);
		return;
	}
	if (buf.contains("askuser"))
	{
		if (_blackEngine->GetType() != XBoard) return;
		QString str = buf.mid(buf.indexOf("askuser") + QString("askuser").length()).trimmed();
		QStringList parts = str.split(' ');
		if (parts.size() < 2) return;
		const QString& reptag = parts.first();
		const QString& message = parts.sliced(1).join(' ');
		bool ok;
		QString text = QInputDialog::getText(this, message, reptag, QLineEdit::Normal, "", &ok);
		if (ok)
		{
			dynamic_cast<WbEngine*>(_blackEngine.get())->SendString((reptag + " " + text).toLatin1());
		}
		return;
	}
	EngineOutputHandler::ReadStandardOutput(buf, _blackEngine, _board, _textEdit, _gameVariant, _engineOutput, Black);
	if (_whiteEngine != nullptr && _whiteEngine->IsActive())
	{
        const QByteArray moveArray = EngineOutputHandler::ExtractMove(buf, _blackEngine->GetType(), _gameVariant);
		if (moveArray.isEmpty()) return;
		if (moveArray.contains("O-O"))
		{
			_whiteEngine->Move(moveArray);
		}
		else if (moveArray.size() < 8)
		{
            const Move m = EngineOutputHandler::ByteArrayToMove(moveArray, _whiteEngine->GetType(), _board->GetWidth(), _board->GetHeight());
            QByteArray convertedMoveArray = EngineOutputHandler::MoveToByteArray(m, _whiteEngine->GetType(), _board->GetWidth(), _board->GetHeight());
			_whiteEngine->Move(moveArray[1] == '*' || moveArray[1] == '@' ? moveArray[0] : convertedMoveArray[0],
			                   moveArray[1] == '*' || moveArray[1] == '@' ? moveArray[1] : convertedMoveArray[1],
				               convertedMoveArray[2], convertedMoveArray[3], moveArray.size() > 4 ? moveArray[4] : ' ');
		}
		else
		{
			std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->DoubleMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], moveArray[6], moveArray[7]);
		}
	}
	else
	{
		_currentPlayer = White;
	}
    this->_statusBar->showMessage(_gameVariant == Xiangqi || _gameVariant == Janggi ? "Red move" : "White move");
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
	if (_editorMode) return;

	const int w = this->size().width() / _board->GetWidth();
	const int h = this->size().height() / _board->GetHeight();
	const int x = event->x() / w;
	const int y = event->y() / h;

    if (_gameVariant != MicroShogi && _gameVariant != KyotoShogi && _gameVariant != Shogi && _gameVariant != MiniShogi &&
		_gameVariant != JudkinShogi && _gameVariant != WhaleShogi && _gameVariant != ToriShogi && _gameVariant != MusketeerChess &&
        _gameVariant != EuroShogi && _gameVariant != YariShogi && _gameVariant != CrazyWa && _gameVariant != Sittuyin) return;
	if ((_blackEngine != nullptr && _blackEngine->IsActive() && _currentPlayer == Black) ||
		(_whiteEngine != nullptr && _whiteEngine->IsActive() && _currentPlayer == White)) return;
	if (_gameVariant == MusketeerChess && _currentPlayer == White && dynamic_cast<MusketeerChessBoard*>(_board)->WhitePiecesToPlace == 0) return;
	if (_gameVariant == MusketeerChess && _currentPlayer == Black && dynamic_cast<MusketeerChessBoard*>(_board)->BlackPiecesToPlace == 0) return;

	QMenu menu(this);

	if (_gameVariant == MusketeerChess && _currentPlayer == Black && _musketeerPiece != None)
	{
		const std::string str = StringManager::PieceType2Description(_gameVariant, _musketeerPiece);
		menu.addAction(QString::fromStdString(str));
	}
	else
	{
		const auto cps = dynamic_cast<PieceStorage*>(_board)->GetCapturedPieces(_currentPlayer);
		for (const auto cp : cps)
		{
			const std::string str = StringManager::PieceType2Description(_gameVariant, cp);
			menu.addAction(QString::fromStdString(str));
		}
	}

	// Execute the menu at the cursor position
	const QAction* selectedAction = menu.exec(event->globalPos());

	// Handle the selected action
	if (selectedAction != nullptr)
	{
        const PieceType newPiece = StringManager::Description2PieceType(_gameVariant, selectedAction->text().toStdString());
		if (_board->GetData(x, y) != std::nullopt)
		{
			QMessageBox mb(QMessageBox::Warning, "Illegal drop", "Square is already occupied",
				QMessageBox::Ok, this);
			mb.exec();
			return;
		}
		if (std::ranges::find(shogiVariants, _gameVariant) != std::end(shogiVariants))
		{
			if (newPiece == Pawn)
			{
				if ((_currentPlayer == White && y == 0) || (_currentPlayer == Black && y == _board->GetHeight() - 1))
				{
					QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot place pawn on the last row",
						QMessageBox::Ok, this);
					mb.exec();
					return;
				}
				const std::optional<Piece> kp = _currentPlayer == White ? _board->GetData(x, y - 1) : _board->GetData(x, y + 1);
				if (kp != std::nullopt && kp->Type == King && kp->Colour != _currentPlayer && _gameVariant != YariShogi)
				{
					QMessageBox mb(QMessageBox::Warning, "Illegal drop", "You cannot check king by the pawn drop",
						QMessageBox::Ok, this);
					mb.exec();
					return;
				}
				for (int index = 0; index < _board->GetHeight(); index++)
				{
					const std::optional<Piece> p = _board->GetData(x, index);
					if (p != std::nullopt && p->Type == Pawn && p->Colour == _currentPlayer)
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
		}
		if (_gameVariant == Sittuyin)
		{
			if (newPiece == Rook)
			{
				if ((_currentPlayer == White && y != _board->GetHeight() - 1) || (_currentPlayer == Black && y != 0))
				{
					QMessageBox mb(QMessageBox::Warning, "Illegal drop", "Rook can only be placed on the first row",
						QMessageBox::Ok, this);
					mb.exec();
					return;
				}
			}
			else
			{
				bool isValidCell;
				if (_currentPlayer == White)
				{
					isValidCell = y >= _board->GetHeight() - 2 || (y == _board->GetHeight() - 3 && x > 3);
				}
				else
				{
					isValidCell = y <= 1 || (y == 2 && x <= 3);
				}
				if (!isValidCell)
				{
					QMessageBox mb(QMessageBox::Warning, "Illegal drop", "Piece cannot be placed on this square",
						QMessageBox::Ok, this);
					mb.exec();
					return;
				}
			}
		}
		if (_gameVariant == MusketeerChess)
		{
			if ((_currentPlayer == White && y != _board->GetHeight() - 1) || (_currentPlayer == Black && y != 0))
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "Pieces can only be placed on the first row",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
			if ((x == _board->GetWidth() - 1 || x == 0) && _board->GetData(4, y) != std::nullopt)
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "Piece cannot be places on Rook file because another piece has been placed on the King file",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
			if (x == 4 && (_board->GetData(_board->GetWidth() - 1, y) != std::nullopt || _board->GetData(0, y) != std::nullopt))
			{
				QMessageBox mb(QMessageBox::Warning, "Illegal drop", "Piece cannot be places on King file because another piece has been placed on the Rook file",
					QMessageBox::Ok, this);
				mb.exec();
				return;
			}
		}
		_board->SetData(x, y, Piece(newPiece, _currentPlayer));
        const char sc = _board->GetStringCode(x, y)[0];
		const std::shared_ptr<Engine> engine = _currentPlayer == White ? _blackEngine : _whiteEngine;
		if (engine != nullptr && engine->IsActive() && _gameVariant != MusketeerChess)
		{
            if (engine->GetType() == USI)
				engine->Move(sc, '*', _board->GetWidth() - x, y, ' ');
			else
				engine->Move(sc, '@', x, _board->GetHeight() - y, ' ');
		}
		EngineOutputHandler::AddMove(_board, _gameVariant, newPiece, sc, '*', x, y, ' ', ' ');
		dynamic_cast<PieceStorage*>(_board)->RemoveCapturedPiece(newPiece, _currentPlayer);
		if (_gameVariant == MusketeerChess)
		{
			if (_currentPlayer == White)
			{
				dynamic_cast<MusketeerChessBoard*>(_board)->WhitePiecesToPlace--;
				if (dynamic_cast<MusketeerChessBoard*>(_board)->WhitePiecesToPlace >= 0)
				{
					if (_blackEngine != nullptr && _blackEngine->IsActive()) return;
				}
				_musketeerPiece = newPiece;
			}
			else
			{
				dynamic_cast<MusketeerChessBoard*>(_board)->BlackPiecesToPlace--;
				if (dynamic_cast<MusketeerChessBoard*>(_board)->BlackPiecesToPlace >= 0)
				{
					if (_whiteEngine != nullptr && _whiteEngine->IsActive()) return;
				}
			}
		}
		FinishMove(x, y);
	}
}
