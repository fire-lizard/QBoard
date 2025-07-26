#pragma once
#include <QMainWindow>
#include <QCheckBox>
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
#include "enginemanager.h"
#include "networkmanager.h"
#include "newgamedialog.h"
#include "Communications.h"
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

	void on_actionPlace_triggered() const;

	void on_actionClear_triggered() const;

	void on_actionExit_triggered() const;

    void on_actionNew_game_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionStop_game_triggered() const;

    void on_actionEngine_Manager_triggered();

	void on_actionNetwork_Manager_triggered();

private:
	void closeEvent(QCloseEvent *) override;

	void LoadEngine(const std::shared_ptr<Engine>& engine, const QString& engineExe, PieceColour player);

	static void StopEngine(std::shared_ptr<Engine> engine);

	void StartNewGame(GameVariant newGameVariant) const;

	static void readXmlUsingStream(const QString& fileName, QTableWidget* engineTable);

	static void createXmlFromTable(const QString& fileName, const QTableWidget* engineTable);

	Ui::MainWindow *ui;
	std::shared_ptr<Communications> _comm;
	QString _currentStyle = "";
	int _engineMemorySize = 80;
	std::shared_ptr<Engine> _whiteEngine = nullptr;
	QString _whiteEngineExe = "";
	QString _whiteEngineName = "";
	EngineProtocol _whiteEngineProtocol = XBoard;
	std::shared_ptr<Engine> _blackEngine = nullptr;
	QString _blackEngineExe = "";
	QString _blackEngineName = "";
	EngineProtocol _blackEngineProtocol = XBoard;
	QString _userName;
	QString _settingsDir;
	QString _settingsFileName = "QBoard.ini";
	QString _enginesListFileName = "QBoardEngines.xml";
	std::vector<std::tuple<QString, GameVariant, EngineProtocol, QString>> _engines;
};
