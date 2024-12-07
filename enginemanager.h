#pragma once
#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include "comboboxitemdelegate.h"
#include "addenginedialog.h"
#include "Common.h"

namespace Ui {
class EngineManager;
}

class EngineManager : public QDialog
{
    Q_OBJECT

public:
    explicit EngineManager(QWidget *parent = nullptr);
    ~EngineManager() override;
	QTableWidget* GetEngineTable() const;
    static GameVariant StringToGameVariant(const QString& str);
    static EngineProtocol StringToEngineProtocol(const QString& str);

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

    void on_engineTable_cellDoubleClicked(int row, int column);

private:
    Ui::EngineManager *ui;
};
