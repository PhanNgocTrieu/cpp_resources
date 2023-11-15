#ifndef SOCKET_SERVICE_H__
#define SOCKET_SERVICE_H__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <errno.h> 
#include <sys/types.h>
#include <functional>

class SocketInterface {
    public:
        struct Connector {
            uint16_t source_fd;
        };
    public:
        virtual int setup(int argc = -1, char* argv = nullptr) = 0;
        virtual void loop() = 0;

};

class SocketServer : public SocketInterface {
    public:
        typedef std::function<void (uint16_t fd)> newConnectionCallback;
        typedef std::function<void (uint16_t fd, char *buffer)> receiveCallback;
        typedef std::function<void (uint16_t fd)> disconnectCallback;

    public:
        static SocketServer* getInstance();
        virtual ~SocketServer();
        virtual int setup(int argc = -1, char* argv= nullptr) override;
        virtual void loop() override;

        void resgisterConnectionCallback(const newConnectionCallback& cb);
        void resgisterDisconnectionCallback(const disconnectCallback& cb);
        void resgisterReceiveCallback(const receiveCallback& cb);

        uint16_t sendMessage(Connector conn, const char *messageBuffer);
        uint16_t sendMessage(Connector conn, char *messageBuffer);

    protected:
        int set_socket();
        int set_bind();
        int start_listen();
        void handleNewConnection();
        void handleReceiveMsg(int fd);
        void handleDisconnect();

    private:
        SocketServer();
        SocketServer(const SocketServer& other) = delete;
        SocketServer& operator=(const SocketServer& other) = delete;

    private:
        LoggerService* m_logger;
        sockaddr_in m_addr;
        int m_masterSocket;
        int m_clientSocket;
        int m_maxfd;
        int readfs;
        fd_set master_fds;
        fd_set connect_fds;
        newConnectionCallback m_connectCallback;
        disconnectCallback m_disconnectCallback;
        receiveCallback m_receiveCallback;
};

#endif /* SOCKET_SERVICE_H__ */