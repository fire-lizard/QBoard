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

void Editor::Relayout()
{
    constexpr int margin = 10;
    const QSize dims = ui->zboard->Dimensions();
    const int cell = std::max(8, std::min((width() - 2 * margin) / dims.width(),
                                          (height() - 2 * margin) / dims.height()));
    ui->zboard->setGeometry(margin, margin, dims.width() * cell + 1, dims.height() * cell + 1);
}

void Editor::resizeEvent(QResizeEvent*)
{
    Relayout();
}
