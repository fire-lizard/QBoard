#pragma once
#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include "comboboxitemdelegate.h"
#include "addenginedialog.h"

namespace Ui {
class EngineManager;
}

class EngineManager : public QDialog
{
    Q_OBJECT

public:
    explicit EngineManager(QWidget *parent = nullptr);
    ~EngineManager();
	QTableWidget* GetEngineTable();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
    Ui::EngineManager *ui;
};
