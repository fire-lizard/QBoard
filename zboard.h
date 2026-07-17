#pragma once
#include <vector>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "Common.h"
#include "graphicsmanager.h"

class ZBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ZBoard(QWidget *parent = nullptr);
    void Fill(std::vector<std::pair<PieceColour, PieceType>> capturedPieces);
    void Fill(int count, PieceColour pieceColour, PieceType *pieces);
    PieceColour GetChosenColour() const;
    PieceType GetChosenPiece() const;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
	int _width;
    int _height;
    bool _editorMode = true;
	PieceStyle _pieceStyle;
    GameVariant _gameVariant;
    PieceColour _chosenColour = White;
    PieceType _chosenPiece = None;
    std::vector<std::pair<PieceColour, PieceType>> _pieces;
};
