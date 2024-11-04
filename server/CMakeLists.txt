
# Добавляем исполняемый файл для сервера с уникальным именем
add_executable(server_app server.cpp)

# Включаем нужные библиотеки
find_package(Threads REQUIRED)
target_link_libraries(server_app PRIVATE Threads::Threads)
