cmake_minimum_required(VERSION 3.16.3)

project(TicketPoint)

set(EXECUTABLES
    ${PROJECT_SOURCE_DIR}/Classes/Person.cpp
    ${PROJECT_SOURCE_DIR}/Classes/User.cpp
    ${PROJECT_SOURCE_DIR}/Classes/Technician
    ${PROJECT_SOURCE_DIR}/Database/Database.cpp
    ${PROJECT_SOURCE_DIR}/Utils/Utils.cpp
    ${PROJECT_SOURCE_DIR}/Main.cpp)

add_executable(${PROJECT_NAME} ${EXECUTABLES})

target_link_libraries(${PROJECT_NAME} mysqlcppconn)