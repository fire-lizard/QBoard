#pragma once
#include <vector>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "Common.h"
#include "MakrukPiece.h"
#include "KanjiPiece.h"
#include "ChuShogiPiece.h"
#include "graphicsmanager.h"

class ZBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ZBoard(QWidget *parent = nullptr, int width = 2, int height = 9);
    void Fill(PieceColour pieceColour, std::vector<std::pair<PieceColour, PieceType>> capturedPieces);
    void Fill(int count, PieceType *pieces);
    PieceType GetChosenPiece();
    void SetChosenPiece(PieceType chosenPiece);

signals:

private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

    int _width;
    int _height;
    PieceStyle _pieceStyle;
    GameVariant _gameVariant;
    bool _editorMode;
    PieceType _chosenPiece;
    std::vector<PieceType> _pieces;
};
