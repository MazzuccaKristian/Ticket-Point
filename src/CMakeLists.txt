cmake_minimum_required(VERSION 3.16.3)

project(TicketPoint VERSION 0.0.1)

set(EXECUTABLES
    ${PROJECT_SOURCE_DIR}/Classes/Person.cpp
    ${PROJECT_SOURCE_DIR}/Classes/User.cpp
    ${PROJECT_SOURCE_DIR}/Classes/Technician
    ${PROJECT_SOURCE_DIR}/Database/Database.cpp
    ${PROJECT_SOURCE_DIR}/Utils/Utils.cpp
    ${PROJECT_SOURCE_DIR}/Main.cpp)

add_executable(${PROJECT_NAME} ${EXECUTABLES})

target_link_libraries(${PROJECT_NAME} mysqlcppconn)

# TESTING executables
add_executable(connection ${PROJECT_SOURCE_DIR}/Test/Connection.cpp ${PROJECT_SOURCE_DIR}/Database/Database.cpp)
target_link_libraries(connection mysqlcppconn)
add_executable(retrieveTickets ${PROJECT_SOURCE_DIR}/Test/RetrieveTickets.cpp ${PROJECT_SOURCE_DIR}/Database/Database.cpp)
target_link_libraries(retrieveTickets mysqlcppconn)
add_executable(ticketCreation ${PROJECT_SOURCE_DIR}/Test/TicketCreation.cpp ${PROJECT_SOURCE_DIR}/Database/Database.cpp)
target_link_libraries(ticketCreation mysqlcppconn)
###

enable_testing()

# UNIT TESTS
add_test(NAME connection COMMAND $<TARGET_FILE:connection>)
set_property(TEST connection PROPERTY WILL_FAIL false)
add_test(NAME retrieveTickets COMMAND $<TARGET_FILE:retrieveTickets>)
set_property(TEST retrieveTickets PROPERTY WILL_FAIL false)
add_test(NAME ticketCreation COMMAND $<TARGET_FILE:ticketCreation>)
# set_property(TEST ticketCreation PROPERTY WILL_FAIL false)
#