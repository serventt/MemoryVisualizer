cmake_minimum_required(VERSION 3.10)
project(MemoryVisualizer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(SFML_DIR "C:/libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

# --- DLL Deployment Logic ---

# Define the list of DLLs required for the project
# Note: Ensure the 'bin' folder path matches your SFML installation
set(SFML_BIN_DIR "C:/libraries/SFML-2.5.1/bin")

set(SFML_DLLS
    "${SFML_BIN_DIR}/sfml-graphics-d-2.dll"
    "${SFML_BIN_DIR}/sfml-window-d-2.dll"
    "${SFML_BIN_DIR}/sfml-system-d-2.dll"
    "${SFML_BIN_DIR}/sfml-audio-d-2.dll"
)

# This command runs AFTER the build finishes successfully
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SFML_DLLS}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Deploying SFML DLLs to the output directory..."
)	