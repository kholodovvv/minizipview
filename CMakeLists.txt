cmake_minimum_required(VERSION 3.5)

project(minizipview LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(minizipview
  main.cpp
  mainwindow.cpp
  tablemodel.cpp
  mainwindow.h
  tablemodel.h
)

if(UNIX)

include(FindPkgConfig)
pkg_check_modules(MZIP minizip REQUIRED)
pkg_check_modules(ZL zlib REQUIRED)
pkg_check_modules(OSSL openssl REQUIRED)

link_directories(${MZIP_LIBDIR})
link_directories(${ZL_LIBDIR})
link_directories(${OSSL_LIBDIR})

target_link_libraries("${PROJECT_NAME}" PRIVATE "${MZIP_LIBRARIES}")
target_include_directories("${PROJECT_NAME}" PRIVATE "${MZIP_INCLUDE_DIRS}")

target_link_libraries("${PROJECT_NAME}" PRIVATE "${ZL_LIBRARIES}")
target_include_directories("${PROJECT_NAME}" PRIVATE "${ZL_INCLUDE_DIRS}")

target_link_libraries("${PROJECT_NAME}" PRIVATE "${OSSL_LIBRARIES}")
target_include_directories("${PROJECT_NAME}" PRIVATE "${OSSL_INCLUDE_DIRS}")

elseif(WIN32)

find_package(MZIP minizip REQUIRED)
find_package(ZL zlib REQUIRED)
find_package(OSSL openssl REQUIRED)

link_directories(${MZIP_LIBDIR})
link_directories(${ZL_LIBDIR})
link_directories(${OSSL_LIBDIR})

target_link_libraries("${PROJECT_NAME}" PRIVATE "${MZIP_LIBRARIES}")
target_include_directories("${PROJECT_NAME}" PRIVATE "${MZIP_INCLUDE_DIRS}")

target_link_libraries("${PROJECT_NAME}" PRIVATE "${ZL_LIBRARIES}")
target_include_directories("${PROJECT_NAME}" PRIVATE "${ZL_INCLUDE_DIRS}")

target_link_libraries("${PROJECT_NAME}" PRIVATE "${OSSL_LIBRARIES}")
target_include_directories("${PROJECT_NAME}" PRIVATE "${OSSL_INCLUDE_DIRS}")

endif()

target_link_libraries(minizipview PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
