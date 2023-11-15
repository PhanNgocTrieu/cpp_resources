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
#include <errno.h> 
#include <sys/types.h>

#define DEFAULT_PORT 8080
#define MAX_CLIENTS 30

class SocketServiceInterface {
    public:
        virtual int check(int exp, const char* msg) = 0;
};

class SocketServer : public SocketServiceInterface {
    public:
        virtual int check(int exp, const char* msg) override { 
            if (exp == SOCKERROR) {
                
            }
        }
};

class SocketService {
    public:
        typedef struct {
            /**
             * @brief 
             * 
             */
            int master_socket;

            /**
             * @brief 
             * 
             */
            int opt;

            /**
             * @brief Used for multiple clients
             * 
             */
            int readfds;

            /**
             * @brief Used for multiple clients
             * 
             */
            int socket_clients[MAX_CLIENTS];

            /**
             * @brief 
             * 
             */
            int port;

             /**
             * @brief 
             * 
             */
            struct sockaddr_in address;

            /**
             * @brief 
             * 
             */
            socklen_t addrlen;
        } SocketInfor_t;

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
            close(master_socket);
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

            if (m_isMultiClients) {
                //initialise all client_socket[] to 0 so not checked  
                for (int i = 0; i < MAX_CLIENTS; i++)   
                {   
                    socket_clients[i] = 0;
                }
            }

            if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                LOG_INFO(m_logger, "Failed to open socket");
                return;
            }

            if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &m_opt, sizeof(m_opt)) < 0) {
                LOG_INFO(m_logger, "Failed to setSocketOpt");
                return;
            }

            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(m_port);

            if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
                LOG_INFO(m_logger, "Failed to bind to socket");
                return;
            }

            if (listen(master_socket, 3) < 0) {
                LOG_INFO(m_logger, "Failed to listen on socket");
                return;
            }

            if (!m_isMultiClients) {
                if ((m_connectedFd = accept(master_socket, (struct sockaddr*)&address, &addrlen)) < 0) {
                    LOG_INFO(m_logger, "Failed to accept socket");
                    return;
                }
            }

            LOG_INFO(m_logger, "Completed Initializing Socket Server with address: " << address.sin_addr.s_addr);
            run_server();
        }


        void client_init() {
            LOG_INFO(m_logger, "Start initializing Client!");
            if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                LOG_INFO(m_logger, "Failed to open socket");
                return;
            }

            address.sin_family = AF_INET;
            address.sin_port = htons(m_port);
            if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) { 
                LOG_INFO(m_logger, "Invalid address / Address not supported");
                return;
            }

            if (connect(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
                LOG_INFO(m_logger, "Connected to host failed");
                return;
            }

            LOG_INFO(m_logger, "Completed Initializing Socket Client with address: " << inet_ntoa(address.sin_addr));

            run_client();
        }

        void run_server() {
            if (m_isMultiClients) {
                int max_sd, sd, activity, new_socket;
                while (true) {
                    //a message  
                    char *message = "ECHO Daemon v1.0 \r\n";  
                    //clear the socket set  
                    FD_ZERO(&readfds);
                    //add master socket to set  
                    FD_SET(master_socket, &readfds);
                    max_sd = master_socket;

                    //add child sockets to set  
                    for (int i = 0 ; i < MAX_CLIENTS ; i++)   
                    {   

                        //socket descriptor  
                        sd = socket_clients[i];   
                            
                        //if valid socket descriptor then add to read list  
                        if(sd > 0) {
                            FD_SET( sd, &readfds);
                        }
                            
                        //highest file descriptor number, need it for the select function  
                        if(sd > max_sd) max_sd = sd;
                    } 

                    //wait for an activity on one of the sockets , timeout is NULL ,  
                    //so wait indefinitely  (readfds using for reading message from max_sd)
                    activity = select( max_sd + 1 , &readfds , nullptr , nullptr , nullptr );
                    if ((activity < 0) && (errno!=EINTR))   
                    {   
                        LOG_INFO(m_logger,"select error");   
                    }

                    //If something happened on the master socket ,  
                    //then its an incoming connection  
                    if (FD_ISSET(master_socket, &readfds))   
                    {   
                        LOG_INFO(m_logger, "something happened on master socket");
                        if ((new_socket = accept(master_socket,  
                                (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
                        {   
                            LOG_ERROR(m_logger,"accept error");
                            exit(EXIT_FAILURE);
                        }

                        //inform user of socket number - used in send and receive commands  
                        LOG_INFO(m_logger, "New connection, socket fd is " << new_socket << "ip is : " << inet_ntoa(address.sin_addr) << ", port is " << ntohs(address.sin_port));
                    
                        //send new connection greeting message  
                        if( send(new_socket, message, strlen(message), 0) != strlen(message) )
                        {   
                            LOG_ERROR(m_logger, "Send failed");
                        }
                            
                        LOG_INFO(m_logger,"Welcome message sent successfully");
                            
                        //add new socket to array of sockets  
                        for (int i = 0; i < MAX_CLIENTS; i++)   
                        {   
                            //if position is empty  
                            if( socket_clients[i] == 0 )   
                            {   
                                socket_clients[i] = new_socket;
                                LOG_INFO(m_logger,"Adding to list of sockets as: " << i << " with socket: " << new_socket);
                                break;   
                            }   
                        }

                        //else its some IO operation on some other socket 
                        for (int i = 0; i < MAX_CLIENTS; i++)   
                        {   
                            sd = socket_clients[i];   
                            if (FD_ISSET( sd , &readfds))   
                            {   
                                char buffer[1024];
                                int valread;
                                //Check if it was for closing , and also read the incoming message  
                                if ((valread = read( sd , buffer, 1024)) == 0)   
                                {   
                                    //Somebody disconnected , get his details and print  
                                    getpeername(sd, (struct sockaddr*)&address ,(socklen_t*)&addrlen);   
                                    LOG_INFO(m_logger, "Host disconnected, id: " << std::string(inet_ntoa(address.sin_addr)) << ", port: " << ntohs(address.sin_port));
                                    //Close the socket and mark as 0 in list for reuse  
                                    close(sd);
                                    socket_clients[i] = 0;
                                }   
                                //Echo back the message that came in  
                                else 
                                {   
                                    //set the string terminating NULL byte on the end of the data read  
                                    buffer[valread] = '\0';   
                                    send(sd , buffer , strlen(buffer) , 0 );   
                                }   
                            }   
                        }
                    }

                    // for (int i = 0; i < MAX_CLIENTS; i++) {
                    //     if (socket_clients[i] != 0) {
                    //         LOG_INFO(m_logger, "Socket sending for message:" << socket_clients[i] );
                    //         if (recv(socket_clients[i], message, strlen(message), 0) != strlen(message)) {
                    //             LOG_INFO(m_logger, std::string(message));
                    //         }
                    //         sleep(2);
                    //         send(socket_clients[i], message, strlen(message), 0) != strlen(message);
                    //         LOG_INFO(m_logger, " Sent message: " << message);
                    //     }
                    // }
                    // for (int i = 0; i < MAX_CLIENTS; i++) {
                    //     if (socket_clients[i] != 0) {
                    //         send(new_socket, message, strlen(message), 0) != strlen(message);
                    //         LOG_INFO(m_logger, " Sent message: " << message);
                    //     }
                    //     else {
                    //         break;
                    //     }
                    // }
                    // sleep(1);
                    LOG_INFO(m_logger, " Server Loops " );
                }
            }
            else {
                while (1) {
                    LOG_INFO(m_logger, " Message in loop of Server ");
                    sleep(1);
                };
            }
        }

        void run_client() {
            while (1) {
                char* message = "Hello world";
                send(master_socket, message, sizeof(message), 0);
                LOG_INFO(m_logger, "Sent: " << std::string(message));
                char buffer[1024];
                if ((recv( master_socket , buffer, 1024, 0) != 0)) {
                    LOG_INFO(m_logger, std::string(buffer));
                    // char *message = "Hello from Clients\n";
                    // write(master_socket, message, sizeof(message));
                    // LOG_INFO(m_logger, " Message in loop of Client ");
                }
                else {
                    break;
                }
                //Check if it was for closing , and also read the  
                //incoming message  
                sleep(2);
                LOG_INFO(m_logger, " Client loops ");
            };
        }

    private:
        /**
         * @brief 
         * 
         */
        LoggerService* m_logger{nullptr};

        /**
         * @brief 
         * 
         */
        SocketInfor_t m_socketHolder;

        /**
         * @brief 
         * 
         */
        struct sockaddr_in address;

        /**
         * @brief 
         * 
         */
        socklen_t addrlen;
        
        /**
         * @brief 
         * 
         */
        std::vector<int> m_connectedList;

        /**
         * @brief master_socket
         * 
         */
        int master_socket;

        /**
         * @brief connected socket
         * 
         */
        int m_connectedFd;

        /**
         * @brief 
         * 
         */
        int m_opt{1};
        int m_port;
        bool m_isServer {false};
        bool m_isConnected {false};
        bool m_isMultiClients {true};
        //set of socket descriptors  
        fd_set readfds;
        fd_set writefds;
        int socket_clients[MAX_CLIENTS];
};

#endif