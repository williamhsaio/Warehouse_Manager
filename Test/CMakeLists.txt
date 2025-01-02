cmake_minimum_required(VERSION 3.16)

project(Warehouse_Test LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

if ($ENV{GOOGLETEST_DIR})
    get_filename_component(_GTEST_BASE $ENV{GOOGLETEST_DIR} REALPATH)
elseif (EXISTS "/Users/dongmei/googletest/build/googletest") # set by QC
    get_filename_component(_GTEST_BASE "/Users/dongmei/googletest/build/googletest" REALPATH) # set by QC
endif()

if (NOT GTEST_ROOT)
    if (_GTEST_BASE)
        message("Setting GTEST_ROOT to ${_GTEST_BASE}")
        set(GTEST_ROOT ${_GTEST_BASE})
    else()
        message("No GTEST_ROOT specified - using system defaults.")
    endif()
endif()

find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    message (FATAL_ERROR "No GTest Found")
endif()

add_executable(Warehouse_Test main.cpp tst_product.cpp
../product.h ../product.cpp
tst_tablemodel.cpp ../tablemodel.h ../tablemodel.cpp
)
add_test(NAME Product COMMAND Product)

target_link_libraries(Warehouse_Test PRIVATE GTest::GTest Qt${QT_VERSION_MAJOR}::Core)
if (GMock_FOUND)
    target_link_libraries(Warehouse_Test INTERFACE GTest::GMock)
endif()
