#pragma once
#include <QMenu>
#include <QStatusBar>
#include <QPainter>
#include <QMouseEvent>
#include "mainwindow.h"
#include "ChuShogiBoard.h"
#include "DaiShogiBoard.h"
#include "DaiDaiShogiBoard.h"
#include "KoShogiBoard.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiVariantBoard.h"
#include "MiniShogiBoard.h"
#include "JudkinShogiBoard.h"
#include "WaShogiBoard.h"
#include "TenjikuShogiBoard.h"
#include "MakrukBoard.h"
#include "promotiondialog.h"
#include "EngineOutputHandler.h"
#include "Logger.h"

class VBoard : public QWidget
{
	Q_OBJECT
public:
	explicit VBoard(QWidget *parent = nullptr);
	~VBoard() override;
	Board* GetBoard() const;
	GameVariant GetGameVariant() const;
	void SetGameVariant(GameVariant gameVariant);
	PieceStyle GetPieceStyle() const;
	void SetPieceStyle(PieceStyle pieceStyle);
	EngineOutput GetEngineOutput() const;
	void SetEngineOutput(EngineOutput engineOutput);
	PieceColour GetCurrentPlayer() const;
	void SetCurrentPlayer(PieceColour currentPlayer);
	void SetTextEdit(QTextEdit *textEdit);
	void SetTextEdit2(QTextEdit* textEdit);
	void SetStatusBar(QStatusBar *statusBar);
	void SetMainWindow(QMainWindow *window);
	void SetWhiteEngine(std::shared_ptr<Engine> engine);
	void SetBlackEngine(std::shared_ptr<Engine> engine);
	bool GetEditorMode() const;
	void SetEditorMode(bool editorMode);

protected:
	void contextMenuEvent(QContextMenuEvent* event) override;

	bool event(QEvent* event) override;

private:
	void paintEvent(QPaintEvent *) override;

	void mousePressEvent(QMouseEvent *event) override;

	bool CheckRepetition(int oldX, int oldY, int newX, int newY);
	char CheckPromotion(const Piece* p, int y);
	bool PossibleMove(int x, int y) const;
	bool PossibleShoot(int x, int y) const;
	bool AskForPromotion();
	void FinishMove();
	void CancelLionMove();

	Board *_board;
	Board *_editorBoard = nullptr;
	PieceColour _currentPlayer = White;
	PieceStyle _pieceStyle = European;
	EngineOutput _engineOutput = Concise;
	Piece *_currentPiece;
	int _oldX = -1;
	int _oldY = -1;
	int _px = -1;
	int _py = -1;
	std::vector<std::pair<int, int>> _moves;
	std::vector<std::pair<int, int>> _shoots;
	std::vector<std::pair<int, int>> _attackers;
	std::vector<std::pair<int, int>> _defenders;
	std::vector<std::string> _whiteMoves;
	std::vector<std::string> _blackMoves;
	QStatusBar *_statusBar;
	QTextEdit *_textEdit;
	QTextEdit *_textEdit2;
	QMainWindow *_window = nullptr;
	GameVariant _gameVariant = Chess;
	std::shared_ptr<Engine> _whiteEngine = nullptr;
	std::shared_ptr<Engine> _blackEngine = nullptr;
	PieceType _promotedPieces[60] = { Tokin, Prince, PloddingOx, HeavenlyHorse, RaidingFalcon, BearEyes, TenaciousFalcon, HeavenlyTetrarch,
									  WhiteHorse, Whale, MultiGeneral, FreeBoar, FlyingOx, Eagle, Unicorn, FlyingStag, FuriousFiend, GreatElephant,
									  MountainWitch, WizardStork, Emperor, TeachingKing, BuddhistSpirit, FreeGold, FreeSilver, FreeCopper, FreeIron,
									  FreeTile, FreeStone, FreeEarth, FreeTiger, FreeLeopard, FreeSerpent, FreeDragon, FreeCat, GreatDragon, GoldenBird,
									  FreeWolf, FreeBear, Bat, FreeGo, DoubleKylin, DoublePhoenix, ViceCommissioner, CompanyCommander,
									  PoisonFlame, ExtensiveFog, HolyLight, SkywardNet, Thunderclap, RoamingAssault, RisingDragon, WingedTiger,
									  FlyingHawk, EarthwardNet, DivineCarriage, LongbowKnight, CrossbowKnight, CannonCarriage, KnightCaptain };
	PieceColour _chosenColour = White;
	PieceType _chosenPiece = None;
	bool _editorMode = false;
	bool _lionMovedOnce = false;
	bool _lionMovedTwice = false;
	bool _preparedToShoot = false;
	bool _pieceShotOnce = false;
	std::pair<int, int> _firstShoot = { -1, -1 };
	std::pair<int, int> _lionFirstMove = { -1, -1 };
	std::pair<int, int> _lionSecondMove = { -1, -1 };
	std::vector<std::pair<int, int>> _tcMoves;

signals:

	public slots :

	void whiteEngineReadyReadStandardOutput();

	void whiteEngineReadyReadStandardError() const;

	void blackEngineReadyReadStandardOutput();

	void blackEngineReadyReadStandardError() const;
};
