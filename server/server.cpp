#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *response = "Окей";

    // Создаем сокет
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    // Привязываем сокет к порту
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Ошибка при установке параметров сокета");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Ошибка привязки сокета");
        exit(EXIT_FAILURE);
    }

    // Ожидаем подключения
    if (listen(server_fd, 3) < 0) {
        perror("Ошибка ожидания подключения");
        exit(EXIT_FAILURE);
    }

    std::cout << "Ожидание сообщения от клиента...\n";

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Ошибка принятия подключения");
        exit(EXIT_FAILURE);
    }

    // Читаем сообщение от клиента
    int valread = read(new_socket, buffer, 1024);
    if (valread < 0) {
        perror("Ошибка при чтении сообщения от клиента");
    } else {
        std::cout << "Получено сообщение: " << buffer << "\n";
    }

    // Отправляем ответ клиенту
    int send_result = send(new_socket, response, strlen(response), 0);
    if (send_result < 0) {
        perror("Ошибка отправки ответа клиенту");
    } else {
        std::cout << "Ответ отправлен: Окей\n";
    }

    // Закрываем сокет
    close(new_socket);
    close(server_fd);

    return 0;
}
