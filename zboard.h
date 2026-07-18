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
    void Fill(int count, PieceType *pieces);
    void Setup(int width, int height, GameVariant gameVariant, PieceStyle pieceStyle);
    std::optional<Piece> GetChosenPiece() const;
    static int GetRowCount(GameVariant gameVariant);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    std::vector<PieceType> GetPromotedPieces() const;

	int _width = 8;
    int _height = 8;
    bool _editorMode = true;
	PieceStyle _pieceStyle = European;
    GameVariant _gameVariant = Chess;
    std::optional<Piece> _chosenPiece = std::nullopt;
    std::vector<std::optional<Piece>> _pieces;
};
