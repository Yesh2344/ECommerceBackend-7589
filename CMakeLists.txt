cmake_minimum_required(VERSION 3.15)
project(ECommerceBackend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------
# Dependencies
# -------------------------------------------------
include(FetchContent)

# Catch2 for unit testing
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(catch2)

# -------------------------------------------------
# Source files
# -------------------------------------------------
set(SRC_FILES
    src/Logger.cpp
    src/Config.cpp
    src/Cart.cpp
    src/CreditCardProcessor.cpp
    src/PayPalProcessor.cpp
    src/main.cpp
)

add_executable(ECommerceBackend ${SRC_FILES})

target_include_directories(ECommerceBackend PRIVATE src)

# -------------------------------------------------
# Testing
# -------------------------------------------------
add_executable(test_cart tests/test_cart.cpp src/Cart.cpp src/Logger.cpp src/Config.cpp)
target_include_directories(test_cart PRIVATE src)
target_link_libraries(test_cart PRIVATE Catch2::Catch2WithMain)

add_test(NAME CartTests COMMAND test_cart)