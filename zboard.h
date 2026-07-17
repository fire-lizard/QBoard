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
    void Setup(int width, int height, GameVariant gameVariant, PieceStyle pieceStyle);
    PieceColour GetChosenColour() const;
    PieceType GetChosenPiece() const;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
	int _width = 0;
    int _height = 0;
    bool _editorMode = true;
	PieceStyle _pieceStyle = European;
    GameVariant _gameVariant = Chess;
    PieceColour _chosenColour = White;
    PieceType _chosenPiece = None;
    std::vector<std::pair<PieceColour, PieceType>> _pieces;
};
