cmake_minimum_required(VERSION 3.10)
project(ClientServerApp)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем подпроекты
add_subdirectory(client)
add_subdirectory(server)
