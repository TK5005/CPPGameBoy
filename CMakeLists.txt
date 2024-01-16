cmake_minimum_required(VERSION 3.18.4)

# Set the project name and version
project(GameboyCPP VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

# Add the executable
add_executable(
        ${PROJECT_NAME}
        src/Main.cpp
        src/GameboyCPU.cpp
        src/GameboyMMU.cpp
        src/Opcodes.cpp
        src/GameboyBus.cpp
        src/Cartridge.cpp
        src/ByteUtility.cpp
        )

add_executable(
        GameboyUnitTests
        unitTests/OpcodeTest.cpp
        unitTests/GameboyBusTest.cpp
)

add_executable(
        CartridgeDevTest
        devTests/CartridgeDevTest.cpp
        src/Cartridge.cpp
        src/ByteUtility.cpp
)

add_executable(
        MMUDevTest
        devTests/MMUDevTest.cpp
        src/GameboyBus.cpp
        src/GameboyMMU.cpp
        src/GameboyCPU.cpp
        src/Cartridge.cpp
        src/ByteUtility.cpp
)

add_executable(
        GameboyBusDevTest
        devTests/GameboyBusDevTest.cpp
        src/GameboyCPU.cpp
        src/GameboyMMU.cpp
        src/Opcodes.cpp
        src/GameboyBus.cpp
        src/Cartridge.cpp
        src/ByteUtility.cpp
)

add_executable(
        ClockDevTest
        devTests/ClockDevTest.cpp
        src/GameboyCPU.cpp
        src/GameboyMMU.cpp
        src/Opcodes.cpp
        src/GameboyBus.cpp
        src/Cartridge.cpp
        src/ByteUtility.cpp
        src/Clock.cpp
)

target_link_libraries(
        GameboyUnitTests
        GTest::gtest_main
)

target_link_libraries(
        ${PROJECT_NAME}
        sfml-graphics
        sfml-audio
)

target_link_libraries(
        ClockDevTest
        sfml-graphics
        sfml-audio
        sfml-system
)

file(COPY roms DESTINATION .)

include(GoogleTest)
gtest_discover_tests(GameboyUnitTests)