#include "SocketService.h"

#define PORT 8000
#define NUMBER_CLIENTS 30
#define BUFFER_SIZE 2048

SocketServer* SocketServer::getInstance() {
    static SocketServer ins;
    return &ins;
}

SocketServer::SocketServer()
: m_logger(LoggerService::getInstance("SocketServer")) {
    
}

SocketServer::~SocketServer() {}


int SocketServer::setup(int argc, char* argv) {
    if (set_socket() < 0) { return -1; }
    if (set_bind() < 0) { return -2; }
    if (start_listen() < 0) { return -3; }
}

int SocketServer::set_socket() {
    m_masterSocket = socket(PF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (m_masterSocket < 0) {
        LOG_ERROR(m_logger, "Failed to create socket");
        return -1;
    }

    FD_ZERO(&master_fds);
    FD_ZERO(&connect_fds);

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(PORT);
    m_addr.sin_addr.s_addr = INADDR_ANY;

    if (setsockopt(m_masterSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        LOG_ERROR(m_logger, "Failed to setSocketOpt");
        return -1;
    }
    LOG_INFO(m_logger, "Success to create socket");
    return 0;
}

int SocketServer::start_listen() {
    int status = listen(m_masterSocket, NUMBER_CLIENTS);
    if (status < 0) {
        LOG_ERROR(m_logger, "Failed to bind listen socket");
        return -1;
    }
    LOG_INFO(m_logger, "Success to set listen socket");
    return status;
}

int SocketServer::set_bind() {
    int status = bind(m_masterSocket, (struct sockaddr*)&m_addr, sizeof(m_addr));
    if (status < 0) {
        LOG_ERROR(m_logger, "Failed to bind socket");
        return -1;
    }
    LOG_INFO(m_logger, "Success to bind socket");
    FD_SET(m_masterSocket, &master_fds); //insert the master socket file-descriptor into the master fd-set
	m_maxfd = m_masterSocket;
    return 0;
}

void SocketServer::loop() {
}

void SocketServer::resgisterConnectionCallback(const newConnectionCallback& cb) {
    if (cb != nullptr) {
        LOG_INFO(m_logger,"Register connection callback successful");
        m_connectCallback = cb;
    }
    LOG_ERROR(m_logger,"Register connection callback failed");
}

void SocketServer::resgisterDisconnectionCallback(const disconnectCallback& cb) {
    if (cb != nullptr) {
        LOG_INFO(m_logger,"Register disconnection callback successful");
        m_disconnectCallback = cb;
    }
    LOG_ERROR(m_logger,"Register disconnection callback failed");
}

void SocketServer::resgisterReceiveCallback(const receiveCallback& cb) {
    if (cb != nullptr) {
        LOG_INFO(m_logger,"Register receiving callback successful");
        m_receiveCallback = cb;
    }
    LOG_ERROR(m_logger,"Register receiving callback failed");
}

uint16_t SocketServer::sendMessage(SocketInterface::Connector conn, const char *messageBuffer) {
    return send(conn.source_fd, messageBuffer, strlen(messageBuffer), 0);
}

uint16_t SocketServer::sendMessage(SocketInterface::Connector conn, char *messageBuffer) {
    return send(conn.source_fd, messageBuffer, strlen(messageBuffer), 0);
}

void SocketServer::handleNewConnection() {
    LOG_INFO(m_logger,"New Connection Handle");
}

void SocketServer::handleReceiveMsg(int fd) {
    LOG_INFO(m_logger,"Receive Message Handle");
}

void SocketServer::handleDisconnect() {
    LOG_INFO(m_logger,"Disconnected Handle");
}
