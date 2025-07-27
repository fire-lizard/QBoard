#pragma once
#include <QApplication>
#include <QPointer>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QCryptographicHash>
#include <QNetworkInterface>

enum BoardInformation
{
    EMPTY_SQUARE = 0,
    INVALID = 0,
    NSQUARES = 8,
    VALID = 1,
    VALID_CASTLE = 2,
    VALID_EN_PASSANT = 4,
    VALID_PAWN2 = 3
};

enum StateInformation
{
    BLACK = 1,
    I_AM_FIRST = 4,
    MY_TURN = 3,
    OPPONENT_TIMER = 8,
    PLAYER_TIMER = 7,
    THEIR_TURN = 5,
    THEY_ARE_FIRST = 6,
    WHITE = 2
};

struct move_s
{
    char m_departure[3];
    int m_board[NSQUARES][NSQUARES];
    int m_enpassant;
    int m_is_opponent_king_threat;
    int m_pawn2; // Did a pawn move two squares?
    int m_piece;
    int m_promoted;
    int m_rook; // Castling.
    int m_rook_x1; // Castling.
    int m_rook_x2; // Castling.
    int m_rook_y1; // Castling.
    int m_rook_y2; // Castling.
    int m_x1;
    int m_x2;
    int m_y1;
    int m_y2;
};

class Communications : public QObject
{
    Q_OBJECT

public:
    Communications();
    static void SetGui(QDialog* gui);
    static void SetVBoard(QWidget* vboard);
    bool is_connected_remotely() const;
    bool is_listening() const;
    bool is_ready() const;
    static QHostAddress preferred_host_address(const QAbstractSocket::NetworkLayerProtocol protocol);
    void connect_remotely();
    void disconnect_remotely() const;
    void initialize();
    void quit();
    void send_move(const struct move_s& current_move);
    void set_listen();
    void stop_listening();

private:
    QPointer<QTcpSocket> m_client_connection;
    QTcpServer m_listening_socket;
    static constexpr int s_buffer_size = 1024;
    static QString SocketErrorToString(QAbstractSocket::SocketError error);
    QByteArray xor_arrays(const QByteArray& a, const QByteArray& b) const;
    bool memcmp(const QByteArray& a, const QByteArray& b) const;
    static QByteArray hmac(const QByteArray& data, const QByteArray& k);
    static QByteArray shax(const QByteArray& data);
    void prepare_connection_status() const;

private slots:
    void slot_accept_connection();
    void slot_client_connected();
    void slot_client_disconnected();
    void slot_disconnected(QAbstractSocket::SocketError error) const;
    void slot_update_board();

signals:
    void connected_to_client();
    void disconnected_from_client();
};
