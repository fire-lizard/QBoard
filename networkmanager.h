#pragma once
#include <QDialog>
#include <QHostAddress>
#include <QLineEdit>
#include <QSpinBox>
#include <QFileDialog>
#include <QSettings>
#include "Communications.h"

namespace Ui {
    class NetworkManager;
}

class NetworkManager : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkManager(QWidget* parent = nullptr);
    ~NetworkManager() override;
    void SetCommunications(Communications* communications);
	QHostAddress get_listening_address() const;
    QLineEdit* get_allowed_host_field() const;
    QLineEdit* get_local_host_field() const;
    QLineEdit* get_remote_host_field() const;
    QLineEdit* get_remote_scope_id_field() const;
    QSpinBox* get_local_port_field() const;
    QSpinBox* get_remote_port_field() const;
    void reset() const;
    void stop() const;

private:
    Ui::NetworkManager* ui;
    Communications* _comm;

private slots:
    void slot_connect() const;
    void slot_connected_to_client() const;
    void slot_disconnect() const;
    void slot_disconnected_from_client() const;
    void slot_listen() const;
    void slot_local(bool state) const;
    void slot_protocol_changed() const;
    void slot_remote(bool state) const;
};
