
# Добавляем исполняемый файл для клиента с уникальным именем
add_executable(client_app client.cpp)

# Включаем нужные библиотеки
find_package(Threads REQUIRED)
target_link_libraries(client_app PRIVATE Threads::Threads)
