#pragma once
#include <tuple>
#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include "comboboxitemdelegate.h"
#include "addenginedialog.h"
#include "Common.h"

namespace Ui {
class EngineManager;
}

namespace {
    using Pair = QPair<GameVariant, QString>;

    const QList<Pair>& variantMap()
    {
        static const QList<Pair> map = {
            {Chess,           "Chess"},
            {CapablancaChess, "Capablanca Chess"},
            {GothicChess,     "Gothic Chess"},
            {JanusChess,      "Janus Chess"},
            {Xiangqi,         "Xiangqi"},
            {Shogi,           "Shogi"},
            {ShoShogi,        "Sho Shogi"},
            {ChuShogi,        "Chu Shogi"},
            {DaiShogi,        "Dai Shogi"},
            {TenjikuShogi,    "Tenjiku Shogi"},
            {DaiDaiShogi,     "Dai Dai Shogi"},
            {MakaDaiDaiShogi, "Maka Dai Dai Shogi"},
            {KoShogi,         "Ko Shogi"},
            {MiniShogi,       "Mini Shogi"},
            {JudkinShogi,     "Judkins Shogi"},
            {WhaleShogi,      "Whale Shogi"},
            {ToriShogi,       "Tori Shogi"},
            {EuroShogi,       "Euro Shogi"},
            {Shatranj,        "Shatranj"},
            {Makruk,          "Makruk"},
            {WaShogi,         "Wa Shogi"},
            {CrazyWa,         "CrazyWa"}
        };
        return map;
    }
}

class EngineManager : public QDialog
{
    Q_OBJECT

public:
    explicit EngineManager(QWidget *parent = nullptr);
    ~EngineManager() override;
	QTableWidget* GetEngineTable() const;
    static QString GameVariantToString(GameVariant variant);
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
