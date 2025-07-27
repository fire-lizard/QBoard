#pragma once
#include <QApplication>
#include <QPointer>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

class Communications : public QObject
{
    Q_OBJECT

public:
    Communications();
    static void SetGui(QDialog* gui);
    static void SetVBoard(QWidget* vboard);
    bool is_connected_remotely() const;
    bool is_listening() const;
    static QHostAddress preferred_host_address(const QAbstractSocket::NetworkLayerProtocol protocol);
    void connect_remotely();
    void disconnect_remotely() const;
    void initialize();
    void quit();
    void send_move(const std::string& fen) const;
    void set_listen();
    void stop_listening();

private:
    QPointer<QTcpSocket> m_client_connection;
    QTcpServer m_listening_socket;
    static constexpr int s_buffer_size = 2048;
    static QString SocketErrorToString(QAbstractSocket::SocketError error);
    void prepare_connection_status() const;

private slots:
    void slot_accept_connection();
    void slot_client_connected();
    void slot_client_disconnected();
    void slot_disconnected(QAbstractSocket::SocketError error) const;
    void slot_update_board() const;

signals:
    void connected_to_client();
    void disconnected_from_client();
};
