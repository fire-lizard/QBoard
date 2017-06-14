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
    QApplication::quit();
}
