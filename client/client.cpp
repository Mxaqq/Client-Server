#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Считываем сообщение из аргумента командной строки или из консоли
    std::string message;
    if (argc > 1) {
        message = argv[1];
    } else {
        std::cout << "Введите сообщение для отправки: ";
        std::getline(std::cin, message);
    }

    // Создаем сокет
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Ошибка создания сокета\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразуем IP-адрес в бинарный формат
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Неверный адрес или адрес не поддерживается\n";
        return -1;
    }

    // Подключаемся к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Ошибка подключения\n";
        return -1;
    }

    // Отправляем сообщение
    send(sock, message.c_str(), message.length(), 0);
    std::cout << "Сообщение отправлено: " << message << "\n";

    // Ожидаем ответ от сервера
    int valread = read(sock, buffer, 1024);
    std::cout << "Ответ от сервера: " << buffer << "\n";

    // Закрываем сокет
    close(sock);

    return 0;
}
