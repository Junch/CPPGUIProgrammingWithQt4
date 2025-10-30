# Expenses example
cmake_minimum_required(VERSION 3.16)
project(expenses)

set(CMAKE_AUTOMOC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBS Qt5::Widgets)
endif()

add_executable(expenses
    expense.h
    expensedialog.h
    expensewindow.h
    expense.cpp
    expensedialog.cpp
    expensewindow.cpp
    main.cpp
)

target_link_libraries(expenses ${QT_LIBS})
