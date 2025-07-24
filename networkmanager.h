#pragma once
#include <QDialog>

namespace Ui {
    class NetworkManager;
}

class NetworkManager : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkManager(QWidget* parent = nullptr);
    ~NetworkManager() override;

private:
    Ui::NetworkManager* ui;
};
