#ifndef __SOCKET_SERVICE_H__
#define __SOCKET_SERVICE_H__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../Models/Logger.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#define DEFAULT_PORT 8080

class SocketService {
    public:
        SocketService(bool isServer, int argc, char** argv)
        : m_logger(LoggerService::getInstance("SocketService"))
        , m_isServer(isServer) {
            LOG_INFO(m_logger, "Create SocketService: argc: " << argc);
            if (argc < 2) {
                m_port = DEFAULT_PORT;
            }
            else {
                LOG_INFO(m_logger, "Port to connect: " << std::string(argv[1]));
                m_port = atoi(argv[1]);
            }

            initialize();
        }
        ~SocketService() {
            close(m_socketfd);
        }

        void initialize() {
            if (m_isServer) {
                // Initialize as ServerSocket
                server_init();
            }
            else {
                // Initialize as ClientSocket
                client_init();
            }
        }

    protected:
        void server_init() {
            LOG_INFO(m_logger, "Start initializing Server!");
            if ((m_socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                LOG_INFO(m_logger, "Failed to open socket");
                return;
            }

            if (setsockopt(m_socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &m_opt, sizeof(m_opt)) < 0) {
                LOG_INFO(m_logger, "Failed to setSocketOpt");
                return;
            }

            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(m_port);

            if (bind(m_socketfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
                LOG_INFO(m_logger, "Failed to bind to socket");
                return;
            }

            if (listen(m_socketfd, 3) < 0) {
                LOG_INFO(m_logger, "Failed to listen on socket");
                return;
            }

            if ((m_connectedFd = accept(m_socketfd, (struct sockaddr*)&address, &addrlen)) < 0) {
                LOG_INFO(m_logger, "Failed to accept socket");
                return;
            }

            LOG_INFO(m_logger, "Completed Initializing Socket Server with address: " << address.sin_addr.s_addr);
            run_server();
        }


        void client_init() {
            LOG_INFO(m_logger, "Start initializing Client!");
            if ((m_socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                LOG_INFO(m_logger, "Failed to open socket");
                return;
            }

            address.sin_family = AF_INET;
            address.sin_port = htons(m_port);
            if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) { 
                LOG_INFO(m_logger, "Invalid address / Address not supported");
                return;
            }

            if (connect(m_socketfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
                LOG_INFO(m_logger, "Connected to host failed");
                return;
            }
            LOG_INFO(m_logger, "Completed Initializing Socket Client with address: " << address.sin_addr.s_addr);

            run_client();
        }

        void run_server() {
            while (1) {
                LOG_INFO(m_logger, " Message in loop of Server ");
                sleep(2);
            };
        }

        void run_client() {
            while (1) {
                LOG_INFO(m_logger, " Message in loop of Client ");
                sleep(2);
            };
        }

    private:
        LoggerService* m_logger{nullptr};
        struct sockaddr_in address;
        socklen_t addrlen;
        int m_socketfd;
        int m_connectedFd;
        int m_opt{1};
        int m_port;
        std::vector<int> m_connectedList;
        bool m_isServer {false};
        bool m_isConnected {false};
};

#endif