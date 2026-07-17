#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}

ZBoard* Editor::GetBoard() const
{
    return ui->zboard;
}
