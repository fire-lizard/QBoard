#pragma once
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include <QSysInfo>
#include <QDate>
#include <tuple>
#include <vector>
#include "settingsdialog.h"
#include "WbEngine.h"
#include "UciEngine.h"
#include "UcciEngine.h"
#include "UsiEngine.h"
#include "QianhongEngine.h"
#include "ChuShogiEngine.h"
#include "enginemanager.h"
#include "newgamedialog.h"
#include "IniFile.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

	private slots:
	void on_actionSettings_triggered();

	void on_actionAbout_triggered();

	void on_actionExit_triggered();

    void on_actionNew_game_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionStop_game_triggered();

    void on_actionEngine_Manager_triggered();

private:
	void closeEvent(QCloseEvent *) override;

	void LoadEngine();

	static void readXmlUsingStream(const QString& fileName, QTableWidget* engineTable);

	static void createXmlFromTable(const QString& fileName, const QTableWidget* engineTable);

	Ui::MainWindow *ui;
	QString _currentStyle = "";
	Engine *_engine = nullptr;
	QString _engineExe = "";
	QString _engineName = "";
	QStringList _engineArguments;
	EngineProtocol _engineProtocol = WinBoard;
	QString _settingsDir;
	QString _settingsFileName = "QBoard.ini";
	QString _enginesListFileName = "QBoardEngines.xml";
	std::vector<std::tuple<QString, GameVariant, EngineProtocol, QString, QString>> _engines;
};
