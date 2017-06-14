#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include "settingsdialog.h"
#include "ChuShogiBoard.h"
#include "ChessBoard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSettings_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void paintEvent(QPaintEvent *evt);

private:
    Ui::MainWindow *ui;

    bool PossibleMove(int x, int y);

    //ChuShogiBoard _board;
    ChessBoard _board;
    PieceColour _currentPlayer = White;
    bool _check = false;
    Piece *_currentPiece;
    int _oldX = -1;
    int _oldY = -1;
    vector<pair<int,int>> _moves;
    vector<pair<int,int>> _myMoves;
    vector<pair<int,int>> _opponentMoves;
};

#endif // MAINWINDOW_H
