#pragma once
#include <QDialog>
#include "zboard.h"

namespace Ui {
class Editor;
}

class Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor() override;
    ZBoard* GetBoard() const;

private:
    Ui::Editor *ui;
};
