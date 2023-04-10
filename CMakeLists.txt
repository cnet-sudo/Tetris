cmake_minimum_required(VERSION 3.21)
project(Tetris VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(Tetris main.cpp GameEngine.cpp GameEngine.h AssetManager.cpp AssetManager.h GameSound.cpp GameSound.h
Tetramino.cpp Tetramino.h Button.cpp Button.h)

add_custom_command(TARGET Tetris POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/sound
                        $<TARGET_FILE_DIR:Tetris>/sound
                   VERBATIM)
add_custom_command(TARGET Tetris POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/font
                        $<TARGET_FILE_DIR:Tetris>/font
                   VERBATIM)
add_custom_command(TARGET Tetris POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/image
                        $<TARGET_FILE_DIR:Tetris>/image
                   VERBATIM)
				   
add_custom_command(
  TARGET Tetris POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${PROJECT_SOURCE_DIR}/openal32.dll
    $<TARGET_FILE_DIR:Tetris>/openal32.dll)

target_link_libraries(Tetris PRIVATE sfml-graphics sfml-system sfml-window sfml-audio )

target_compile_features(Tetris PRIVATE cxx_std_14)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Tetris> $<TARGET_FILE_DIR:Tetris> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Tetris)

# Директория с СMakeLists.txt
# cmake -S . -B build
# cmake --build build --config Release
# cmake --build build --config Debug
# Для запуска проекта выбрать активный проект