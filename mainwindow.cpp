#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog *settingsDialog = new SettingsDialog();
    settingsDialog->exec();
    if (settingsDialog->result() == QDialog::Accepted)
    {
    }

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "QBoard 1.0");
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::paintEvent(QPaintEvent *evt)
{
    QPainter painter(ui->vboard);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::NoBrush);

        QSize s = ui->vboard->size();;
        int w = s.width() / _board.GetWidth();
        int h = s.height() / _board.GetHeight();
        for (int i = 0; i < _board.GetWidth(); i++)
        {
            for (int j = 0; j < _board.GetHeight(); j++)
            {
                /*if (PossibleMove(i, j))
                {
                    if (_board.GetData(i, j) != nullptr)
                    {
                        dc.SetBrush(*wxRED_BRUSH);
                        dc.DrawRectangle(i * w, j * h, w, h);
                        dc.SetBrush(wxNullBrush);
                    }
                    else if (_board.GetData(i, j) == nullptr)
                    {
                        dc.SetBrush(*wxCYAN_BRUSH);
                        dc.DrawRectangle(i * w, j * h, w, h);
                        dc.SetBrush(wxNullBrush);
                    }
                }
                else if (any_of(_opponentMoves.begin(), _opponentMoves.end(), [=](pair<int,int> p){return p.first == i && p.second == j;}))
                {
                    if (_board.GetData(i, j) != nullptr && (_board.GetData(i, j)->GetType() == King || _board.GetData(i, j)->GetType() == Queen))
                    {
                        dc.SetBrush(*wxYELLOW_BRUSH);
                        if (_board.GetData(i, j)->GetType() == King)
                            _check = true;
                    }
                    dc.DrawRectangle(i * w, j * h, w, h);
                    dc.SetBrush(wxNullBrush);
                }
                else
                {
                    dc.DrawRectangle(i * w, j * h, w, h);
                }*/
            }
        }
        /*for (int i = 0; i < _board.GetWidth(); i++)
        {
            for (int j = 0; j < _board.GetHeight(); j++)
            {
                Piece *p = _board.GetData(i, j);
                if (p != nullptr)
                {
                    PieceType t = p->GetType();
                    PieceColour c = p->GetColour();
                    wxImage image("images/" + Piece::GetImageFileName(t, c));
                    wxBitmap bitmap(image);
                    dc.DrawBitmap(bitmap, i * w + 10, j * h + 5);
                }
            }
        }*/
}

bool MainWindow::PossibleMove(int x, int y)
{
    for (unsigned index = 0; index < _moves.size(); index++)
    {
        if (_moves[index].first == x && _moves[index].second == y)
        {
            return true;
        }
    }
    return false;
}
