#pragma once
#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QStandardPaths>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "comboboxitemdelegate.h"
#include "Common.h"
#include "addenginedialog.h"

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

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
    Ui::EngineManager *ui;

    static EngineProtocol StringToEngineProtocol(const QString& str);

    static void addElementToXmlStream(const QString& fileName, const QString& engineName, const QString& engineProtocol, const QString& enginePath);

    static void modifyXmlElement(const QString& fileName, const QString& engineName, const QString& engineProtocol, const QString& enginePath);

    void readXmlUsingStream(const QString& fileName) const;

    static bool hasAttributeWithSpecificValue(const QString& fileName, const QString& attributeName, const QString& attributeValue);

    static void deleteXmlElementByAttribute(const QString& fileName, const QString& attributeName, const QString& attributeValue);
};
