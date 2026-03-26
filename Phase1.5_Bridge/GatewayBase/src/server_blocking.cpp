#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "Logger.hpp"
#include <arpa/inet.h>
#include <iostream>
int main()
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1)
    {
        perror("socket failed");
        exit(1);
    }

    int opt = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {

        LOG_INFO("[错误] 致命:setsockopt(SO_REUSEADDR) 失败！端口可能仍处于锁定状态。");
        exit(EXIT_FAILURE);
    }
    LOG_INFO("[信息] SO_REUSEADDR 特权授予成功，端口复用已开启。");

    int bind_return = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_return == -1)
    {
        perror("bind failed");
        exit(1);
    }
    int listen_retuen = listen(listen_fd, 10);
    if (listen_retuen == -1)
    {
        perror("listen failed");
        exit(1);
    }
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    int conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (conn_fd == -1)
    {
        perror("accept failed");
    }
    char *client_ip = inet_ntoa(client_addr.sin_addr);
    LOG_INFO("收到连接%s,fd =%d ", client_ip, conn_fd);
    char buffer[1024];
    while (true)
    {
        int bytes_read = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            LOG_INFO("收到数据: %s", buffer);
            send(conn_fd, buffer, bytes_read, 0);
        }
        else if (bytes_read == 0)
        {
            LOG_INFO("客户端主动断开了连接");
            break;
        }
        else
        {
            perror("recv failed");
            break;
        }
    }
    close(conn_fd);
    return 0;
}