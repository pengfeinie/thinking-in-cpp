# 第14章 socket

## 1. 服务端代码 (`server.cpp`)

```c++
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <poll.h>
#include <chrono>
#include <thread>
#include <mutex>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SEND_INTERVAL 1000  // 发送间隔时间，单位：毫秒

std::mutex mtx;

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        // 发送数据到客户端
        const char* message = "Hello from server!";
        int bytesSent = send(clientSocket, message, strlen(message), 0);
        if (bytesSent < 0) {
            perror("Send failed");
            break;  // 如果发送失败，退出线程
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(SEND_INTERVAL));  // 每隔SEND_INTERVAL毫秒发送一次
    }
    close(clientSocket);  // 关闭客户端socket
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // 创建socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置socket选项
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 绑定socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听socket
    if (listen(serverSocket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    std::vector<struct pollfd> pollFds;
    std::vector<int> clientSockets;
    std::vector<std::thread> clientThreads;

    // 初始化pollFds
    struct pollfd serverPollFd;
    serverPollFd.fd = serverSocket;
    serverPollFd.events = POLLIN;
    pollFds.push_back(serverPollFd);

    while (true) {
        // 使用poll来监听socket
        int activity = poll(pollFds.data(), pollFds.size(), -1);
        if (activity < 0) {
            perror("Poll error");
            continue;
        }

        // 检查是否有新的连接
        if (pollFds[0].revents & POLLIN) {
            if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen)) < 0) {
                perror("Accept failed");
                continue;
            }

            std::cout << "New client connected: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

            // 添加新的客户端到pollFds和clientSockets
            struct pollfd clientPollFd;
            clientPollFd.fd = clientSocket;
            clientPollFd.events = POLLOUT;
            pollFds.push_back(clientPollFd);
            clientSockets.push_back(clientSocket);

            // 为每个客户端创建一个线程来处理发送任务
            clientThreads.emplace_back(handleClient, clientSocket);
        }

        // 处理所有客户端的断开连接事件
        for (size_t i = 1; i < pollFds.size(); ++i) {
            if (pollFds[i].revents & (POLLHUP | POLLERR)) {
                std::cout << "Client disconnected: " << clientSockets[i - 1] << std::endl;
                close(pollFds[i].fd);
                pollFds.erase(pollFds.begin() + i);
                clientSockets.erase(clientSockets.begin() + (i - 1));
            }
        }
    }

    // 等待所有客户端线程结束
    for (auto& thread : clientThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    close(serverSocket);
    return 0;
}
```

### 说明

- **服务端**:
  - 使用`poll`来监听多个客户端连接。
  - 当有新的客户端连接时，将其添加到`pollFds`和`clientSockets`列表中，并为每个客户端创建一个单独的线程来处理发送任务。
  - 在`poll`中使用`POLLIN`来监听新的连接，使用`POLLHUP`和`POLLERR`来监听客户端的断开连接事件。
  - 在`for`循环中，遍历所有客户端socket，检查其是否在`POLLHUP`或`POLLERR`中，如果是，则关闭客户端socket并从`pollFds`和`clientSockets`列表中移除该客户端。
  - 使用`std::this_thread::sleep_for`来控制发送频率，确保每次发送数据之间有一定的间隔。

这样，服务端可以更好地管理多个客户端连接，并且在发送数据时不会出现乱码或重复发送的问题。当一个客户端断开连接时，服务端能够正确处理并继续运行。

### 2. 服务端代码 (`server.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SEND_INTERVAL 1000  // 发送间隔时间，单位：毫秒
#define MAX_CLIENTS 10

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    char buffer[BUFFER_SIZE];
    while (1) {
        // 发送数据到客户端
        const char* message = "Hello from server!";
        int bytesSent = send(clientSocket, message, strlen(message), 0);
        if (bytesSent < 0) {
            perror("Send failed");
            break;  // 如果发送失败，退出线程
        }
        usleep(SEND_INTERVAL * 1000);  // 每隔SEND_INTERVAL毫秒发送一次
    }
    close(clientSocket);  // 关闭客户端socket
    free(arg);  // 释放传递的参数内存
    return NULL;
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // 创建socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置socket选项
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 绑定socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听socket
    if (listen(serverSocket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    struct pollfd pollFds[MAX_CLIENTS + 1];
    int clientSockets[MAX_CLIENTS];
    int clientCount = 0;
    pthread_t clientThreads[MAX_CLIENTS];

    // 初始化pollFds
    pollFds[0].fd = serverSocket;
    pollFds[0].events = POLLIN;

    while (1) {
        // 使用poll来监听socket
        int activity = poll(pollFds, clientCount + 1, -1);
        if (activity < 0) {
            perror("Poll error");
            continue;
        }

        // 检查是否有新的连接
        if (pollFds[0].revents & POLLIN) {
            if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen)) < 0) {
                perror("Accept failed");
                continue;
            }

            printf("New client connected: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

            // 添加新的客户端到pollFds和clientSockets
            if (clientCount < MAX_CLIENTS) {
                int* clientSocketPtr = (int*)malloc(sizeof(int));
                *clientSocketPtr = clientSocket;
                pollFds[clientCount + 1].fd = clientSocket;
                pollFds[clientCount + 1].events = POLLOUT;
                clientSockets[clientCount] = clientSocket;
                clientCount++;

                // 为每个客户端创建一个线程来处理发送任务
                pthread_create(&clientThreads[clientCount - 1], NULL, handleClient, clientSocketPtr);
            } else {
                printf("Max clients reached, connection rejected\n");
                close(clientSocket);
            }
        }

        // 处理所有客户端的断开连接事件
        for (int i = 1; i <= clientCount; ++i) {
            if (pollFds[i].revents & (POLLHUP | POLLERR)) {
                printf("Client disconnected: %d\n", clientSockets[i - 1]);
                close(pollFds[i].fd);
                for (int j = i; j < clientCount; ++j) {
                    pollFds[j] = pollFds[j + 1];
                    clientSockets[j - 1] = clientSockets[j];
                }
                clientCount--;
            }
        }
    }

    // 等待所有客户端线程结束
    for (int i = 0; i < clientCount; ++i) {
        pthread_join(clientThreads[i], NULL);
    }

    close(serverSocket);
    return 0;
}
```

## 3. 客户端代码 (`client.cpp`)

```c++
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // 创建socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    // 将IP地址转换为网络字节序
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server" << std::endl;

    while (true) {
        // 接收服务器数据
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            perror("Receive failed or connection closed");
            break;
        }
        std::cout << "Received from server: " << buffer << std::endl;
    }

    close(clientSocket);
    return 0;
}
```

### 4. 编译和运行

**编译服务端代码**:

```
g++ -o server server.cpp -pthread
or
gcc -o server server.c -pthread
```

**编译客户端代码**:

```
g++ -o client client.cpp
```

**运行服务端**:

```
./server
```

**运行客户端**:

```
./client
```



**handleClient 函数如何接收 const char* message ?**

在C语言中，`handleClient`函数可以通过传递参数的方式接收`const char* message`。我们可以将消息作为参数传递给线程函数，并在创建线程时将消息传递给线程函数。

下面是改进后的服务端代码，其中`handleClient`函数接收`const char* message`作为参数：

### 改进后的服务端代码 (`server.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SEND_INTERVAL 1000  // 发送间隔时间，单位：毫秒
#define MAX_CLIENTS 10

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int clientSocket;
    const char* message;
} ClientData;

void* handleClient(void* arg) {
    ClientData* data = (ClientData*)arg;
    int clientSocket = data->clientSocket;
    const char* message = data->message;
    char buffer[BUFFER_SIZE];
    while (1) {
        // 发送数据到客户端
        int bytesSent = send(clientSocket, message, strlen(message), 0);
        if (bytesSent < 0) {
            perror("Send failed");
            break;  // 如果发送失败，退出线程
        }
        usleep(SEND_INTERVAL * 1000);  // 每隔SEND_INTERVAL毫秒发送一次
    }
    close(clientSocket);  // 关闭客户端socket
    free(data);  // 释放传递的参数内存
    return NULL;
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // 创建socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置socket选项
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 绑定socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听socket
    if (listen(serverSocket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    struct pollfd pollFds[MAX_CLIENTS + 1];
    int clientSockets[MAX_CLIENTS];
    int clientCount = 0;
    pthread_t clientThreads[MAX_CLIENTS];

    // 初始化pollFds
    pollFds[0].fd = serverSocket;
    pollFds[0].events = POLLIN;

    while (1) {
        // 使用poll来监听socket
        int activity = poll(pollFds, clientCount + 1, -1);
        if (activity < 0) {
            perror("Poll error");
            continue;
        }

        // 检查是否有新的连接
        if (pollFds[0].revents & POLLIN) {
            if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen)) < 0) {
                perror("Accept failed");
                continue;
            }

            printf("New client connected: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

            // 添加新的客户端到pollFds和clientSockets
            if (clientCount < MAX_CLIENTS) {
                ClientData* data = (ClientData*)malloc(sizeof(ClientData));
                data->clientSocket = clientSocket;
                data->message = "Hello from server!";
                pollFds[clientCount + 1].fd = clientSocket;
                pollFds[clientCount + 1].events = POLLOUT;
                clientSockets[clientCount] = clientSocket;
                clientCount++;

                // 为每个客户端创建一个线程来处理发送任务
                pthread_create(&clientThreads[clientCount - 1], NULL, handleClient, data);
            } else {
                printf("Max clients reached, connection rejected\n");
                close(clientSocket);
            }
        }

        // 处理所有客户端的断开连接事件
        for (int i = 1; i <= clientCount; ++i) {
            if (pollFds[i].revents & (POLLHUP | POLLERR)) {
                printf("Client disconnected: %d\n", clientSockets[i - 1]);
                close(pollFds[i].fd);
                for (int j = i; j < clientCount; ++j) {
                    pollFds[j] = pollFds[j + 1];
                    clientSockets[j - 1] = clientSockets[j];
                }
                clientCount--;
            }
        }
    }

    // 等待所有客户端线程结束
    for (int i = 0; i < clientCount; ++i) {
        pthread_join(clientThreads[i], NULL);
    }

    close(serverSocket);
    return 0;
}
```

### 说明

- **服务端**:
  - 使用`poll`来监听多个客户端连接。
  - 当有新的客户端连接时，将其添加到`pollFds`和`clientSockets`列表中，并为每个客户端创建一个单独的线程来处理发送任务。
  - 在`poll`中使用`POLLIN`来监听新的连接，使用`POLLHUP`和`POLLERR`来监听客户端的断开连接事件。
  - 在`for`循环中，遍历所有客户端socket，检查其是否在`POLLHUP`或`POLLERR`中，如果是，则关闭客户端socket并从`pollFds`和`clientSockets`列表中移除该客户端。
  - 使用`usleep`来控制发送频率，确保每次发送数据之间有一定的间隔。
  - `handleClient`函数接收一个`ClientData`结构体作为参数，该结构体包含客户端socket和要发送的消息。

这样，服务端可以更好地管理多个客户端连接，并且在发送数据时不会出现乱码或重复发送的问题。当一个客户端断开连接时，服务端能够正确处理并继续运行。